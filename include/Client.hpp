#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "mainHeader.hpp"

class Client
{
    public:
        Client();
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client();
    
        void setClientFD(const int &fd);

        int getClientFD();

    private:
        int _clientFD;

};

#endif