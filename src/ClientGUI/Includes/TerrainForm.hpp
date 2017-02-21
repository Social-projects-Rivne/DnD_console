#pragma once 

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "UserActions.hpp"
#include "HttpClient.hpp"

class TerrainForm
{
    sf::Event _event;
    tgui::Gui _gui;

    HttpClient *_http_client;

    // UI elements
    tgui::Theme::Ptr   _theme;
    tgui::EditBox::Ptr _terrain_name;
    tgui::EditBox::Ptr _terrain_type;
    tgui::EditBox::Ptr _terrain_width;
    tgui::EditBox::Ptr _terrain_height;
    tgui::EditBox::Ptr _terrain_description;
    tgui::ListBox::Ptr _terrain_list;
    tgui::Button::Ptr  _create_btn;
    tgui::Button::Ptr  _back_btn;
    tgui::Button::Ptr  _refresh_btn;
    
    tgui::Picture::Ptr _back;

    std::string _game_session;
    json _terrain_data;
    
    bool _updated;
    bool create_button_click;

    void fInitUIElements();
    void fCreateTerrain(tgui::EditBox::Ptr name, tgui::EditBox::Ptr type, tgui::EditBox::Ptr width, tgui::EditBox::Ptr height, tgui::EditBox::Ptr description);
    void fLoadNPCListBox();
    void fRefresh();
    void fDisable();
public:
    bool display_window;
    TerrainForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client);
    void fUpdate(sf::RenderWindow  &window);
    void fDraw(sf::RenderWindow & window);
};