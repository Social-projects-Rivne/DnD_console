#pragma once

#include <json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;

class Terrain
{
	std::string _owner;
	std::string _name;
	std::string _width;
	std::string _height;
	std::string _description;

public:
	Terrain(std::string owner, std::string name, std::string width, std::string height, std::string description)
	{
		this->_owner = owner;
		this->_name = name;
		this->_height = height;
		this->_width = width;
		this->_description = description;
	}

	void fShowTerrain()
	{
		std::cout << "Name:" << _name << std::endl;
		std::cout << "Width:" << _width << std::endl;
		std::cout << "Height:" << _height << std::endl;
		std::cout << "Description:" << _description << std::endl;

	}
	json fTerrain_To_Json()
	{
		json resualt;

		resualt["session_id"] = _owner;
		resualt["name"] = _name;
		resualt["width"] = _width;
		resualt["height"] = _height;
		resualt["description"] = _description;

		return resualt;
	}
};