#include "Includes/HandleBoardElems.hpp"

HandleBoardElems::HandleBoardElems()
{
}

HandleBoardElems::HandleBoardElems(const sf::Sprite & sprite)
{
    elem_sprite = sprite;
    is_on_board = false;
}

HandleBoardElems::~HandleBoardElems()
{
}
