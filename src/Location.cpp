#include "../include/mainHeader.hpp"

Location::Location () {}
Location::Location (const Location& other) :
		_path(other.getPath()),
		_allowMethods(other.getAllowedMethods()),
		_root(other.getRoot()),
		_returnCode(other.getReturnCode()),
		_returnPath(other.getReturnPath()),
		_autoindex(other.getAutoindex()),
		_upload(other.getUpload()),
		_maxBody(other.getMaxBody()),
		_cgiExt(other.getCgiExt()),
		_cgiPath(other.getCgiPath())
{}
Location& Location::operator=(const Location& other)
{
	if (this != &other)
	{
		_path = other.getPath();
		_allowMethods = other.getAllowedMethods();
		_root = other.getRoot();
		_returnCode = other.getReturnCode();
		_returnPath = other.getReturnPath();
		_autoindex = other.getAutoindex();
		_upload = other.getUpload();
		_maxBody = other.getMaxBody();
		_cgiExt = other.getCgiExt();
		_cgiPath = other.getCgiPath();
	}
	return *this;
}
Location::~Location () {}





void Location::setPath(const std::string& path)
{
	_path = path;
}

void Location::setAllowedMethods(const std::vector<std::string>& methods)
{
	_allowMethods = methods;
}

void Location::setRoot(const std::string& root)
{
	_root = root;
}

void Location::setReturnCode(const int& rcode)
{
	_returnCode = rcode;
}

void Location::setReturnPath(const std::string& rpath)
{
	_returnPath = rpath;
}

void Location::setAutoindex(const bool& autoindex)
{
	_autoindex = autoindex;
}

void Location::setUpload(const std::string& upload)
{
	_upload = upload;
}

void Location::setMaxBody(const std::string& maxBody)
{
	if(maxBody[maxBody.size() - 1] == 'M')
	{
		std::string tmp = maxBody.substr(0, maxBody.size() - 1);
		_maxBody = std::atoi(tmp.c_str());
	}
	else
		_maxBody = std::atoi(maxBody.c_str());
}

void Location::setCgiExt(const std::string& ext)
{
	_cgiExt = ext;
}

void Location::setCgiPath(const std::string& cpath)
{
	_cgiPath = cpath;
}





const std::string& Location::getPath() const
{
	return _path;
}

const std::vector<std::string>& Location::getAllowedMethods() const
{
	return _allowMethods;
}

const std::string& Location::getRoot() const
{
	return _root;
}

const int& Location::getReturnCode() const
{
	return _returnCode;
}

const std::string& Location::getReturnPath() const
{
	return _returnPath;
}

const bool& Location::getAutoindex() const
{
	return _autoindex;
}

const std::string& Location::getUpload() const
{
	return _upload;
}

const std::string& Location::getMaxBody() const
{
	return _maxBody;
}

const std::string& Location::getCgiExt() const
{
	return _cgiExt;
}

const std::string& Location::getCgiPath() const
{
	return _cgiPath;
}