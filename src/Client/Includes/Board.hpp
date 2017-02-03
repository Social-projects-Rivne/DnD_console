#pragma once
#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <string>
#include "json.hpp"
using json = nlohmann::json;

class Board
{
private:
    std::string _length;
    std::string _width;
    std::string _name;

public:
    Board();
    Board(const std::string &name, const std::string &length, const std::string &width);
    virtual ~Board();
    void fCreate();

    json fToJson();

};

#endif // !__BOARD_HPP__