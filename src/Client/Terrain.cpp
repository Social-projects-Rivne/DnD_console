#include "Includes\Terrain.hpp"

Terrain::Terrain(std::string owner, std::string name, std::string width, std::string height, std::string description)
{
	this->_owner = owner;
	this->_name = name;
	this->_height = height;
	this->_width = width;
	this->_description = description;
}

void Terrain:: fShowTerrain()
{
	std::cout << "Name:" << _name << std::endl;
	std::cout << "Width:" << _width << std::endl;
	std::cout << "Height:" << _height << std::endl;
	std::cout << "Description:" << _description << std::endl;

}
json Terrain:: fTerrain_To_Json()
{
	json resualt;

	resualt["session_id"] = _owner;
	resualt["name"] = _name;
	resualt["width"] = _width;
	resualt["height"] = _height;
	resualt["description"] = _description;

	return resualt;
}