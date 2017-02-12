#pragma once
#include <TGUI/TGUI.hpp>

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

public:
    bool display_window;

    BoardCreate(const sf::Event &event, sf::RenderWindow &window);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);

};

