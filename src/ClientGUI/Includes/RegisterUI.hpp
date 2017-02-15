#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Network.hpp"
#include "UserActions.hpp"

class RegisterUser
{
	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr theme;
	tgui::EditBox::Ptr editBoxUsername;
	tgui::EditBox::Ptr editBoxEmail;
	tgui::EditBox::Ptr editBoxPassword;
	tgui::EditBox::Ptr editBoxPasswordRe;
	tgui::Button::Ptr register_button;

	void fRegistration(tgui::EditBox::Ptr username, tgui::EditBox::Ptr email, tgui::EditBox::Ptr password, tgui::EditBox::Ptr re_password);
	void fLoadUI();

public:
	bool display_window;

	RegisterUser(const sf::Event &event, sf::RenderWindow &window);
	void fUpdate(sf::RenderWindow  &window);
	void fDraw(sf::RenderWindow & window);
};
