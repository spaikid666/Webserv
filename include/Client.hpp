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
		void setRawRequest(const std::string &rawRequest);

        int getClientFD();
		std::string getClientRawRequest();

		bool appendRequest(const char *request, size_t bytes);

    private:
        int _clientFD;
		std::string _rawRequest;

};

#endif