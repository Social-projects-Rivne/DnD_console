

#include "IniParser.hpp"

IniParser::IniParser(std::string path) : _path(path)
{
}

std::map<std::string, std::string> IniParser::fGetParams()
{
	std::ifstream file(_path.c_str());
	std::string buff;
	std::string res = "";
	std::string category_name;
	std::string insert;
	std::string key;
	std::string value;
	bool isKey = true;

	for (int i = 0; std::getline(file, buff); ++i)
	{
		insert = "";
		if (buff[0] == '[')
		{
			category_name = "";
			for (int ch = 1; ch < buff.length()-1; ch++)
				category_name+=buff[ch];

			category_name += ".";
			continue;
		}

		insert = category_name + buff;
		key = "";
		value = "";
		for (int j = 0; j < insert.length(); j++)
		{
			if(insert[j] == ' ') continue;
			if(insert[j] == '=')
			{
				isKey = false;
				continue;
			}
			if(isKey)
				key+=insert[j];
			else
				value+=insert[j];
		}
		isKey = true;
		_params.insert({key, value});
	}

	file.close();
	return _params;
}


void IniParser::fSetParams(std::map<std::string, std::string> params)
{
	std::fstream file(_path.c_str());
	std::string map_category_name;
	std::string tmp_key;
	std::string key;
	std::string value;
	bool category_flag = true;


	if (file.is_open())
	{
		for (auto &el : params)
		{
			tmp_key = el.first;
			key = "";
			map_category_name = "";
			value = el.second;

			for (int i = 0; i < tmp_key.length(); i++)
			{
				if (tmp_key[i] == '.')
				{
					category_flag = false;
					continue;
				}
				if (category_flag)
					map_category_name+=tmp_key[i];
				else
					key+=tmp_key[i];
			}

			file << key << " = " << value << "\n";
		}
	}
	else
		std::cout << "An error occurred in file opening" << std ::endl;


	file.close();
}


IniParser::~IniParser()
{
	// TODO Auto-generated destructor stub
}

