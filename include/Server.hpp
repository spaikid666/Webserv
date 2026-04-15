#ifndef SERVER_HPP
#define SERVER_HPP

#include "mainHeader.hpp"
#include "Location.hpp"

class Server
{
	public:
		Server();
		Server(const Server& other);
		Server& operator=(const Server& other);
		~Server(void);

		void setPort(const std::string& port);
		void setHost(const std::string& host);
		void setServerName(const std::string& svrName);
		void setMaxBody(const std::string& maxBody);
		void setErrorPage(const std::string& errPage);
		void setRoot(const std::string& root);
		void setIndex(const std::string& index);
		void setLocation(const Location& location);

		const std::string& getPort(void) const;
		const std::string& getHost(void) const;
		const std::string& getServerName(void) const;
		const long& getMaxBody(void) const;
		const std::string& getErrorPage(void) const;
		const std::string& getRoot(void) const;
		const std::string& getIndex(void) const;
		const std::vector<Location>& getLocations(void) const;


	private:
		std::string _port;
		std::string _host;
		std::string _svrName;
		long		_maxBody;
		std::string _errPage;
		std::string _root;
		std::string _index;
		std::vector<Location> _locations;
};

#endif