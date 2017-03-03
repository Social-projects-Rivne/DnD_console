#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardMenu.hpp"
#include "BoardEdit.hpp"
#include "HttpClient.hpp"

int main()
{
    boost::asio::io_service io_service;
    HttpClient* client = new HttpClient(io_service, "localhost", "15000");


	sf::RenderWindow window(sf::VideoMode(1600, 900), "dnd");
    
    window.setMouseCursorVisible(false);
    sf::Texture mouse_cursor;
    mouse_cursor.loadFromFile("sprites/Interface/Cursors/Hand.png");
    sf::Sprite mouse_sprite;
    mouse_sprite.setTexture(mouse_cursor);
    mouse_sprite.setOrigin(16, 16);

    sf::Event event;

    BoardMenu menu(event, window, client);

	while (window.isOpen())
	{
        //game.fUpdate(window);
        //game.fDraw(window);

        menu.fUpdate(window);

        //board.fUpdate(window);
        //R: 39 G: 42 B: 61
        window.clear(sf::Color(39,42,61));

        mouse_sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        //board.fDraw(window);
        menu.fDraw(window);

        window.draw(mouse_sprite);
        window.display();

        
	}

	return 0;
}
