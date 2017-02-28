#include "Includes/MeinMenuForm.hpp"


void MeinMenuForm::fInitUIElements()
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

    _btn_player = _theme->load("Button");
    _btn_player->setSize(275, 50);
    _btn_player->setPosition(145, 270);
    _btn_player->setText("Player mode");
    _gui.add(_btn_player);

    _btn_dm = _theme->load("Button");
    _btn_dm->setSize(275, 50);
    _btn_dm->setPosition(145, 350);
    _btn_dm->setText("DM mode");
    _gui.add(_btn_dm);

    _btn_exit = _theme->load("Button");
    _btn_exit->setSize(275, 50);
    _btn_exit->setPosition(145, 430);
    _btn_exit->setText("Exit");
    _gui.add(_btn_exit);

    _btn_player->connect("pressed", &MeinMenuForm::fPlayerMode_clicked, this);
    _btn_dm->connect("pressed", &MeinMenuForm::fDM_Mode_clicked, this);
    _btn_exit->connect("pressed", &MeinMenuForm::fExit_clicked, this);
}
void MeinMenuForm::fPlayerMode_clicked()
{
    _player_m_button_click = true;
}

void MeinMenuForm::fDM_Mode_clicked()
{
    _dm_m_button_click = true;
}

void MeinMenuForm::fExit_clicked()
{
    _exit_m_button_click = true;
}

MeinMenuForm::MeinMenuForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client)
{

    display_window = true;
    _menu_option = NONE;
    _player_m_button_click = false;
    _dm_m_button_click = false;
    _http_client = http_client;
    this->_game_session = game_session;
   // window.create(sf::VideoMode(1280, 800), "Dungeons & Dragons");
    _gui.setWindow(window);
    this->_event = event;
    fInitUIElements();

}
void MeinMenuForm::fUpdate(sf::RenderWindow  &window)
{
    switch (_menu_option)
    {
    case MeinMenuForm::NONE:
    {
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed || _exit_m_button_click)
                window.close();

            if (_dm_m_button_click)
            {
                dm_window = new DMForm(_event, window, _game_session, _http_client);
                _menu_option = DM_MODE;
            }
            if (_player_m_button_click)
            {
                _menu_option = PLAYER_MODE;

                character_window = new CharacterForm(_event, window, _game_session, _http_client);
            }


            _gui.handleEvent(_event);
        }
    }
    break;
    case MeinMenuForm::PLAYER_MODE:
    {
        character_window->fUpdate(window);
    }
    break;
    case MeinMenuForm::DM_MODE:
    {
        dm_window->fUpdate(window);
    }
    break;
    case MeinMenuForm::EXIT:
        break;
    }
}

void MeinMenuForm::fDraw(sf::RenderWindow & window)
{
    switch (_menu_option)
    {
    case MeinMenuForm::NONE:
    {
        _gui.draw();
    }
    break;
    case MeinMenuForm::PLAYER_MODE:
    {
        if (character_window->display_window)
            character_window->fDraw(window);
        else
        {
            delete character_window;
            _menu_option = MeinMenuForm::NONE;
            _player_m_button_click = false;
        }
    }
    break;
    case MeinMenuForm::DM_MODE:
    {
        if (dm_window->display_window)
            dm_window->fDraw(window);
        else
        {
            delete dm_window;
            _menu_option = MeinMenuForm::NONE;
            _dm_m_button_click = false;
        }
    }
    break;
    case MeinMenuForm::EXIT:
    {

    }
    break;
    }
}