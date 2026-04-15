#include "../include/mainHeader.hpp"

Client::Client() {}

Client::Client(const Client &other)
{
	_clientFD = other._clientFD;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		_clientFD = other._clientFD;
	}
	return *this;
}

Client::~Client() {}




void Client::setClientFD(const int &clientFD)
{
	this->_clientFD = clientFD;
}




int Client::getClientFD()
{
	return this->_clientFD;
}