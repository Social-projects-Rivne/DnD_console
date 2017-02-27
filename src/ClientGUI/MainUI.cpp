#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Includes/LoginForm.hpp"
#include "Includes/IniParser.hpp"



int main()
{
    IniParser pIni_parser("config.ini");
    auto params = pIni_parser.fGetParams();
    try
    {
        //std::shared_ptr<HttpClient>http_client(new HttpClient(io_service, params["client.host"], params["client.port"]));
        boost::asio::io_service io_service;
        HttpClient* client = new HttpClient(io_service, "localhost", "15000");

        sf::Image icon;
        if (!icon.loadFromFile("Interface/ico.png")) {
            return EXIT_FAILURE;
        }

        sf::RenderWindow window(sf::VideoMode(850, 320), "dnd");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        sf::Event event;
        LoginForm menu(event, window, client);
        while (window.isOpen())
        {
            menu.fUpdate(window);
            menu.fDraw(window);
            window.display();
        }
    }
    catch (std::exception& e)
    {
        std::cout <<e.what() << std::endl;
    }
    system("pause");
	return EXIT_SUCCESS;
}