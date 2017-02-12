#pragma once
#include <SFML/Graphics.hpp>
#include "BoardEdit.hpp"
#include "BoardCreate.hpp"
class BoardMenu
{
private:
    enum _selected_menu 
    {
        NONE,
        CREATE_BOARD,
        EDIT_BOARD,
        BACK
    };

    sf::Event _event;

    //UI elems
    sf::Texture _back_btn;
    sf::Texture _board_edit_btn;
    sf::Texture _create_board_btn;

    sf::Sprite  _back_btn_spr;
    sf::Sprite  _board_edit_btn_sprite;
    sf::Sprite  _create_board_btn_sprite;

    //Buttons text
    sf::Font font;
    sf::Text _board_edit_txt;
    sf::Text _back_btn_txt;
    sf::Text _create_board_txt;

    //Avail menu options
    BoardEdit*   edit_board;
    BoardCreate* create_board;

    _selected_menu _menu_option;

    void fLoadUiElements(sf::RenderWindow &window);
public:
    BoardMenu(const sf::Event &event, sf::RenderWindow &window);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);
};

