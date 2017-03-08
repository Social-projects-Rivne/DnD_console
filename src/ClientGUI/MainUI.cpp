// MainUI.cpp
//
// GUI_Client
// for 
// SoftServe ITA
//
// Kopelyuk Vitaliy
// vkopeluk@gmail.com
//

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Includes/LoginForm.hpp"
#include "Includes/IniParser.hpp"
#include "Includes/Logger.hpp"



int main()
{
    IniParser pIni_parser("config.ini");
    auto params = pIni_parser.fGetParams();
    boost::asio::io_service io_service;

    HttpClient *http_client = new HttpClient(io_service, params["client.host"], params["client.port"]);

    Logger::fLog("Client started", Logger::type::info);
    try
    {
        sf::Image icon;
        if (!icon.loadFromFile("Interface/ico.png")) {
            return EXIT_FAILURE;
        }

        sf::RenderWindow window(sf::VideoMode(1920,1080), "Dungeons & Dragons", sf::Style::Fullscreen);
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        window.setFramerateLimit(60);
        sf::Event event;
        LoginForm menu(event, window, http_client);
        while (window.isOpen())
        {
            menu.fUpdate(window);
            menu.fDraw(window);
            window.display();
        }
    }
    catch (std::exception& e)
    {
        Logger::fLog(e.what(), Logger::type::error);
        std::cout <<e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}