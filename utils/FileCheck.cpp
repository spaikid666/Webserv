#include "../include/mainHeader.hpp"

bool fileNotEmpty(const std::string& filePath)
{
	int fd = open(filePath.c_str(), 0);
	if(fd < 0)
	{
		std::cerr << "[ERROR]: '" << filePath << "' doesn't exist or is not accessible." << std::endl;
		return FAIL;
	}
	char c;
	if(!read(fd, &c, 1))
	{
		std::cerr << "[ERROR]: The file '" << filePath << "' is empty." << std::endl;
		return FAIL;
	}
	close(fd);
	return SUCCESS;
}

bool fileExtension(const std::string& filePath, std::string ext)
{
	if (filePath.size() < 5 || filePath.substr(filePath.size() - 5) != ext)
	{
		std::cerr << "[ERROR]: The extension '" << ext << "' from '" << filePath << "' is not supported, try '.conf'." << std::endl;
		return FAIL;
	}
	return SUCCESS;
}

bool checkFile(const std::string& filePath)
{
	if(!fileNotEmpty(filePath))
		return FAIL;
	if(!fileExtension(filePath, ".conf"))
		return FAIL;
	return SUCCESS;
}