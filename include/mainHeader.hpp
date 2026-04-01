#ifndef MAINHEADER_HPP
#define MAINHEADER_HPP

/* System libraries */
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

/* Custom Macros */
#define FAIL false
#define SUCCESS true

/* Classes */
#include "Server.hpp"

/* From FileCheck.cpp */
bool fileNotEmpty(const std::string &filePath);
bool fileExtension(const std::string &filePath, std::string ext);
bool checkConfigFile(const std::string &filePath);

/* From Parse.cpp */
std::vector<std::string> getTokens(const std::string &filePath);
std::vector<Server> parseTokens(const std::vector<std::string> &tokens);
bool parseServer(Server &svr, const std::vector<std::string> &tokens, size_t *i);
void parseLocation(Server svr, const std::vector<std::string> &tokens, size_t *i);
bool missingField(std::string token);

#endif