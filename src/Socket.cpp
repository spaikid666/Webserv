#include "../include/mainHeader.hpp"

Socket::Socket(std::string host, std::string port)
{
    memset(&_address, 0, sizeof(_address));
    _address.sin_family = AF_INET;
	_address.sin_addr.s_addr = inet_addr(host.c_str());
    _address.sin_port = htons(std::atoi(port.c_str()));
}

Socket::Socket(const Socket &other)
{
    this->_socketFD = other._socketFD;
    this->_host = other._host;
    this->_port = other._port;
    this->_address = other._address;
    this->_isListening = other._isListening;
}

Socket& Socket::operator=(const Socket &other)
{
    if (this != &other)
    {
        this->_socketFD = other._socketFD;
        this->_host = other._host;
        this->_port = other._port;
        this->_address = other._address;
        this->_isListening = other._isListening;
    }
    return *this;
}

Socket::~Socket() {}





void Socket::setSocketFD(const int &socketFD)
{
    this->_socketFD = socketFD;
}

void Socket::setHost(const std::string &host)
{
    this->_host = host;
}

void Socket::setPort(const std::string &port)
{
    this->_port = port;
}

void Socket::setAddress(const sockaddr_in &address)
{
    this->_address = address;
}




const int &Socket::getSocketFD() const
{
    return this->_socketFD;
}

const std::string &Socket::getHost() const
{
    return this->_host;
}

const std::string &Socket::getPort() const
{
    return this->_port;
}

const sockaddr_in &Socket::getAddress() const
{
    return this->_address;
}

const int &Socket::getIsListening() const
{
    return this->_isListening;
}