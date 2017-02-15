#include "Includes/RegisterUI.hpp"

void RegisterUser::fRegistration(tgui::EditBox::Ptr username, tgui::EditBox::Ptr email, tgui::EditBox::Ptr password, tgui::EditBox::Ptr re_password)
{

	std::string request = UserActions::fRegistration(username->getText(), email->getText().toAnsiString(), password->getText().toAnsiString(), re_password->getText().toAnsiString()).dump();
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

void RegisterUser::fLoadUI()
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

	register_button->connect("pressed", &RegisterUser::fRegistration, this, editBoxUsername, editBoxEmail, editBoxPassword, editBoxPasswordRe);
}

RegisterUser::RegisterUser(const sf::Event &event, sf::RenderWindow &window)
{
	display_window = true;
	window.create(sf::VideoMode(1200, 400), "Dungeons & Dragons: Registration");
	gui.setWindow(window);
	//_http_client = client;
	this->_event = event;
	fLoadUI();
}
void RegisterUser::fUpdate(sf::RenderWindow  &window)
{

	while (window.pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
			window.close();

		gui.handleEvent(_event);
	}
}
void RegisterUser::fDraw(sf::RenderWindow & window)
{
	gui.draw();
}