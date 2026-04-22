#include "../include/mainHeader.hpp"

ServerManager::ServerManager() {}

ServerManager::ServerManager(const std::vector<Server> &servers, const std::vector<Socket> &sockets)
{   
    (void)servers;
    (void)sockets;
}

ServerManager::ServerManager(const ServerManager &other)
{
    this->_servers = other._servers;
    this->_sockets = other._sockets;
}

ServerManager& ServerManager::operator=(const ServerManager &other)
{
    if (this != &other)
    {
        this->_servers = other._servers;
        this->_sockets = other._sockets;
    }
    return *this;
}

ServerManager::~ServerManager() {}



void ServerManager::setServers(const std::vector<Server> &servers)
{
    this->_servers = servers;
}

void ServerManager::setSockets(const std::vector<Socket> &sockets)
{
	this->_sockets = sockets;
}



const std::vector<Server> ServerManager::getServers()
{
    return this->_servers;
}

const std::vector<Socket> ServerManager::getSockets()
{
    return this->_sockets;
}




std::vector<Server> ServerManager::parseServers(const char *configFile)
{
	if(!checkFile(configFile))
		return std::vector<Server>();

	std::vector<std::string> tokens = getTokens(configFile);

	if (tokens.empty())
	{
		std::cerr << "[ERROR]: The server's Configuration File is empty." << std::endl;
		return std::vector<Server>();
	}
	
	std::vector<Server> servers;
	servers = parseTokens(tokens);

	if (servers.empty())
	{
		std::cerr << "[ERROR]: Error when parsing the Configuration File." << std::endl;
		return std::vector<Server>();
	}

	return servers;
}


std::vector<Socket> ServerManager::startSockets(std::vector<Socket> &sockets)
{
	if(!createSockets(this->getServers(), sockets))
	{
		std::cerr << "[ERROR]: The server's configuration is invalid." << std::endl;
		return std::vector<Socket>();
	}
	return sockets;
}


bool ServerManager::setUpServers(const char *configFile)
{
	this->setServers(this->parseServers(configFile));
	if (this->getServers().empty())
		return FAIL;
		
	std::vector<Socket> sockets;
	this->setSockets(this->startSockets(sockets));
	if (this->getSockets().empty())
		return FAIL;

	return SUCCESS;
}

bool ServerManager::initServer()
{
	int poll_return;

	this->createPolls();

	while (true)
	{
		poll_return = poll(&this->_pollFDs[0], this->_pollFDs.size(), -1);
		if (poll_return < 0)
		{
			std::cerr << "[ERROR]: Error, poll() failed." << std::endl;
			return FAIL;
		}
		std::cout << "Poll woke up, number of new total events incoming: " << poll_return << std::endl;

		for (size_t i = 0; i < this->_pollFDs.size(); i++)
		{
			if (this->_pollFDs[i].revents & POLLIN)
			{
				if (this->isServerFD(this->_pollFDs[i].fd))
				{
					if (!handleNewClient(&i))
					{
						std::cerr << "[ERROR]: Error creating the new client." << std::endl;
						continue;
					}
				}
				else
				{
					if (!handleClientEvent(&i))
					{
						std::cerr << "[ERROR]: There was an error inside the client's routine loop." << std::endl;
						return FAIL;
					}	
				}
			}
		}

	}

	return SUCCESS;
}

void ServerManager::createPolls()
{
	struct pollfd pollFD;

	for(size_t i = 0; i < this->_sockets.size(); i++)
	{
		pollFD.fd = this->_sockets[i].getSocketFD();
		pollFD.events = POLLIN;
		pollFD.revents = 0;
		this->_pollFDs.push_back(pollFD);
	}
}

bool ServerManager::isServerFD(int fd)
{
	for (size_t i = 0; i < this->_sockets.size(); i++)
	{
		if (fd == this->_sockets[i].getSocketFD())
			return SUCCESS;
	}
	return FAIL;
}

bool ServerManager::handleNewClient(size_t *i)
{
	std::cout << "New client connecting" << std::endl;
	int client_fd = accept(this->_pollFDs[*i].fd, NULL, NULL);

	if (client_fd < 0)
	{
		std::cerr << "[ERROR]: accept() failed." << std::endl;
		return FAIL;
	}

	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "[ERROR]: fcntl() failed on client's socket." << std::endl;
		close(client_fd);
		return FAIL;
	}

	struct pollfd client_poll;
	client_poll.fd = client_fd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	this->_pollFDs.push_back(client_poll);

	this->_clients[client_fd] = Client();

	std::cout << "Successfully added client on FD: " << client_fd << std::endl;

	return SUCCESS;
}

bool ServerManager::handleClientEvent(size_t *i)
{
	std::cout << "Client sent data" << std::endl;
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	int bytes_read = recv(_pollFDs[*i].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_read <= 0)
	{
		if (!deleteClient(i))
			return FAIL;
		else
			return SUCCESS;
	}
	if (bytes_read > 0)
	{
		// This is for checking if the HTTP request if full, if not iterate again over poll until getting the full request
		int new_request = this->_clients[_pollFDs[*i].fd].appendRequest(buffer, bytes_read);
		if (new_request)
		{
			// The next 2 std::cout lines are just for debbuging, they must be deleted later
			std::cout << "----- DEBUG LINE FOR CHECKING IF THE DATA FROM THE CLIENT IS SAVED CORRECTLY -----" << std::endl;
			std::cout << "Client " << _pollFDs[*i].fd << " sent: " << _clients[_pollFDs[*i].fd].getClientRawRequest() << std::endl;
			//HTTP PARSING (ULISES)
		}
	}

	return SUCCESS;
}

bool ServerManager::deleteClient(size_t *i)
{
    int delete_fd = this->_pollFDs[*i].fd;
    std::cout << "Client " << delete_fd << " disconnected." << std::endl;
    
    if (close(delete_fd) < 0)
	{
		std::cerr << "[ERROR]: Error deleting the client." << std::endl;
		return FAIL;
	}
    
    this->_clients.erase(delete_fd);
    this->_pollFDs.erase(this->_pollFDs.begin() + *i);
    (*i)--;
    
    return SUCCESS;
}