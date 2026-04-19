#include "../include/mainHeader.hpp"

/*
static bool validateConfig(std::vector<Server> &servers)
{
	
}
*/

static bool duplicatedSocket(const std::string &host, const std::string &port, const std::vector<Socket> &sockets)
{
	for(unsigned int i = 0; i < sockets.size(); i++)
	{
		if (sockets[i].getHost() == host && sockets[i].getPort() == port)
			return SUCCESS;
	}
	return FAIL;
}

static bool parseSockets(const std::vector<Server> &servers, std::vector<Socket> &sockets)
{
	size_t i = 0;
	std::string host;
	in_addr_t   ip;
	std::string port;

	while (i < servers.size())
	{
		host = servers[i].getHost();
		port = servers[i].getPort();
		ip = inet_addr(servers[i].getHost().c_str());
		if (ip == BAD_IP)
		{
			std::cout << "[ERROR]: The Host IP: " << host << " is invalid." << std::endl;
			return FAIL;
		}
		if(!duplicatedSocket(host, port, sockets))
		{
			Socket socket(host, port);
			sockets.push_back(socket);
		}
		i++;
	}
	return SUCCESS;
}

static bool checkSocketPort(const std::vector<Socket> &sockets, size_t *i)
{
	int opt = 1;

	if (setsockopt(sockets[*i].getSocketFD(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		return FAIL;
	return SUCCESS;
}

static bool bindSocket(const std::vector<Socket> &sockets, const size_t *i)
{
	const struct sockaddr_in &addr = sockets[*i].getAddress();

	if(bind(sockets[*i].getSocketFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return FAIL;
	return SUCCESS;
}

static bool listenSocket(const std::vector<Socket> &sockets, const size_t *i)
{
	if(listen(sockets[*i].getSocketFD(), SOMAXCONN) < 0)
		return FAIL;
	return SUCCESS;
}

bool createSockets(const std::vector<Server> &servers, std::vector<Socket> &sockets)
{
	size_t i = 0;
	int fd;

	if(!parseSockets(servers, sockets))
	{
		std::cerr << "[ERROR]: Error creating parsing the sockets." << std::endl;
		return FAIL;
	}
	while (i < sockets.size())
	{
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd == -1)
		{
			std::cout << "[ERROR]: Error creating the socket." << std::endl;
			return FAIL;
		}
		sockets[i].setSocketFD(fd);
		if (!checkSocketPort(sockets, &i))
		{
			std::cout << "[ERROR]: The port selected for the socket is being in use, please use another one." << std::endl;
			return FAIL;
		}
		if (fcntl(sockets[i].getSocketFD(), F_SETFL, O_NONBLOCK) == -1)
		{
			std::cout << "[ERROR]: The socket cannot be set to non-block." << std::endl;
			return FAIL;
		}
		if (!bindSocket(sockets, &i))
		{
			std::cout << "[ERROR]: Error binding the socket FD to the address." << std::endl;
			return FAIL;
		}
		if (!listenSocket(sockets, &i))
		{
			std::cout << "[ERROR]: The socket doesn't recieve a connection." << std::endl;
			return FAIL;
		}
		i++;
	}
	return SUCCESS;
}