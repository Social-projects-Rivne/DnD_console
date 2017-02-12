#include "BoardCreate.hpp"

void BoardCreate::fSubmit(BoardCreate* o)
{
    if (o->_board_height->getText().toAnsiString() != "" &&
        o->_board_width->getText().toAnsiString() != "")
    {
        o->_board_json["name"] = o->_board_name->getText().toAnsiString();
        o->_board_json["height"] = o->_board_height->getText().toAnsiString();
        o->_board_json["width"] = o->_board_width->getText().toAnsiString();
        std::cout << std::setw(2) << o->_board_json;
        o->display_window = false;
    }

}

BoardCreate::BoardCreate(const sf::Event &event, sf::RenderWindow & window)
{
    display_window = true;
    this->_event = event;
    gui.setWindow(window);

    std::cout << "Start";

    theme = tgui::Theme::create("sprites/Theme/Black.txt");
    _board_name = theme->load("EditBox");
    _board_name->setSize(300, 50);
    _board_name->setDefaultText("Board name");

    _board_height = theme->load("EditBox");
    _board_height->setSize(300, 50);
    _board_height->setPosition(0, 55);
    _board_height->setDefaultText("Board height");
    _board_height->setInputValidator("^[1-9]$|^[1-2]\\d$|^3[0-2]$");

    _board_width = theme->load("EditBox");
    _board_width->setSize(300, 50);
    _board_width->setPosition(0, 110);
    _board_width->setDefaultText("Board width");
    _board_width->setInputValidator("^[1-9]$|^[1-2]\\d$|^3[0-2]$");


    _submit_btn = theme->load("Button");
    _submit_btn->setText("Submit");
    _submit_btn->setTextSize(16);
    _submit_btn->setSize(150, 50);
    _submit_btn->setPosition(75, 165);
    
    _submit_btn->connect("pressed", BoardCreate::fSubmit, this);

    gui.add(_board_name);
    gui.add(_board_height);
    gui.add(_board_width);
    gui.add(_submit_btn);
}

void BoardCreate::fUpdate(sf::RenderWindow & window)
{
    while (window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            window.close();
        gui.handleEvent(_event);
    }
}

void BoardCreate::fDraw(sf::RenderWindow & window)
{
      gui.draw();
}
