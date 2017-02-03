#include "Includes/Board.hpp"
#include "Includes/DataValidator.hpp"
#include <iostream>

Board::Board()
{
}

Board::Board(const std::string &name, const std::string &length, const std::string &width)
            : _name(name), _length(length), _width(width)
{
}

Board::~Board()
{
}

void Board::fCreate()
{

}

json Board::fToJson()
{
    json board;

    board["name"]   = _name;
    board["length"] = _length;
    board["width"]  = _width;

    return board;
}


