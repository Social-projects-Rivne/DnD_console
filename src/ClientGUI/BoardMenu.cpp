#include "Includes/BoardMenu.hpp"
#include "Includes/BoardEdit.hpp"

BoardMenu::BoardMenu(const sf::Event & event, sf::RenderWindow &window, HttpClient* client, const std::string &ses) :
                                            http_thread(&BoardMenu::fLoadBoardListBox, this)
{
    draw_window = true;
    _session_id = ses;
    this->_event = event;
    _gui.setWindow(window);
    _board_id = -1;
    fLoadUiElements(window);
    _client = client;
    updated = true;
    try
    {
        //http_thread = new sf::Thread(&BoardMenu::fLoadBoardListBox, this);
        http_thread.launch();
        //fLoadBoardListBox();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    _menu_option = _selected_menu::NONE;
}

void BoardMenu::fUpdate(sf::RenderWindow & window)
{
    switch (_menu_option)
    {
    case BoardMenu::NONE:
    {
        try
        {
            if (_board_data["status"] == "success" && !updated)
            {
                std::string quan = _board_data["boards_quantity"];
                for (int i = 0; i < std::stoi(quan); i++)
                {
                    _list_of_board->addItem(_board_data["list"][i]["board"], std::to_string(i));
                }
                updated = true;
            }
        }
        catch (const std::exception&)
        {

        }
        while (window.pollEvent(_event))
        {

            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                window.close();

            if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
            {
                if (_back_btn_spr.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    http_thread.terminate();
                    draw_window = false;
                }


                if (_board_edit_btn_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    if (_board_id >= 0)
                    {
                        _menu_option = _selected_menu::EDIT_BOARD;
                        std::string height = _board_data["list"][_board_id]["height"];
                        std::string width  = _board_data["list"][_board_id]["width"];
                        std::string id     = _board_data["list"][_board_id]["id"];
                        edit_board = new BoardEdit(std::stoi(height),
                        		                   std::stoi(width),
												   id,
												   _event,
												   window,
												   _client,
                                                   _session_id);
                    }
                }

                if (_create_board_btn_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    _menu_option = _selected_menu::CREATE_BOARD;
                    create_board = new BoardCreate(_event, window, _client, _session_id);
                }


                if (_refresh_list_btn_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    _list_of_board->removeAllItems();
                    http_thread.launch();
                    //fLoadBoardListBox();
                }

                if (_list_of_board->getPosition().x <= _event.mouseButton.x &&
                    _list_of_board->getPosition().x + _list_of_board->getSize().x >= _event.mouseButton.x &&
                    _list_of_board->getPosition().y <= _event.mouseButton.y &&
                    _list_of_board->getPosition().y + _list_of_board->getSize().y >= _event.mouseButton.y)
                {
                    std::string tmp = _list_of_board->getSelectedItemId().toAnsiString();
                    try
                    {
                        _board_id = std::stoi(tmp);
                    }
                    catch (const std::exception&)
                    {
                        _board_id = -1;
                    }
                    std::cout << tmp;
                }

            }
            _gui.handleEvent(_event);
        }
    }
    break;
    case BoardMenu::CREATE_BOARD:
    {
        create_board->fUpdate(window);
    }
        break;
    case BoardMenu::EDIT_BOARD:
    {
        edit_board->fUpdate(window);
    }
    break;
    case BoardMenu::BACK:
        break;
    }
}

void BoardMenu::fDraw(sf::RenderWindow & window)
{
    switch (_menu_option)
    {
    case BoardMenu::NONE:
    {
        if (_board_id >= 0)
        {
            window.draw(_board_edit_btn_sprite);
            window.draw(_board_edit_txt);
        }
        window.draw(_refresh_list_btn_sprite);
        window.draw(_refresh_list_txt);
        window.draw(_create_board_btn_sprite);
        window.draw(_create_board_txt);
        window.draw(_back_btn_spr);
        window.draw(_back_btn_txt);
        _gui.draw();
    }
    break;
    case BoardMenu::CREATE_BOARD:
    {
        if (create_board->display_window)
            create_board->fDraw(window);
        else
        {
            delete create_board;
            _menu_option = BoardMenu::NONE;
        }
    }
        break;
    case BoardMenu::EDIT_BOARD:
    {
        if (edit_board->draw_window)
            edit_board->fDraw(window);
        else
        {
            try
            {
               delete edit_board;
            }
            catch (const std::exception& e)
            {
                std::cout << "Exception: " << e.what();
            }
            _menu_option = BoardMenu::NONE;
        }
    }
        break;
    case BoardMenu::BACK:
    {

    }
        break;
    }

}

void BoardMenu::fLoadUiElements(sf::RenderWindow & window)
{
    font.loadFromFile("arial.ttf");

    _board_edit_txt.setString("Edit board");
    _board_edit_txt.setCharacterSize(20);
    _board_edit_txt.setFont(font);

    _create_board_txt.setString("Create board");
    _create_board_txt.setCharacterSize(20);
    _create_board_txt.setFont(font);

    _refresh_list_txt.setString("Refresh List");
    _refresh_list_txt.setCharacterSize(20);
    _refresh_list_txt.setFont(font);

    _back_btn_txt.setString("Back");
    _back_btn_txt.setCharacterSize(20);
    _back_btn_txt.setFont(font);


    _board_edit_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _board_edit_btn_sprite.setTexture(_board_edit_btn);

    _create_board_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _create_board_btn_sprite.setTexture(_create_board_btn);

    _refresh_list_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _refresh_list_btn_sprite.setTexture(_refresh_list_btn);

    _back_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _back_btn_spr.setTexture(_back_btn);
    _back_btn_spr.setScale(0.5, 1);

    int wind_center_x = window.getSize().x;

    _board_edit_btn_sprite.setPosition(wind_center_x - (_board_edit_btn_sprite.getGlobalBounds().width + 10),
        _board_edit_btn_sprite.getGlobalBounds().height);

    _create_board_btn_sprite.setPosition(_board_edit_btn_sprite.getPosition().x,
        _board_edit_btn_sprite.getPosition().y + _create_board_btn_sprite.getGlobalBounds().height + 10);
    _refresh_list_btn_sprite.setPosition(0, 425);
    _refresh_list_txt.setPosition(100, 435);

    _back_btn_spr.setPosition(0, window.getSize().y - _back_btn_spr.getGlobalBounds().height);

    _board_edit_txt.setPosition(_board_edit_btn_sprite.getPosition().x +
        _board_edit_btn_sprite.getGlobalBounds().width / 2 -
        _board_edit_txt.getGlobalBounds().width / 2,
        _board_edit_btn_sprite.getPosition().y +
        _board_edit_btn_sprite.getGlobalBounds().height / 2 -
        _board_edit_txt.getGlobalBounds().height);

    _create_board_txt.setPosition(_create_board_btn_sprite.getPosition().x +
        _create_board_btn_sprite.getGlobalBounds().width / 2 -
        _create_board_txt.getGlobalBounds().width / 2,
        _create_board_btn_sprite.getPosition().y +
        _create_board_btn_sprite.getGlobalBounds().height / 2 -
        _create_board_txt.getGlobalBounds().height);

    _back_btn_txt.setPosition(_back_btn_spr.getPosition().x +
        _back_btn_spr.getGlobalBounds().width / 2 -
        _back_btn_txt.getGlobalBounds().width / 2,
        _back_btn_spr.getPosition().y +
        _back_btn_spr.getGlobalBounds().height / 2 -
        _back_btn_txt.getGlobalBounds().height);


    _theme = tgui::Theme::create("sprites/Theme/Black.txt");
    _list_of_board = _theme->load("ListBox");
    _list_of_board->setSize(300, 400);
    _gui.add(_list_of_board);
}

void BoardMenu::fLoadBoardListBox()
{
    //
    std::string response;
    //auto q = "{\"session_id\":\"1\", \"board\":\"temp5\", \"width\":\"15\", \"height\":\"15\", \"description\":\"desc\"}";
    auto request = "{\"session_id\":\""+_session_id+"\"}";
    _client->fSendRequest(HttpClient::_POST, "/api/loadmyboardslist", request);
    _client->fGetResponse(response);
    _board_data = json::parse(response);
    std::cout << _board_data;
    updated = false;
}
