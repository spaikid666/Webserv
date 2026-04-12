#include "../include/mainHeader.hpp"

bool fileNotEmpty(const std::string& filePath)
{
	int fd = open(filePath.c_str(), 0);
	if(fd < 0)
	{
		std::cerr << "[Error]: '" << filePath << "' doesn't exist or is not accessible." << std::endl;
		return false;
	}
	char c;
	if(!read(fd, &c, 1))
	{
		std::cerr << "[Error]: The file '" << filePath << "' is empty." << std::endl;
		return false;
	}
	close(fd);
	return true;
}

bool fileExtension(const std::string& filePath, std::string ext)
{
	if (filePath.size() < 5 || filePath.substr(filePath.size() - 5) != ext)
	{
		std::cerr << "[Error]: The extension '" << ext << "' from '" << filePath << "' is not supported, try '.conf'." << std::endl;
		return false;
	}
	return true;
}

bool checkFile(const std::string& filePath)
{
	if(!fileNotEmpty(filePath))
		return false;
	if(!fileExtension(filePath, ".conf"))
		return false;
	return true;
}