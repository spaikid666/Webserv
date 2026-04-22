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

void Client::setRawRequest(const std::string &rawRequest)
{
	this->_rawRequest = rawRequest;
}






int Client::getClientFD()
{
	return this->_clientFD;
}

std::string Client::getClientRawRequest()
{
	return this->_rawRequest;
}





bool Client::appendRequest(const char *request, size_t bytes)
{
	std::string temp = this->getClientRawRequest();
	temp.append(request, bytes);
	
	this->setRawRequest(temp);
	if (this->_rawRequest.find("\r\n\r\n") != std::string::npos)
		return SUCCESS;
	return FAIL;
}
