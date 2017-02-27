#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "UserActions.hpp"
#include "HttpClient.hpp"

class CharacterForm
{
    sf::Event _event;
    tgui::Gui _gui;
    HttpClient *_http_client;


    //UI elements 
    tgui::Theme::Ptr    _theme;
    tgui::EditBox::Ptr  _character_name;
    tgui::EditBox::Ptr  _character_race;
    tgui::EditBox::Ptr  _character_class;
    tgui::ComboBox::Ptr _strength;
    tgui::ComboBox::Ptr _dexterity;
    tgui::ComboBox::Ptr _constitution;
    tgui::ComboBox::Ptr _inteligence;
    tgui::ComboBox::Ptr _wisdom;
    tgui::ComboBox::Ptr _charisma;
    tgui::Label::Ptr    _strength_l;
    tgui::Label::Ptr    _dexterity_l;
    tgui::Label::Ptr    _constitution_l;
    tgui::Label::Ptr    _inteligence_l;
    tgui::Label::Ptr    _wisdom_l;
    tgui::Label::Ptr    _charisma_l;
    tgui::ListBox::Ptr  _character_list;
    tgui::Button::Ptr   _create_btn;
    tgui::Button::Ptr   _back_btn;
    tgui::Button::Ptr   _refresh_btn;
    tgui::Picture::Ptr  _back;

    std::string _data_strength;
    std::string _data_dexterity;
    std::string _data_constitution;
    std::string _data_intelligence;
    std::string _data_wisdom;
    std::string _data_charisma;
    
    
    std::string _game_session;
    json _character_data;
    
    bool _updated;
    bool _combo_box;
    bool _create_button_click;

    void fInitUIElements();
    void fCreateCharacter(tgui::EditBox::Ptr name, tgui::EditBox::Ptr _class, tgui::EditBox::Ptr race);

    void fLoadCharacterListBox();
    void fRefresh();
    void fDisable();
public:
    bool display_window;
    CharacterForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client);
    void fUpdate(sf::RenderWindow  &window);
    void fDraw(sf::RenderWindow & window);
};
