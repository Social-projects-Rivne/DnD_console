#include "BoardMenu.hpp"
#include "BoardEdit.hpp"

BoardMenu::BoardMenu(const sf::Event & event, sf::RenderWindow &window)
{
    this->_event = event;

    fLoadUiElements(window);

    _menu_option = _selected_menu::NONE;
}

void BoardMenu::fUpdate(sf::RenderWindow & window)
{
    switch (_menu_option)
    {
    case BoardMenu::NONE:
    {
        while (window.pollEvent(_event))
        {

            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                window.close();

            if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
            {
                if (_board_edit_btn_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    edit_board = new BoardEdit(10, 10, _event, window);
                    _menu_option = _selected_menu::EDIT_BOARD;
                }

                if (_create_board_btn_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    create_board = new BoardCreate(_event, window);
                    _menu_option = _selected_menu::CREATE_BOARD;
                }
            }
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
        window.draw(_board_edit_btn_sprite);
        window.draw(_create_board_btn_sprite);
        window.draw(_board_edit_txt);
        window.draw(_create_board_txt);
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
            delete edit_board;
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

    _board_edit_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _board_edit_btn_sprite.setTexture(_board_edit_btn);

    _create_board_btn.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _create_board_btn_sprite.setTexture(_create_board_btn);

    int wind_center_x = window.getSize().x / 2;

    _board_edit_btn_sprite.setPosition(wind_center_x - (_board_edit_btn_sprite.getGlobalBounds().width / 2),
        _board_edit_btn_sprite.getGlobalBounds().height);

    _create_board_btn_sprite.setPosition(_board_edit_btn_sprite.getPosition().x,
        _board_edit_btn_sprite.getPosition().y + _create_board_btn_sprite.getGlobalBounds().height + 10);


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
}