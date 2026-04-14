#include "../include/mainHeader.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "[ERROR]: Number of arguments invalid. Try: ./webserv [configuration file]" << std::endl;
		return 1;
	}

	if(!checkFile(argv[1]))
		return 1;
	
	std::vector<std::string> tokens = getTokens(argv[1]);
	if (tokens.empty())
		return 1;

	/* For checking if all the tokens are printed propertly:
	for (size_t i = 0; i < tokens.size(); ++i)
		std::cout << tokens[i] << std::endl;
	*/
	
	std::vector<Server> servers = parseTokens(tokens);
	if (servers.empty())
		return 1;

	/* For checking that all the paramethers from location are parsed correctly 
	const std::vector<Location>& locations = servers[1].getLocations();
	std::cout << locations[0].getAutoindex() << std::endl;
	std::cout << locations[0].getPath() << std::endl;
	std::cout << locations[0].getMaxBody() << std::endl;
	*/

	std::vector<Socket> sockets;

	if(!(createSockets(servers, sockets)))
	{
		std::cerr << "[ERROR]: The server's configuration is invalid." << std::endl;
		return 1;
	}



	return 0;
}