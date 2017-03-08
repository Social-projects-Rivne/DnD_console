#include "Includes/MessageBox.hpp"

MessBox::MessBox(const sf::Event & event, sf::RenderWindow &window)
{
	_button_ok_click = false;
	_button_yes_click = false;
	_button_no_click = false;
	_button_okk_click = false;
	_button_cancel_click = false;

	auto windowWidth = 250;
	auto windowHeight = 150;

	int pos_x = (window.getSize().x - windowWidth) / 2;
	int pos_y = (window.getSize().y - windowHeight) / 2;
	_message_box_window = new sf::RenderWindow(sf::VideoMode(pos_x, pos_y), "MessageBox");
	_gui.setWindow(*_message_box_window);

	_picture = std::make_shared<tgui::Picture>("Interface/MessageBox.png");
	_picture->setSize(pos_x, pos_y);
	_gui.add(_picture);

	this->_event = event;

	_theme = std::make_shared<tgui::Theme>("Interface/Black.txt");

	_button_ok = _theme->load("Button");
	_button_ok->setSize(150, 35);
	_button_ok->setPosition((_message_box_window->getSize().x - _button_ok->getSize().x) / 2, _message_box_window->getSize().y / 2 + 50);
	_button_ok->setText("Ok");

	_button_yes = _theme->load("Button");
	_button_yes->setSize(100, 35);
	_button_yes->setPosition((_message_box_window->getSize().x - _button_yes->getSize().x) / 2 - _button_yes->getSize().x / 2 - 10, _message_box_window->getSize().y / 2 + 50);
	_button_yes->setText("Yes");

	_button_no = _theme->load("Button");
	_button_no->setSize(100, 35);
	_button_no->setPosition((_message_box_window->getSize().x - _button_no->getSize().x) / 2 + _button_no->getSize().x / 2 + 10, _message_box_window->getSize().y / 2 + 50);
	_button_no->setText("No");

	_button_okk = _theme->load("Button");
	_button_okk->setSize(100, 35);
	_button_okk->setPosition((_message_box_window->getSize().x - _button_okk->getSize().x) / 2 - _button_okk->getSize().x / 2 - 10, _message_box_window->getSize().y / 2 + 50);
	_button_okk->setText("Ok");

	_button_cancel = _theme->load("Button");
	_button_cancel->setSize(100, 35);
	_button_cancel->setPosition((_message_box_window->getSize().x - _button_cancel->getSize().x) / 2 + _button_cancel->getSize().x / 2 + 10, _message_box_window->getSize().y / 2 + 50);
	_button_cancel->setText("Cancel");
}

bool MessBox::fMessBoxType(const std::string &message, _elements el)
{
	bool answer;
	if (el ==_elements::Ok)
	{
		fOkInit(*_message_box_window, message);
		fDraw();
		if (_button_ok_click == true)
			answer = true;
	}

	else if (el == _elements::YesNo)
	{
		fYesNoInit(*_message_box_window, message);
		fDraw();
		if (_button_yes_click == true)
			answer = true;
		else if (_button_no_click == true)
			answer = false;
	}
	else if (el == _elements::OkCancel)
	{
		fOkCancelInit(*_message_box_window, message);
		fDraw();
		if (_button_okk_click == true)
			answer = true;
		else if (_button_cancel_click == true)
			answer = false;
	}

	return answer;
}

void MessBox::fSetLabel(sf::RenderWindow &_message_box_window, const std::string &message)
{
	_theme = std::make_shared<tgui::Theme>("Interface/Black.txt");

	_label = std::make_shared<tgui::Label>();
	_label = _theme->load("Label");
	_label->setTextColor(tgui::Color::Color("red"));
	_label->setTextSize(20);
	_label->setText(message);
	_label->setPosition((_message_box_window.getSize().x - _label->getSize().x) / 2, (_message_box_window.getSize().y - _label->getSize().y) / 2);
	_gui.add(_label);
}

void MessBox::fOkInit(sf::RenderWindow &_message_box_window, const std::string &message)
{
	fSetLabel(_message_box_window, message);

	_gui.add(_button_ok);
}

void MessBox::fYesNoInit(sf::RenderWindow &_message_box_window, const std::string &message)
{
	fSetLabel(_message_box_window, message);

	_gui.add(_button_yes);
	_gui.add(_button_no);
}


void MessBox::fOkCancelInit(sf::RenderWindow &_message_box_window, const std::string &message)
{
	fSetLabel(_message_box_window, message);

	_gui.add(_button_okk);
	_gui.add(_button_cancel);
}

/*
Method for updating events
*/
void MessBox::fUpdate()
{
	while (_message_box_window->pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
			_message_box_window->close();

		if (_button_ok->mouseOnWidget(_event.mouseButton.x, _event.mouseButton.y))
		{
			if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
			{
				_button_ok_click = true;
				_message_box_window->close();
			}
		}

		if (_button_yes->mouseOnWidget(_event.mouseButton.x, _event.mouseButton.y))
		{
			if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
			{
				_button_yes_click = true;
				_message_box_window->close();
			}
		}

		if (_button_no->mouseOnWidget(_event.mouseButton.x, _event.mouseButton.y))
		{
			if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
			{
				_button_no_click = true;
				_message_box_window->close();
			}
		}

		if (_button_okk->mouseOnWidget(_event.mouseButton.x, _event.mouseButton.y))
		{
			if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
			{
				_button_okk_click = true;
				_message_box_window->close();
			}
		}

		if (_button_cancel->mouseOnWidget(_event.mouseButton.x, _event.mouseButton.y))
		{
			if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
			{
				_button_cancel_click = true;
				_message_box_window->close();
			}
		}
		_gui.handleEvent(_event);
	}
}

void MessBox::fDraw()
{
	while (_message_box_window->isOpen())
	{
		fUpdate();
		_message_box_window->clear();
		_gui.draw();
		_message_box_window->display();
	}
}