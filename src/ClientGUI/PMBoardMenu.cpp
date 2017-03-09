#include "Includes/PMBoardMenu.hpp"
#include "Includes/PMBoardMenu.hpp"

void PMBoardMenu::fLoadUi(sf::RenderWindow & window)
{
    _font.loadFromFile("arial.ttf");
    count = 0;
    _back_btn_tex.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _play_btn_tex.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    
    _back_btn_spr.setTexture(_back_btn_tex);
    _play_btn_spr.setTexture(_play_btn_tex);
    _back_btn_spr.setScale(0.5, 1);
    _play_btn_spr.setScale(0.5, 1);

    _back_btn_spr.setPosition(0, window.getSize().y - _back_btn_spr.getGlobalBounds().height);
    _play_btn_spr.setPosition(window.getSize().x - _play_btn_spr.getGlobalBounds().width,
                              window.getSize().y - _play_btn_spr.getGlobalBounds().height);

    _back_btn_txt.setString("Back");
    _play_btn_txt.setString("Play");
    _back_btn_txt.setCharacterSize(20);
    _play_btn_txt.setCharacterSize(20);
    _back_btn_txt.setFont(_font);
    _play_btn_txt.setFont(_font);

    _back_btn_txt.setPosition(_back_btn_spr.getPosition().x +
        _back_btn_spr.getGlobalBounds().width / 2 -
        _back_btn_txt.getGlobalBounds().width / 2,
        _back_btn_spr.getPosition().y +
        _back_btn_spr.getGlobalBounds().height / 2 -
        _back_btn_txt.getGlobalBounds().height);

    _play_btn_txt.setPosition(_play_btn_spr.getPosition().x +
        _play_btn_spr.getGlobalBounds().width / 2 -
        _play_btn_txt.getGlobalBounds().width / 2,
        _play_btn_spr.getPosition().y +
        _play_btn_spr.getGlobalBounds().height / 2 -
        _play_btn_txt.getGlobalBounds().height);

    _board_list = _theme->load("ListBox");
    _char_list  = _theme->load("ListBox");
    _board_list->setSize(window.getSize().x / 3.5, window.getSize().y / 1.5);
    _char_list->setSize(window.getSize().x / 3.5, window.getSize().y / 1.5);

    _board_list->setPosition(window.getSize().x / 2 - _board_list->getSize().x/2 - _board_list->getSize().x - 10,
                             window.getSize().y / 2 - _board_list->getSize().y / 2);

    _char_list->setPosition(window.getSize().x / 2 + _char_list->getSize().x/2 + 10,
                            window.getSize().y / 2 - _char_list->getSize().y / 2);

    _gui.add(_board_list);
    _gui.add(_char_list);
}



void PMBoardMenu::fLoadData()
{
    //"message": "list of your characters is empty",
    //"status" : "warning"
    try
    {
        std::string response;
        std::string request = "{\"session_id\":\"" + _session_id + "\"}";
        _http_client->fSendRequest(HttpClient::_POST, "/api/loadboardslist", request);
        _http_client->fGetResponse(response);
        _board_data = json::parse(response.c_str());
        response = "";
        _http_client->fSendRequest(HttpClient::_POST, "/api/loadmycharacterslist", request);
        _http_client->fGetResponse(response);
        _user_characters = json::parse(response.c_str());
        std::cout << std::setw(2) << _board_data << std::endl;
        std::cout << std::setw(2) << _user_characters << std::endl;
        _is_loaded = true;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

PMBoardMenu::PMBoardMenu(const sf::Event & _event, sf::RenderWindow & window, HttpClient* cl, const std::string & session)
                : _load_thread(&PMBoardMenu::fLoadData, this)
{
    this->_event = _event;
    this->_session_id = session;
    this->_http_client = cl;
    _gui.setWindow(window);
    _selected_board = -1;
    _selected_char  = -1;
    _is_loaded      = false;
    draw_window     = true;
    _theme = tgui::Theme::create("sprites/Theme/Black.txt");
    fLoadUi(window);
    _selected_option = PMBoardMenu::NONE;
    _load_thread.launch();
}

void PMBoardMenu::fUpdate(sf::RenderWindow & window)
{
    switch (_selected_option)
    {
    case PMBoardMenu::NONE:
    {
        if (draw_window)
        {
            if (_is_loaded)
            {
                if (_board_data["status"] == "warning")
                {
                    _board_list->addItem("Empty board list try again later or create new board", "-1");
                }
                if (_user_characters["status"] == "warning")
                {
                    _char_list->addItem("You have not created any charaters, please create and try again", "-1");
                }
                if (_board_data["status"] == "success")
                {
                    //"boards_quantity": "3",
                    std::string board_quan = _board_data["boards_quantity"];
                    for (int i = 0; i < std::stoi(board_quan); i++)
                    {
                        _board_list->addItem(_board_data["list"][i]["board"], std::to_string(i));
                    }
                }
                if (_user_characters["status"] == "success")
                {
                    std::string char_quan = _user_characters["character_quantity"];
                    for (int i = 0; i < std::stoi(char_quan); i++)
                    {
                        _char_list->addItem(_user_characters["list"][i]["character"], std::to_string(i));
                    }
                }
                _is_loaded = false;
            }

            while (window.pollEvent(_event))
            {
                if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
                {
                    if (_back_btn_spr.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                    {
                        _load_thread.terminate();
                        draw_window = false;
                    }

                    if (_play_btn_spr.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                    {
                        if (_selected_board > -1 && _selected_char > -1)
                        {
                            std::string height = _board_data["list"][_selected_board]["height"];
                            std::string width  = _board_data["list"][_selected_board]["width"];
                            std::string id     = _board_data["list"][_selected_board]["id"];
                            std::string ch_id  = _user_characters["list"][_selected_char]["character"];
                            _play_board = new PMPlayBoard(_event,
                                                          window,
                                                          _http_client,
                                                          _session_id,
                                                          std::stoi(width),
                                                          std::stoi(height),
                                                          id,
                                                          ch_id);
                            _selected_option = PMBoardMenu::PLAY;
                        }
                    }

                    if (_board_list->getPosition().x <= _event.mouseButton.x &&
                        _board_list->getPosition().x + _board_list->getSize().x >= _event.mouseButton.x &&
                        _board_list->getPosition().y <= _event.mouseButton.y &&
                        _board_list->getPosition().y + _board_list->getSize().y >= _event.mouseButton.y)
                    {
                        std::string tmp = _board_list->getSelectedItemId().toAnsiString();
                        try
                        {
                            _selected_board = std::stoi(tmp);
                        }
                        catch (const std::exception&)
                        {
                            _selected_board = -1;
                        }
                        std::cout << tmp;
                    }

                    if (_char_list->getPosition().x <= _event.mouseButton.x &&
                        _char_list->getPosition().x + _char_list->getSize().x >= _event.mouseButton.x &&
                        _char_list->getPosition().y <= _event.mouseButton.y &&
                        _char_list->getPosition().y + _char_list->getSize().y >= _event.mouseButton.y)
                    {
                        std::string tmp = _char_list->getSelectedItemId().toAnsiString();
                        try
                        {
                            _selected_char = std::stoi(tmp);
                        }
                        catch (const std::exception&)
                        {
                            _selected_char = -1;
                        }
                        std::cout << tmp;
                    }
                }

                _gui.handleEvent(_event);
            }
        }
    }
    break;
    case PMBoardMenu::PLAY:
    {
        if (_play_board->draw_window)
            _play_board->fUpdate(window);
    }
    break;
    }
}

void PMBoardMenu::fDraw(sf::RenderWindow & window)
{
    switch (_selected_option)
    {
    case PMBoardMenu::NONE:
    {
        if (draw_window)
        {
            window.draw(_back_btn_spr);
            window.draw(_back_btn_txt);

            if (_selected_board > -1 && _selected_char > -1)
            {
                window.draw(_play_btn_spr);
                window.draw(_play_btn_txt);
            }

            _gui.draw();
        }
    }
        break;
    case PMBoardMenu::PLAY:
    {
        if (_play_board->draw_window)
            _play_board->fDraw(window);
        else
        {
            try
            {
                std::cout << count << std::endl;
                delete _play_board;
                count++;
            }
            catch (const std::exception &e)
            {

            }
            _selected_option = PMBoardMenu::NONE;
        }
    }
        break;
    }
}
