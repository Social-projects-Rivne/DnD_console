#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace sf;

void fDisplayNPCMenu(RenderWindow & window);

void menu(RenderWindow & window)
{
    // Load sprites to display
    Texture headerTexture;
    if (!headerTexture.loadFromFile(resourcePath() + "images/dm.png")) {
        return EXIT_FAILURE;
    }
    Sprite header(headerTexture);
    
    Texture menuTexture1, menuTexture2, backTexture, menuBackground;
    if (!menuTexture1.loadFromFile(resourcePath() + "images/npc.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu1(menuTexture1);
    
    if (!menuTexture2.loadFromFile(resourcePath() + "images/terrain.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu2(menuTexture2);
    
    if (!backTexture.loadFromFile(resourcePath() + "images/back.png")) {
        return EXIT_FAILURE;
    }
    Sprite back(backTexture);
    
    if (!menuBackground.loadFromFile(resourcePath() + "images/dragon.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite menuBg(menuBackground);
    sf::Vector2f targetSize(800.0f, 600.0f);
    
    menuBg.setScale(targetSize.x / menuBg.getLocalBounds().width, targetSize.y / menuBg.getLocalBounds().height);
    
    bool isMenu = 1;
    int menuNum = 0;
    header.setPosition(20, 10);
    menu1.setPosition(20, 90);
    menu2.setPosition(20, 140);
    back.setPosition(20, 190);
    menuBg.setPosition(0, 0);
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        back.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));
        
        if (IntRect(20, 90, 170, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
        if (IntRect(20, 140, 230, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
        if (IntRect(20, 190, 385, 50).contains(Mouse::getPosition(window))) { back.setColor(Color::Red); menuNum = 3; }
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                window.clear();
                fDisplayNPCMenu(window);
                isMenu = false;
            }
            if (menuNum == 2)
            {
                //window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if (menuNum == 3)
            {
                window.close();
                isMenu = false;
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(menuBg);
        window.draw(header);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(back);
        
        // Update the window
        window.display();
    }
}

void fDisplayNPCMenu(RenderWindow & window)
{
    // Load sprites to display
    Texture headerTexture;
    if (!headerTexture.loadFromFile(resourcePath() + "images/npc/npc.png")) {
        return EXIT_FAILURE;
    }
    Sprite header(headerTexture);
    
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    if (!menuTexture1.loadFromFile(resourcePath() + "images/npc/create.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu1(menuTexture1);
    
    if (!menuTexture2.loadFromFile(resourcePath() + "images/npc/show.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu2(menuTexture2);
    
    if (!menuTexture3.loadFromFile(resourcePath() + "images/npc/load_by_id.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu3(menuTexture3);
    
    Texture menuTexture4;
    if (!menuTexture4.loadFromFile(resourcePath() + "images/npc/edit.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu4(menuTexture4);

    Texture menuTexture5;
    if (!menuTexture5.loadFromFile(resourcePath() + "images/npc/delete.png")) {
        return EXIT_FAILURE;
    }
    Sprite menu5(menuTexture5);

    Texture backTexture;
    if (!backTexture.loadFromFile(resourcePath() + "images/back.png")) {
        return EXIT_FAILURE;
    }
    Sprite back(backTexture);

    if (!menuBackground.loadFromFile(resourcePath() + "images/dragon.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite menuBg(menuBackground);
    sf::Vector2f targetSize(800.0f, 600.0f);
    
    menuBg.setScale(targetSize.x / menuBg.getLocalBounds().width, targetSize.y / menuBg.getLocalBounds().height);
    
    bool isMenu = 1;
    int menuNum = 0;
    header.setPosition(20, 10);
    menu1.setPosition(20, 90);
    menu2.setPosition(20, 140);
    menu3.setPosition(20, 190);
    menu4.setPosition(20, 240);
    menu5.setPosition(20, 290);
    back.setPosition(20, 340);
    menuBg.setPosition(0, 0);
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menu4.setColor(Color::White);
        menu5.setColor(Color::White);
        back.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));
        
        if (IntRect(20, 90, 180, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
        if (IntRect(20, 140, 237, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
        if (IntRect(20, 190, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
        if (IntRect(20, 240, 353, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Red); menuNum = 4; }
        if (IntRect(20, 290, 381, 50).contains(Mouse::getPosition(window))) { menu5.setColor(Color::Red); menuNum = 5; }
        if (IntRect(20, 340, 375, 50).contains(Mouse::getPosition(window))) { back.setColor(Color::Red); menuNum = 6; }
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
            {
                /*
                std::string request = UserActions::fCreateNpc(user_session).dump();
                std::string response;
                _http_client->fSendRequest(HttpClient::_POST, "/api/addnpc", request);
                _http_client->fGetResponse(response);*/
                window.clear();
                window.draw(menuBg);
                
                Font font;
                font.loadFromFile(resourcePath() + "/Users/olhaleskovska/Desktop/Npc_sfml/Npc_sfml/sansation.ttf");
                Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
                //text.setColor(Color::Yellow);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);
                std::string response;
                response = "text";
                text.setString(response);
                //text.setPosition(view.getCenter().x , view.getCenter().y );
                window.draw(text);
            
            }
            if (menuNum == 2)
            {
                            }
            if (menuNum == 3)
            {
            }
            if (menuNum == 4)
            {
                
            }
            if (menuNum == 5)
            {
                
            }
            if (menuNum == 6)
            {
                window.clear();
                menu(window);
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw sprites
        window.draw(menuBg);
        window.draw(header);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(menu4);
        window.draw(menu5);
        window.draw(back);
        
        // Update window
        window.display();

    }
}

int main(int, char const**)
{
    // Create the main window
    RenderWindow window(sf::VideoMode(800, 600), "DnD");
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    menu(window);
    
    return EXIT_SUCCESS;
}
