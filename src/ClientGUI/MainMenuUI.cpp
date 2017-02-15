#include "Includes/MeinMenuUI.hpp"

void MeinMenu::fLoadUI()
{
	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	theme = std::make_shared<tgui::Theme>("Game.txt");
	_main = std::make_shared<tgui::Picture>("MainMenu.png");
	_main->setSize(tgui::bindMax(1280, windowWidth), tgui::bindMax(800, windowHeight));
	gui.add(_main);

	_menu = std::make_shared<tgui::Picture>("MenuWindow.png");
	_menu->setPosition(100, 180);
	_menu->setSize(372, 582);
	gui.add(_menu);
	_logo = std::make_shared<tgui::Picture>("logo.png");
	_logo->setPosition(100, 100);
	_logo->setSize(372, 122);
	gui.add(_logo);
	_btn_new_game = theme->load("Button");
	_btn_new_game->setSize(275, 50);
	_btn_new_game->setPosition(145, 270);
	_btn_new_game->setText("New Game");
	gui.add(_btn_new_game);

	_btn_settings = theme->load("Button");
	_btn_settings->setSize(275, 50);
	_btn_settings->setPosition(145, 350);
	_btn_settings->setText("Settings");
	gui.add(_btn_settings);

	_btn_exit = theme->load("Button");
	_btn_exit->setSize(275, 50);
	_btn_exit->setPosition(145, 430);
	_btn_exit->setText("Exit");
	gui.add(_btn_exit);
}


MeinMenu::MeinMenu(const sf::Event &event, sf::RenderWindow &window)
{
	display_window = true;
	window.create(sf::VideoMode(1280, 800), "Dungeons & Dragons");
	gui.setWindow(window);
	this->_event = event;
	fLoadUI();

}
void MeinMenu::fUpdate(sf::RenderWindow  &window)
{

	while (window.pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
			window.close();

		gui.handleEvent(_event);
	}
}
void MeinMenu::fDraw(sf::RenderWindow & window)
{
	gui.draw();
}