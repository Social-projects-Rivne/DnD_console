#pragma once
#ifndef SRC_INIPARSER_HPP_
#define SRC_INIPARSER_HPP_

#include <iostream>
#include <fstream>
#include <map>
#include <string>


class IniParser
{
private:
	std::string _path;
	std::map<std::string, std::string> _params;
public:
	IniParser(std::string);
	std::map<std::string, std::string> fGetParams();
	void fSetParams(std::map<std::string, std::string>);

	virtual ~IniParser();
};

#endif /* SRC_INIPARSER_HPP_ */
