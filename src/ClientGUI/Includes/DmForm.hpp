#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "TerrainForm.hpp"
#include "NPCForm.hpp"
#include "BoardMenu.hpp"


class DMForm
{

    enum _selected_menu
    {
        NONE,
        TERRAIN_MENU,
        NPC_MENU,
        BOARD_MENU,
        BACK,
    };

    sf::Event _event;
    tgui::Gui _gui;

    HttpClient *_http_client;
    
    //UI elements
    tgui::Theme::Ptr    _theme;
    tgui::Picture::Ptr  _main;
    tgui::Picture::Ptr  _menu;
    tgui::Picture::Ptr  _logo;
    tgui::Button::Ptr   _btn_Terrain;
    tgui::Button::Ptr   _btn_NPC;
    tgui::Button::Ptr   _btn_Board;
    tgui::Button::Ptr   _btn_back; 

    std::string         _game_session;

    _selected_menu _menu_option;


    NPCForm *npc_menu_window;
    TerrainForm *terrain_menu_window;
    BoardMenu *board_menu;

    void fDisable();
    void fInitUIElements();

public:
    bool display_window;
    DMForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client);

    void fUpdate(sf::RenderWindow  &window);
    void fDraw(sf::RenderWindow & window);
};