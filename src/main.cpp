#include "../include/mainHeader.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "[ERROR]: Number of arguments invalid. Try: ./webserv [configuration file]" << std::endl;
		return 1;
	}

	ServerManager svrMan;

	if(!svrMan.setUpServers(argv[1]))
		return 1;

	if (!svrMan.initServer())
		return 1;

	return 0;
}