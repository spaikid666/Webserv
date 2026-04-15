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
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <poll.h>
#include <map>

/* Custom Macros */
#define FAIL false
#define SUCCESS true
#define BAD_IP 0xFFFFFFFF

/* Classes */
#include "Server.hpp"
#include "Location.hpp"
#include "Socket.hpp"
#include "Client.hpp"
#include "ServerManager.hpp"

/* From FileCheck.cpp */
bool fileNotEmpty(const std::string &filePath);
bool fileExtension(const std::string &filePath, std::string ext);
bool checkFile(const std::string &filePath);

/* From Parse.cpp */
std::vector<std::string> getTokens(const std::string &filePath);
std::vector<Server> parseTokens(const std::vector<std::string> &tokens);

/* From ServerLoop.cpp */
bool serverLoop(ServerManager svrMan);

/* From SocketConfig.cpp */
bool createSockets(const std::vector<Server> &servers, std::vector<Socket> &sockets);

#endif