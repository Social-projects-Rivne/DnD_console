#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>


class MeinMenu
{
	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr theme;
	tgui::Picture::Ptr _main;
	tgui::Picture::Ptr _menu;
	tgui::Picture::Ptr _logo;
	tgui::Button::Ptr _btn_new_game;
	tgui::Button::Ptr _btn_settings;
	tgui::Button::Ptr _btn_exit;

	void fLoadUI();
public:
	bool display_window;

	MeinMenu(const sf::Event &event, sf::RenderWindow &window);
	void fUpdate(sf::RenderWindow  &window);
	void fDraw(sf::RenderWindow & window);
};
