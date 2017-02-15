#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "UserActions.hpp"
#include "MeinMenuUI.hpp"
#include "RegisterUI.hpp"


class LoginForm
{
	enum _selected_menu
	{
		NONE,
		LOGIN,
		MAIN_MENU,
		REGISTER,
	};

	sf::Event _event;
	tgui::Gui gui;
	//HttpClient *_http_client;
	bool main_menu;
	bool reg_button_click;

	tgui::Theme::Ptr _theme;
	tgui::EditBox::Ptr _Username;
	tgui::EditBox::Ptr _BoxPassword;
	tgui::Button::Ptr _Login_button;
	tgui::Button::Ptr _Register_button;
	tgui::ListBox::Ptr terrain_list;
	std::string _game_session;

	RegisterUser *_registration;
	MeinMenu *menu;

	_selected_menu _menu_option;




	void fButtonRegisterClicked();

	void fLoadUI();

	void fLogin(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password);

public:
	LoginForm(const sf::Event & event, sf::RenderWindow &window);
	void fUpdate(sf::RenderWindow &window);
	void fDraw(sf::RenderWindow & window);
};
	