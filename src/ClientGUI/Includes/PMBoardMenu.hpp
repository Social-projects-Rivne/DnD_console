#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "PMPlayBoard.hpp" 
#include "HttpClient.hpp"
#include "json.hpp"

using json = nlohmann::json;

class PMBoardMenu
{
private:

    enum MenuOption
    {
        NONE,
        PLAY
    };
    MenuOption _selected_option;

    // TGUI
    tgui::Gui          _gui;
    tgui::Theme::Ptr   _theme;
    tgui::ListBox::Ptr _board_list;
    tgui::ListBox::Ptr _char_list;
    int                _selected_board;
    int                _selected_char;
    //

    //Http Client
    HttpClient *_http_client;
    //

    // game session
    std::string _session_id;
    //
    int count;
    //Buttons
    sf::Font    _font;
    sf::Texture _back_btn_tex;
    sf::Texture _play_btn_tex;
    sf::Sprite  _back_btn_spr;
    sf::Sprite  _play_btn_spr;
    sf::Text    _back_btn_txt;
    sf::Text    _play_btn_txt;
    //

    //sfml event
    sf::Event _event;
    //

    //Load data thread
    sf::Thread _load_thread;
    bool       _is_loaded;
    json       _board_data;
    json       _user_characters;
    //


    PMPlayBoard* _play_board;

    void fLoadUi(sf::RenderWindow &window);
    void fLoadData();

public:
    bool draw_window;

    PMBoardMenu(const sf::Event &_event,
        sf::RenderWindow &window,
        HttpClient* cl,
        const std::string &session);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);
};

