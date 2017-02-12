#pragma once
#include <TGUI/TGUI.hpp>
#include "json.hpp"

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

    static void fSubmit(BoardCreate* obj);
    json _board_json;
public:

    bool display_window;

    BoardCreate(const sf::Event &event, sf::RenderWindow &window);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);

};

