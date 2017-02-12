#include "BoardCreate.hpp"

BoardCreate::BoardCreate(const sf::Event &event, sf::RenderWindow & window)
{
    display_window = true;
    this->_event = event;
    gui.setWindow(window);

    auto windowWidth = tgui::bindWidth(gui);
    auto windowHeight = tgui::bindHeight(gui);

    theme = tgui::Theme::create("sprites/Theme/Black.txt");
    _board_name = theme->load("EditBox");
    _board_name->setSize(windowWidth * 2 / 4, windowHeight / 10);

    gui.add(_board_name);
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
