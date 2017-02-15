#include "Includes/LoginUI.hpp"



void LoginForm::fButtonRegisterClicked()
{
	reg_button_click = true;
}

void LoginForm::fLoadUI()
{


	tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("Black.txt");


	terrain_list = theme->load("ListBox");
	terrain_list->setSize(250, 250);
	terrain_list->setPosition(0, 0);
	//	boost::asio::io_service io_service;

	//IniParser pIni_parser("config.ini");
	//	auto params = pIni_parser.fGetParams();

	//HttpClient *http_client = new HttpClient(io_service, params["client.host"], params["client.port"]);

	//std::string request = UserActions::fLogin("softserve", "123qqq").dump();
	//std::cout << request << std::endl;
	//	std::string response;
	//_http_client->fSendRequest(HttpClient::_POST, "/api/userlogin", request);
	//_http_client->fGetResponse(response);

	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	tgui::Picture::Ptr picture = std::make_shared<tgui::Picture>("login_screen.png");
	picture->setSize(tgui::bindMax(850, windowWidth), tgui::bindMax(320, windowHeight));
	gui.add(picture);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(40, 55);
	editBoxUsername->setDefaultText("Username");
	gui.add(editBoxUsername, "Username");

	// Create the password edit box
	tgui::EditBox::Ptr editBoxPassword = theme->load("EditBox");
	editBoxPassword->setSize(400, 40);
	editBoxPassword->setPosition(40, 120);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");
	gui.add(editBoxPassword, "Password");

	// Create the login button
	tgui::Button::Ptr login_button = theme->load("Button");
	login_button->setSize(150, 35);
	login_button->setPosition(40, 185);
	login_button->setText("Login");
	gui.add(login_button);

	tgui::Button::Ptr register_button = theme->load("Button");
	register_button->setSize(240, 35);
	register_button->setPosition(200, 185);
	register_button->setText("Register");

	gui.add(register_button);



	login_button->connect("pressed", &LoginForm::fLogin, this, editBoxUsername, editBoxPassword);
	register_button->connect("pressed", &LoginForm::fButtonRegisterClicked, this);
}
void LoginForm::fLogin(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
	std::string request = UserActions::fLogin(username->getText(), password->getText().toAnsiString()).dump();
	std::cout << request << std::endl;
	std::string response;
	http_client->fSendRequest(HttpClient::_POST, "/api/userlogin", request);
	http_client->fGetResponse(response);
	std::cout << "response" << response << std::endl;

	nlohmann::json json_response = json::parse(response);
	std::string status = json_response["status"];

	if (status == "success" || status == "already logged in")
	{
		_game_session = json_response["session_id"];

		main_menu = true;
		//fSwitchMode(_game_session);

	}
	else
	{
		main_menu = false;


	}
}

LoginForm::LoginForm(const sf::Event & event, sf::RenderWindow &window)
{
	window.create(sf::VideoMode(850, 320), "Dungeons & Dragons: Login");
	gui.setWindow(window);
	//_http_client = client;
	main_menu = false;
	this->_event = event;
	fLoadUI();
	_menu_option = _selected_menu::NONE;
}

void LoginForm::fUpdate(sf::RenderWindow &window)
{
	switch (_menu_option)
	{
	case LoginForm::NONE:
	{
		while (window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				window.close();

			if (reg_button_click)
			{
				_registration = new RegisterUser(_event, window);
				_menu_option = REGISTER;
			}

			if (main_menu)
			{
				menu = new MeinMenu(_event, window);
				_menu_option = MAIN_MENU;
			}

			gui.handleEvent(_event);


		}
	}
	break;
	case REGISTER:
	{
		_registration->fUpdate(window);
	}
	break;
	case MAIN_MENU:
	{
		menu->fUpdate(window);
	}

	}
}
void LoginForm::fDraw(sf::RenderWindow & window)
{
	switch (_menu_option)
	{
	case LoginForm::NONE:
	{
		gui.draw();
	}
	break;
	case REGISTER:
	{
		if (_registration->display_window)
			_registration->fDraw(window);
		else
		{
			delete _registration;
			_menu_option = LoginForm::NONE;
		}
	}
	break;
	case MAIN_MENU:
	{
		if (menu->display_window)
			menu->fDraw(window);
		else
		{
			delete menu;
			_menu_option = LoginForm::NONE;
		}
	}
	}

}
