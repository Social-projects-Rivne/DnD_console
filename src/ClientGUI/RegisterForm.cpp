#include "Includes/RegisterForm.hpp"


void RegisterForm::fRegistration(tgui::EditBox::Ptr username, tgui::EditBox::Ptr email, tgui::EditBox::Ptr password, tgui::EditBox::Ptr re_password)
{

    std::string request = UserActions::fRegistration(username->getText(), email->getText().toAnsiString(), password->getText().toAnsiString(), re_password->getText().toAnsiString()).dump();
    std::cout << request << std::endl;
    std::string response;
    _http_client->fSendRequest(HttpClient::_POST, "/api/userregister", request);
    _http_client->fGetResponse(response);
    std::cout << "response" << response << std::endl;

    nlohmann::json json_response = json::parse(response);
    std::string status = json_response["status"];

    if (status == "success")
    {
        std::cout << "OK" << std::endl;
        information_window->show();
        //information_window->setCloseButton(_register_button);
        //information_window->setCloseButton(_back);
    }
}

void RegisterForm::fBack_Click()
{
    display_window = false;
}

void RegisterForm::fInitUIElements()
{
    _theme = std::make_shared<tgui::Theme>("Interface/Black.txt");
    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    tgui::Picture::Ptr picture = std::make_shared<tgui::Picture>("Interface/register_screen.png");
    picture->setSize(tgui::bindMax(1200, windowWidth), tgui::bindMax(400, windowHeight));
    _gui.add(picture);

    _editBoxUsername = _theme->load("EditBox");
    _editBoxUsername->setSize(300, 40);
    _editBoxUsername->setPosition(60, 55);
    _editBoxUsername->setDefaultText("Username");
    _gui.add(_editBoxUsername, "Username");

    _editBoxEmail = _theme->load("EditBox");
    _editBoxEmail->setSize(300, 40);
    _editBoxEmail->setPosition(430, 55);
    _editBoxEmail->setDefaultText("E-mail");
    _gui.add(_editBoxEmail, "E-mail");

    _editBoxPassword = _theme->load("EditBox");
    _editBoxPassword->setSize(300, 40);
    _editBoxPassword->setPosition(60, 160);
    _editBoxPassword->setPasswordCharacter('*');
    _editBoxPassword->setDefaultText("Password");
    _gui.add(_editBoxPassword, "Password");

    _editBoxPasswordRe = _theme->load("EditBox");
    _editBoxPasswordRe->setSize(300, 40);
    _editBoxPasswordRe->setPosition(430, 160);
    _editBoxPasswordRe->setPasswordCharacter('*');
    _editBoxPasswordRe->setDefaultText("Repeat Password");
    _gui.add(_editBoxPasswordRe, "PasswordRe");

    information_window = _theme->load("ChildWindow");
    information_window->setSize(250, 120);
    information_window->setPosition(420, 80);
    information_window->setTitle("Registration success");
    _gui.add(information_window);
    information_window->hide();

    _register_button = _theme->load("Button");
    _register_button->setSize(335, 40);
    _register_button->setPosition(224, 255);
    _register_button->setText("Register");
    _gui.add(_register_button);
    

    _back = _theme->load("Button");
    _back->setSize(335, 40);
    _back->setPosition(224, 315);
    _back->setText("Cancel");
    _gui.add(_back);

    _register_button->connect("pressed", &RegisterForm::fRegistration, this, _editBoxUsername, _editBoxEmail, _editBoxPassword, _editBoxPasswordRe);
    _back->connect("pressed", &RegisterForm::fBack_Click, this);
}

RegisterForm::RegisterForm(const sf::Event &event, sf::RenderWindow &window, HttpClient *http_client)
{
	_http_client = http_client;
    display_window = true;
    window.create(sf::VideoMode(1200, 400), "Dungeons & Dragons: Registration");
    _gui.setWindow(window);
    this->_event = event;
	fInitUIElements();
}
void RegisterForm::fUpdate(sf::RenderWindow  &window)
{

    while (window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            window.close();
        _gui.handleEvent(_event);
    }
}

void RegisterForm::fDraw(sf::RenderWindow & window)
{
    _gui.draw();
}
