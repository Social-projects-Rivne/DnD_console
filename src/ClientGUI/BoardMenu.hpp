#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>
#include "BoardEdit.hpp"
#include "BoardCreate.hpp"
#include "HttpClient.hpp"

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

    sf::Thread http_thread;

    sf::Event _event;
    tgui::Gui _gui;

    //UI elems
    tgui::ListBox::Ptr _list_of_board;
    tgui::Theme::Ptr   _theme;

    sf::Texture _back_btn;
    sf::Texture _board_edit_btn;
    sf::Texture _create_board_btn;
    sf::Texture _refresh_list_btn;

    sf::Sprite  _back_btn_spr;
    sf::Sprite  _board_edit_btn_sprite;
    sf::Sprite  _create_board_btn_sprite;
    sf::Sprite  _refresh_list_btn_sprite;

    //Buttons text
    sf::Font font;
    sf::Text _board_edit_txt;
    sf::Text _back_btn_txt;
    sf::Text _create_board_txt;
    sf::Text _refresh_list_txt;

    //Avail menu options
    BoardEdit*   edit_board;
    BoardCreate* create_board;
    HttpClient* _client;

    int _board_height;
    int _board_width;
    int _board_id;
    bool updated;
    json _board_data;

    _selected_menu _menu_option;

    void fLoadUiElements(sf::RenderWindow &window);
    void fLoadBoardListBox();
public:
    BoardMenu(const sf::Event &event, sf::RenderWindow &window, HttpClient* cl);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);
};

