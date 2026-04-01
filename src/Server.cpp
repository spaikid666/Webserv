#include "../include/mainHeader.hpp"

Server::Server () {}
Server::Server(const Server& other)
	: _port(other.getPort()), _host(other.getHost()), _svrName(other.getServerName()),
	  _maxBody(other.getMaxBody()), _errPage(other.getErrorPage()), 
	  _root(other.getRoot()), _index(other.getIndex())
	  //, _locations(other.getLocations()) 
{
}
Server& Server::operator=(const Server& other)
{
	if (this != &other)
	{
		_port = other.getPort();
		_host = other.getHost();
		_errPage = other.getErrorPage();
		_maxBody = other.getMaxBody();
		_svrName = other.getServerName();
		_root = other.getRoot();
		_index = other.getIndex();
		//_locations = other.getLocations();
	}
	return *this;
}
Server::~Server(void) {}





void Server::setPort(const std::string &port)
{
	_port = port;
}

void Server::setHost(const std::string &host)
{
	_host = host;
}

void Server::setServerName(const std::string &svrName)
{
	_svrName = svrName;
}

void Server::setMaxBody(const std::string &maxBody)
{
	if(maxBody[maxBody.size() - 1] == 'M')
	{
		std::string tmp = maxBody.substr(0, maxBody.size() - 1);
		_maxBody = std::atoi(tmp.c_str());
	}
	else
		_maxBody = std::atoi(maxBody.c_str());
}

void Server::setErrorPage(const std::string &errPage)
{
	_errPage = errPage;
}

void Server::setRoot(const std::string &root)
{
	_root = root;
}

void Server::setIndex(const std::string &index)
{
	_index = index;
}






const std::string &Server::getPort(void) const
{
	return _port;
}

const std::string& Server::getHost() const
{
	return _host;
}

const std::string &Server::getServerName(void) const
{
	return _svrName;
}

const long &Server::getMaxBody(void) const
{
	return _maxBody;
}

const std::string &Server::getErrorPage(void) const
{
	return _errPage;
}

const std::string &Server::getRoot(void) const
{
	return _root;
}

const std::string &Server::getIndex(void) const
{
	return _index;
}