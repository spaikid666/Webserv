#include "../include/mainHeader.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "[Error]: Number of arguments invalid. Try: ./webserv [configuration file]" << std::endl;
		return 1;
	}

	if(!checkConfigFile(argv[1]))
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

	std::cout << servers[0].getHost() << std::endl;

	return 0;
}