// RegisterForm.cpp
//
// GUI_Client
// for 
// SoftServe ITA
//
// Kopelyuk Vitaliy
// vkopeluk@gmail.com
//

#include "Includes/RegisterForm.hpp"
#include "Includes/Logger.hpp"


void RegisterForm::fInitUIElements()
{
    _theme = std::make_shared<tgui::Theme>("Interface/Black.txt");
    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    _picture = std::make_shared<tgui::Picture>("Interface/login.jpg");
    _picture->setSize(windowWidth,windowHeight);
    _gui.add(_picture);

    tgui::Picture::Ptr logo1 = std::make_shared<tgui::Picture>("Interface/log.png");
    logo1->setSize(400, 232);
    logo1->setPosition(10, -30);
    _gui.add(logo1);

    _editBoxUsername = _theme->load("EditBox");
    _editBoxUsername->setSize(300, 40);
    _editBoxUsername->setPosition(windowWidth/2, windowHeight/2-100);
    _editBoxUsername->setDefaultText("Username");
    _gui.add(_editBoxUsername, "Username");

    _editBoxEmail = _theme->load("EditBox");
    _editBoxEmail->setSize(300, 40);
    _editBoxEmail->setPosition(windowWidth/2+350, windowHeight/2-100);
    _editBoxEmail->setDefaultText("E-mail");
    _gui.add(_editBoxEmail, "E-mail");

    _editBoxPassword = _theme->load("EditBox");
    _editBoxPassword->setSize(300, 40);
    _editBoxPassword->setPosition(windowWidth / 2, windowHeight / 2 +5);
    _editBoxPassword->setPasswordCharacter('*');
    _editBoxPassword->setDefaultText("Password");
    _gui.add(_editBoxPassword, "Password");

    _editBoxPasswordRe = _theme->load("EditBox");
    _editBoxPasswordRe->setSize(300, 40);
    _editBoxPasswordRe->setPosition(windowWidth / 2 + 350, windowHeight / 2 +5);
    _editBoxPasswordRe->setPasswordCharacter('*');
    _editBoxPasswordRe->setDefaultText("Repeat Password");
    _gui.add(_editBoxPasswordRe, "PasswordRe");

    _register_button = _theme->load("Button");
    _register_button->setSize(335, 40);
    _register_button->setPosition(windowWidth/2+155, windowHeight/2+100);
    _register_button->setText("Register");
    _gui.add(_register_button);
    
    _back = _theme->load("Button");
    _back->setSize(335, 40);
    _back->setPosition(windowWidth/2+155, windowHeight/2+160);
    _back->setText("Cancel");
    _gui.add(_back);

    _register_button->connect("pressed", &RegisterForm::fRegistration, this, _editBoxUsername, _editBoxEmail, _editBoxPassword, _editBoxPasswordRe);
    _back->connect("pressed", &RegisterForm::fBack_Click, this);
}

void RegisterForm::fRegistration(tgui::EditBox::Ptr username, tgui::EditBox::Ptr email, tgui::EditBox::Ptr password, tgui::EditBox::Ptr re_password)
{
    bool validate_username;
    bool validate_password;
    bool validata_password_match;
    bool validate_email;
    const std::regex  validate_email_("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    if(username->getText().toAnsiString().find(' ') != std::string::npos ||  // check for invalid symbols
        username->getText().toAnsiString().find('\'') != std::string::npos ||
        username->getText().toAnsiString().find('"') != std::string::npos ||
        username->getText().toAnsiString().length() == 0)
    {
        std::cout << "Invalid username! Empty spaces, ' or \" found!\n";
        
        tgui::Label::Ptr toolTip = _theme->load("Label");
        toolTip->setTextColor(tgui::Color::Color("red"));
        toolTip->setPosition(tgui::bindWidth(_gui) / 2, tgui::bindHeight(_gui) / 2 - 60);
        toolTip->setSize(300, 40);
        toolTip->setText(R"(Invalid username! Empty spaces, ' or \" found!)");
        _gui.add(toolTip);

        Logger::fLog("Invalid username! Empty spaces, ' or \" found!", Logger::type::warning);
        validate_username = false;
    }
    else
    {
        validate_username = true;
    }


    if(!std::regex_match(email->getText().toAnsiString(), validate_email_)||
        email->getText().toAnsiString().find(' ') != std::string::npos ||  // check for invalid symbols
        email->getText().toAnsiString().find('\'') != std::string::npos ||
        email->getText().toAnsiString().find('"') != std::string::npos)
    {
        std::cout << "Invalid email address!\n";

        tgui::Label::Ptr toolTip = _theme->load("Label");
        toolTip->setTextColor(tgui::Color::Color("red"));
        toolTip->setPosition(tgui::bindWidth(_gui) / 2+350, tgui::bindHeight(_gui) / 2 - 60);
        toolTip->setSize(300, 40);
        toolTip->setText(R"(Invalid email address!)");
        _gui.add(toolTip);

        Logger::fLog("Invalid email address!", Logger::type::warning);
        validate_email = false;
    }
    else
    {
        validate_email = true;
    }

    if (password->getText().toAnsiString().size() >= 6)
    {
        validate_password = true;
    }
    else
    {
        validate_password = false;
        std::cout << "Password length less than 6 symbols!\n";

        tgui::Label::Ptr toolTip = _theme->load("Label");
        toolTip->setTextColor(tgui::Color::Color("red"));
        toolTip->setPosition(tgui::bindWidth(_gui) / 2, tgui::bindHeight(_gui) / 2 + 45);
        toolTip->setSize(600, 40);
        toolTip->setText(R"(Password length less than 6 symbols! or Password does not match!)");
        _gui.add(toolTip);

        Logger::fLog("Password length less than 6 symbols! or Password does not match!", Logger::type::warning);
    }

    if(password->getText().toAnsiString() == re_password->getText().toAnsiString())
    {
        validata_password_match = true;
    }
    else
    {
        validata_password_match = false;

        tgui::Label::Ptr toolTip = _theme->load("Label");
        toolTip->setTextColor(tgui::Color::Color("red"));
        toolTip->setPosition(tgui::bindWidth(_gui) / 2, tgui::bindHeight(_gui) / 2 + 45);
        toolTip->setSize(600, 40);
        toolTip->setText(R"(Password length less than 6 symbols! or Password does not match!)");
        _gui.add(toolTip);

        std::cout << "Password does not match!\n";
        Logger::fLog("Password length less than 6 symbols! or Password does not match!",Logger::type::warning);
    }


    if (validate_username&&validate_email&&validate_password&&validata_password_match)
    {
        std::string request = UserActions::fRegistration(username->getText(), email->getText().toAnsiString(), password->getText().toAnsiString(), re_password->getText().toAnsiString()).dump();
        std::cout << request << std::endl;
        std::string response;
        _http_client->fSendRequest(HttpClient::_POST, "/api/userregister", request);
        _http_client->fGetResponse(response);
        std::cout << "response" << response << std::endl;

        nlohmann::json json_response = json::parse(response.c_str());

        if (json_response["status"] == "success")
        {
            display_window = false;
            Logger::fLog("User "+username->getText().toAnsiString()+" successfully registred",Logger::type::info);
        }
    }
}

void RegisterForm::fBack_Click()
{
    display_window = false;
}


RegisterForm::RegisterForm(const sf::Event &event, sf::RenderWindow &window, HttpClient *http_client)
{
    _http_client = http_client;
    display_window = true;
    window.setTitle("Dungeons & Dragons: Registration");
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
