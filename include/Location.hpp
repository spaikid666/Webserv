#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "mainHeader.hpp"

class Location
{
	public:
		Location();
		Location(const Location& other);
		Location& operator=(const Location& other);
		~Location();

		void setPath(const std::string& path);
		void setAllowedMethods(const std::vector<std::string>& methods);
		void setRoot(const std::string& root);
		void setReturnCode(const int& rcode);
		void setReturnPath(const std::string& rpath);
		void setAutoindex(const bool& autoindex);
		void setUpload(const std::string& upload);
		void setMaxBody(const std::string& upload);
		void setCgiExt(const std::string& ext);
		void setCgiPath(const std::string& cpath); 

		const std::string& getPath() const;
		const std::vector<std::string>& getAllowedMethods() const;
		const std::string& getRoot() const;
		const int& getReturnCode() const;
		const std::string& getReturnPath() const;
		const bool& getAutoindex() const;
		const std::string& getUpload() const;
		const std::string& getMaxBody() const;
		const std::string& getCgiExt() const;
		const std::string& getCgiPath() const;

	private:
		std::string _path;
		std::vector<std::string> _allowMethods;
		std::string _root;
		int			_returnCode;
		std::string _returnPath;
		bool		_autoindex;
		std::string _upload;
		std::string _maxBody;
		std::string _cgiExt;
		std::string _cgiPath;
};




#endif