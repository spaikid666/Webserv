#include "../include/mainHeader.hpp"

std::vector<std::string> getTokens(const std::string& filePath)
{
	std::vector<std::string> tokens;
	std::string line;
	std::ifstream configFile(filePath.c_str());

	if(!configFile.is_open())
	{
		std::cerr << "[Error]: The configuration file can't be opened." << std::endl;
		return std::vector<std::string>();
	}

	size_t i = 0;
	char c;
	std::string tmp;
	
	while(std::getline(configFile, line))
	{
		i = 0;
		while(i < line.size())
		{
			c = line[i];
			if (std::isspace(c))
			{
				if (!tmp.empty())
				{
					tokens.push_back(tmp);
					tmp.clear();
				}
				i++;
				continue;
			}
			else if (c == '{' || c == '}' || c == ';')
			{
				if (!tmp.empty())
				{
					tokens.push_back(tmp);
					tmp.clear();
				}
				tokens.push_back(std::string(1, c));
				i++;
				continue;
			}
			tmp.push_back(c);
			i++;
		}
		if (!tmp.empty())
		{
			tokens.push_back(tmp);
			tmp.clear();
		}
	}
	return tokens;
}

std::vector<Server> parseTokens(const std::vector<std::string> &tokens)
{
	std::vector<Server> servers;

	for(size_t i = 0; i < tokens.size(); ++i)
	{
		if(tokens[i] == "server")
		{
			Server svr;
			if(!parseServer(svr, tokens, &i))
				return std::vector<Server>();
			servers.push_back(svr);
		}
		/*
		else if(tokens[i] == "#")
		{
			// For the moment I set if a token is '#' just return
			// an error because comments are not supported for the parsing
			std::cerr << "[Error]: Please delete the comments from the configuration file." << std::endl;
			return std::vector<Server>();
		}
		*/
	}
	return servers;
}

bool parseServer(Server &svr, const std::vector<std::string> &tokens, size_t *i)
{
	while(*i < tokens.size())
	{
		if (tokens[*i] == "}")
			return SUCCESS;
		if (tokens[*i] == "server" || tokens[*i] == "{" || tokens[*i] == ";")
		{
			(*i)++;
			continue;
		}
		if(tokens[*i] == "listen")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setPort(tokens[*i + 1]);
		}
		else if(tokens[*i] == "host")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setHost(tokens[*i + 1]);
		}
		else if(tokens[*i] == "server_name")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setServerName(tokens[*i + 1]);	
		}
		else if(tokens[*i] == "client_max_body_size")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			// Here I'm checking if the last character of the string
			// that stores the client_max_body_size has a 'M' at the end or not
			if(tokens[*i + 1][tokens[*i + 1].size() - 1] != 'M')
			{
				std::cout << tokens[*i + 1][tokens[*i + 1].size() - 1] << std::endl;
				// Here I'm checking if it doesn't have a 'M' at the end,
				// I want to make sure that the value inserted is a valid digit.
				// ****** TO DO: Correct the parsing, when it's only 'M' the paramether for 'client_max_body_size' is valid and the program doesn't give a shit.
				if(!std::strtol(tokens[*i + 1].c_str(), NULL, 10))
				{
					std::cerr << "[Error]: There value provided for the paramether 'client_max_body_size' is not valid." << std::endl;
					std::cout << tokens[*i + 1] << std::endl;
					return FAIL;
				}
			}
			svr.setMaxBody(tokens[*i + 1]);
		}
		else if(tokens[*i] == "error_page")
		{
			if (missingField(tokens[*i + 1]) || missingField(tokens[*i + 2]))
				return FAIL;
			else if (tokens[*i + 1] != "404")
			{
				std::cerr << "[Error]: The Error Page Code is invalid, it must be '404'." << std::endl;
				return FAIL;
			}
			svr.setErrorPage(tokens[*i + 2]);
		}
		else if(tokens[*i] == "root")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setRoot(tokens[*i + 1]);
		}
		else if(tokens[*i] == "index")
		{
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setIndex(tokens[*i + 1]);
		}
		/*
		else if(tokens[*i] == "location")
		{
			parseLocation(svr, tokens, i);
		}
		*/
		(*i)++;
	}
	return SUCCESS;
}

bool missingField(std::string token)
{
	if(token == ";")
	{
		std::cerr << "[Error]: There is a missing field in the configuration file." << std::endl;
		return SUCCESS;
	}
	else
		return FAIL;
}

/*
void parseLocation(Server svr, const std::vector<std::string> &tokens, size_t *i)
{
	
}
*/