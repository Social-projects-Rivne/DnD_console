#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardMenu.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "dnd");
    
    window.setMouseCursorVisible(false);
    sf::Texture mouse_cursor;
    mouse_cursor.loadFromFile("sprites/Interface/Cursors/Hand.png");
    sf::Sprite mouse_sprite;
    mouse_sprite.setTexture(mouse_cursor);
    mouse_sprite.setOrigin(16, 16);


    std::cout << "\n\nHELLO\n";
    sf::Event event;

    BoardMenu board(10, 10, event, window);

	while (window.isOpen())
	{
        //game.fUpdate(window);
        //game.fDraw(window);

        board.fUpdate(window);

        window.clear();

        mouse_sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        board.fDraw(window);

        window.draw(mouse_sprite);
        window.display();

        
	}

	return 0;
}