#include "../include/mainHeader.hpp"

static bool hasNextToken(const std::vector<std::string> &tokens, size_t i, const std::string &field)
{
	if (i + 1 >= tokens.size())
	{
		std::cerr << "[Error]: Missing value for '" << field << "'." << std::endl;
		return FAIL;
	}
	return SUCCESS;
}

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
	while(*i < tokens.size() && tokens[*i] != "}")
	{
		if (tokens[*i] == "server" || tokens[*i] == "{" || tokens[*i] == ";")
		{
			(*i)++;
			continue;
		}
		if(tokens[*i] == "listen")
		{
			if (!hasNextToken(tokens, *i, "listen"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setPort(tokens[*i + 1]);
		}
		else if(tokens[*i] == "host")
		{
			if (!hasNextToken(tokens, *i, "host"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setHost(tokens[*i + 1]);
		}
		else if(tokens[*i] == "server_name")
		{
			if (!hasNextToken(tokens, *i, "server_name"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setServerName(tokens[*i + 1]);	
		}
		else if(tokens[*i] == "client_max_body_size")
		{
			if (!hasNextToken(tokens, *i, "client_max_body_size"))
				return FAIL;
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
			if (!hasNextToken(tokens, *i, "error_page") || !hasNextToken(tokens, *i + 1, "error_page"))
				return FAIL;
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
			if (!hasNextToken(tokens, *i, "root"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setRoot(tokens[*i + 1]);
		}
		else if(tokens[*i] == "index")
		{
			if (!hasNextToken(tokens, *i, "index"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			svr.setIndex(tokens[*i + 1]);
		}
		else if(tokens[*i] == "location")
		{
			if (!hasNextToken(tokens, *i, "location"))
				return FAIL;
			if (missingField(tokens[*i + 1]))
				return FAIL;
			if(!parseLocation(svr, tokens, i))
			{
				std::cerr << "[Error]: There was an error getting the locations settings from the server." << std::endl;
				return FAIL;
			}
		}
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


bool parseLocation(Server &svr, const std::vector<std::string> &tokens, size_t *i)
{
	Location location;
	if (*i + 2 >= tokens.size())
	{
		std::cerr << "[Error]: Invalid location block." << std::endl;
		return FAIL;
	}

	location.setPath(tokens[++(*i)]);
	if(tokens[++(*i)] == "{")
	{
		while(*i < tokens.size() && tokens[*i] != "}")
		{
			if(tokens[*i] == "allowed_methods" || tokens[*i] == "allow_methods")
			{
				(*i)++;
				if (missingField(tokens[*i]))
					return FAIL;
				
				std::vector<std::string> methods;

				while(*i < tokens.size() && tokens[*i] != ";")
				{
					if(tokens[*i] == "GET")
						methods.push_back("GET");
					else if(tokens[*i] == "POST")
						methods.push_back("POST");
					else if(tokens[*i] == "DELETE")
						methods.push_back("DELETE");
					else
						return FAIL;
					(*i)++;
				}
				if (*i >= tokens.size() || methods.empty())
					return FAIL;
				location.setAllowedMethods(methods);
			}
			else if(tokens[*i] == "autoindex")
			{
				if (!hasNextToken(tokens, *i, "autoindex"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				else if (tokens[*i] == "ON" || tokens[*i] == "on")
					location.setAutoindex(true);
				else if (tokens[*i] == "OFF" || tokens[*i] == "off")
					location.setAutoindex(false);
				else
					return FAIL;
			}
			else if(tokens[*i] == "root")
			{
				if (!hasNextToken(tokens, *i, "root"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setRoot(tokens[*i]);
			}
			else if(tokens[*i] == "upload")
			{
				if (!hasNextToken(tokens, *i, "upload"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setUpload(tokens[*i]);
			}
			else if(tokens[*i] == "return")
			{
				if (!hasNextToken(tokens, *i, "return") || !hasNextToken(tokens, *i + 1, "return"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setReturnCode(std::atoi(tokens[(*i)++].c_str()));
				if (!(location.getReturnCode()))
					return FAIL;
				location.setReturnPath(tokens[(*i)++]);
			}
			else if(tokens[*i] == "client_max_body_size")
			{
				if (!hasNextToken(tokens, *i, "client_max_body_size"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setMaxBody(tokens[(*i)]);
			}
			else if(tokens[*i] == "cgi_ext")
			{
				if (!hasNextToken(tokens, *i, "cgi_ext"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setCgiExt(tokens[(*i)]);
			}
			else if(tokens[*i] == "cgi_path")
			{
				if (!hasNextToken(tokens, *i, "cgi_path"))
					return FAIL;
				if (missingField(tokens[++(*i)]))
					return FAIL;
				location.setCgiPath(tokens[(*i)]);
			}
			(*i)++;
		}
	}
	else
	{
		return FAIL;
	}
	svr.setLocation(location);
	return SUCCESS;
}
