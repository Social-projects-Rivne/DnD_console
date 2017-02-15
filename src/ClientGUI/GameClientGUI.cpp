#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Network.hpp"
#include "Includes/UserActions.hpp"




class Modes
{
	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr theme;
	tgui::Picture::Ptr _main;
	tgui::Picture::Ptr _menu;
	tgui::Button::Ptr _btn_playerMode;
	tgui::Button::Ptr _btn_DM_Mode;
	tgui::Button::Ptr _btn_back;
	
	void LoadUI()
	{

	}

public:
	Modes()
	{

	}
};


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

	void fLoadUI()
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

public:
	bool display_window;

	MeinMenu(const sf::Event &event, sf::RenderWindow &window)
	{
		display_window = true;
		window.create(sf::VideoMode(1280, 800), "Dungeons & Dragons");
		gui.setWindow(window);
		this->_event = event;
		fLoadUI();
		
	}
	void fUpdate(sf::RenderWindow  &window)
	{

		while (window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(_event);
		}
	}
	void fDraw(sf::RenderWindow & window)
	{
		gui.draw();
	}
};

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

	void fRegistration(tgui::EditBox::Ptr username, tgui::EditBox::Ptr email, tgui::EditBox::Ptr password, tgui::EditBox::Ptr re_password)
	{
	
		std::string request = UserActions::fRegistration(username->getText(), email->getText().toAnsiString(),password->getText().toAnsiString(),re_password->getText().toAnsiString()).dump();
		std::cout << request << std::endl;
		std::string response;
		http_client->fSendRequest(HttpClient::_POST, "/api/userregister", request);
		http_client->fGetResponse(response);
		std::cout << "response" << response << std::endl;
		
		nlohmann::json json_response = json::parse(response);
		std::string status = json_response["status"];

		if (status == "success")
		{
			std::cout << "OK" << std::endl;
			
		}
	}

	void fLoadUI()
	{
			 theme = std::make_shared<tgui::Theme>("Black.txt");
		
		
			auto windowWidth = tgui::bindWidth(gui);
			auto windowHeight = tgui::bindHeight(gui);
		
			// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
			tgui::Picture::Ptr picture = std::make_shared<tgui::Picture>("register_screen.png");
			picture->setSize(tgui::bindMax(1200, windowWidth), tgui::bindMax(400, windowHeight));
			gui.add(picture);
		
			// Create the username edit box
			editBoxUsername = theme->load("EditBox");
			editBoxUsername->setSize(300, 40);
			editBoxUsername->setPosition(60, 55);
			editBoxUsername->setDefaultText("Username");
			gui.add(editBoxUsername, "Username");
		
			// Create the password edit box
			editBoxEmail = theme->load("EditBox");
			editBoxEmail->setSize(300, 40);
			editBoxEmail->setPosition(430, 55);
			editBoxEmail->setDefaultText("E-mail");
			gui.add(editBoxEmail, "E-mail");
		
			editBoxPassword = theme->load("EditBox");
			editBoxPassword->setSize(300, 40);
			editBoxPassword->setPosition(60, 160);
			editBoxPassword->setPasswordCharacter('*');
			editBoxPassword->setDefaultText("Password");
			gui.add(editBoxPassword, "Password");
		
			editBoxPasswordRe = theme->load("EditBox");
			editBoxPasswordRe->setSize(300, 40);
			editBoxPasswordRe->setPosition(430, 160);
			editBoxPasswordRe->setPasswordCharacter('*');
			editBoxPasswordRe->setDefaultText("Repeat Password");
			gui.add(editBoxPasswordRe, "PasswordRe");
		
		
			register_button = theme->load("Button");
			register_button->setSize(335, 40);
			register_button->setPosition(224, 255);
			register_button->setText("Register");
			gui.add(register_button);
		
			register_button->connect("pressed", &RegisterUser::fRegistration,this,editBoxUsername,editBoxEmail,editBoxPassword,editBoxPasswordRe);
		}
public:
	bool display_window;

	RegisterUser(const sf::Event &event, sf::RenderWindow &window)
	{
		display_window = true;
		window.create(sf::VideoMode(1200, 400), "Dungeons & Dragons: Registration");
		gui.setWindow(window);
		//_http_client = client;
		this->_event = event;
		fLoadUI();
	}
	void fUpdate(sf::RenderWindow  &window)
	{
		
			while (window.pollEvent(_event))
			{
				if (_event.type == sf::Event::Closed)
					window.close();

				gui.handleEvent(_event);
			}
	}
	void fDraw(sf::RenderWindow & window)
	{
		gui.draw();
	}
};




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

	


	void fButtonRegisterClicked()
	{
		reg_button_click = true;
	}

	void fLoadUI()
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
	void fLogin(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
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

public:
	LoginForm(const sf::Event & event, sf::RenderWindow &window)
	{
		window.create(sf::VideoMode(850,320),"Dungeons & Dragons: Login");
		gui.setWindow(window);
		//_http_client = client;
		main_menu = false;
		this->_event = event;
		fLoadUI();
		_menu_option = _selected_menu::NONE;
	}

	void fUpdate(sf::RenderWindow &window)
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
	void fDraw(sf::RenderWindow & window)
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

};


int main()
{

	
	
	

	sf::RenderWindow window(sf::VideoMode(1280, 800), "dnd");

	//window.setMouseCursorVisible(false);
	//sf::Texture mouse_cursor;
	//mouse_cursor.loadFromFile("sprites/Interface/Cursors/Hand.png");
	//sf::Sprite mouse_sprite;
	//mouse_sprite.setTexture(mouse_cursor);
	//mouse_sprite.setOrigin(16, 16);

	sf::Event event;

	LoginForm menu(event, window);

	//BoardEdit board(10, 10, event, window);
	while (window.isOpen())
	{
		//game.fUpdate(window);
		//game.fDraw(window);

		menu.fUpdate(window);

		//board.fUpdate(window);
		//R: 39 G: 42 B: 61
		//window.clear(sf::Color(39, 42, 61));

		//mouse_sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		//board.fDraw(window);
		menu.fDraw(window);

	//	window.draw(mouse_sprite);
		window.display();


	}

return EXIT_SUCCESS;
}