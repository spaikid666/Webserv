#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include "mainHeader.hpp"

class ServerManager
{
    public:
        ServerManager();
        ServerManager(const std::vector<Server> &servers, const std::vector<Socket> &sockets);
        ServerManager(const ServerManager &other);
        ServerManager &operator=(const ServerManager &other);
        ~ServerManager();

        void setServers(const std::vector<Server> &servers);
        void setSockets(const std::vector<Socket> &sockets);

        const std::vector<Server> getServers();
        const std::vector<Socket> getSockets();

        std::vector<Server> parseServers(const char *configFile);
        std::vector<Socket> startSockets(std::vector<Socket> &sockets);
        bool setUpServers(const char *configFile);
        bool initServer();

        void createPolls();
        bool isServerFD(int fd);
		bool handleNewClient(size_t *i);
		bool handleClientEvent(size_t *i);
		bool deleteClient(size_t *i);

    private:
        std::vector<Server> _servers;
        std::vector<Socket> _sockets;
        std::vector<struct pollfd> _pollFDs;
        std::map<int, Client> _clients;
};

#endif