#pragma once
#include <TGUI/TGUI.hpp>
#include "json.hpp"
#include "HttpClient.hpp"

using json = nlohmann::json;

class BoardCreate
{
    sf::Event _event;
    tgui::Gui gui;
    

    tgui::Theme::Ptr theme;
    tgui::EditBox::Ptr _board_name;
    tgui::EditBox::Ptr _board_height;
    tgui::EditBox::Ptr _board_width;
    tgui::Button::Ptr  _submit_btn;
    tgui::Button::Ptr  _back_btn;

    HttpClient* _client;
    void fSubmit();
    json _board_json;
public:

    bool display_window;

    BoardCreate(const sf::Event &event, sf::RenderWindow &window, HttpClient* cl);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);

};

