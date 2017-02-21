#include "Includes/DmForm.hpp"


void DMForm::fClickedNpC()
{
    _npc_button_click = true;
}
void DMForm::fClickedTerrain()
{
    _terrain_button_click = true;
}

void DMForm::fDisable()
{
    display_window = false;
}

void DMForm::fInitUIElements()
{
    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    _theme = std::make_shared<tgui::Theme>("Interface/Game.txt");
    _main = std::make_shared<tgui::Picture>("Interface/MainMenu.png");
    _main->setSize(tgui::bindMax(1280, windowWidth), tgui::bindMax(800, windowHeight));
    _gui.add(_main);

    _menu = std::make_shared<tgui::Picture>("Interface/MenuWindow.png");
    _menu->setPosition(100, 180);
    _menu->setSize(372, 582);
    _gui.add(_menu);

    _logo = std::make_shared<tgui::Picture>("Interface/logo.png");
    _logo->setPosition(100, 100);
    _logo->setSize(372, 122);
    _gui.add(_logo);
    _btn_Terrain = _theme->load("Button");
    _btn_Terrain->setSize(275, 50);
    _btn_Terrain->setPosition(145, 270);
    _btn_Terrain->setText("Terrain menu");
    _gui.add(_btn_Terrain);

    _btn_NPC = _theme->load("Button");
    _btn_NPC->setSize(275, 50);
    _btn_NPC->setPosition(145, 350);
    _btn_NPC->setText("NPC menu");
    _gui.add(_btn_NPC);

    _btn_back = _theme->load("Button");
    _btn_back->setSize(275, 50);
    _btn_back->setPosition(145, 430);
    _btn_back->setText("Back");
    _gui.add(_btn_back);

    _btn_back->connect("pressed", &DMForm::fDisable, this);
    _btn_NPC->connect("pressed", &DMForm::fClickedNpC, this);
    _btn_Terrain->connect("pressed", &DMForm::fClickedTerrain, this);
}


DMForm::DMForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client)
{
    display_window = true;
    _game_session = game_session;
    _http_client = http_client;
    _gui.setWindow(window);
    _menu_option = NONE;
    fInitUIElements();
    this->_event = event;
}

void DMForm::fUpdate(sf::RenderWindow  &window)
{
    switch (_menu_option)
    {
    case DMForm::NONE:
    {
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                window.close();

            if (_npc_button_click)
            {
                npc_menu_window = new NPCForm(_event, window, _game_session, _http_client);
                _menu_option = DMForm::NPC_MENU;
            }

            if (_terrain_button_click)
            {
                terrain_menu_window = new TerrainForm(_event, window, _game_session, _http_client);
                _menu_option = DMForm::TERRAIN_MENU;
            }
            _gui.handleEvent(_event);
        }
    }
    break;
    case DMForm::TERRAIN_MENU:
    {
        terrain_menu_window->fUpdate(window);
    }
    break;
    case DMForm::NPC_MENU:
    {
        npc_menu_window->fUpdate(window);
    }
    break;
    case DMForm::BACK:
        break;
    }
}
void DMForm::fDraw(sf::RenderWindow & window)
{
    switch (_menu_option)
    {
    case DMForm::NONE:
    {
        _gui.draw();
    }
    break;
    case DMForm::NPC_MENU:
    {
        if (npc_menu_window->display_window)
            npc_menu_window->fDraw(window);
        else
        {
            delete npc_menu_window;
            _menu_option = DMForm::NONE;
            _npc_button_click = false;
        }
    }
    break;
    case DMForm::TERRAIN_MENU:
    {
        if (terrain_menu_window->display_window)
            terrain_menu_window->fDraw(window);
        else
        {
            delete terrain_menu_window;
            _menu_option = DMForm::NONE;
            _terrain_button_click = false;
        }
    }
    break;
    }
}
