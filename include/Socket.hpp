#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "mainHeader.hpp"

class Socket
{
	public:
		Socket(std::string host, std::string port);
		Socket(const Socket &other);
		Socket &operator=(const Socket &other);
		~Socket();

		void setSocketFD(const int &socketFD);
		void setHost(const std::string &host);
		void setPort(const std::string &port);
		void setAddress(const sockaddr_in &address);

		const int &getSocketFD() const;
		const std::string &getHost() const;
		const std::string &getPort() const;
		const sockaddr_in &getAddress() const;
		const int &getIsListening() const;

	private:
		int _socketFD;
		std::string _host;
		std::string _port;
		struct sockaddr_in _address;
		int _isListening;
};

std::vector<Socket> getSockets(std::vector<Server> &servers, std::vector<Socket> &sockets);

#endif