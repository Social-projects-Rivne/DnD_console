#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class MessBox
{
private:
	sf::RenderWindow * _message_box_window;
	sf::Event _event;
	tgui::Gui _gui;

	// UI elements
	tgui::Theme::Ptr       _theme;
	tgui::Picture::Ptr     _picture;
	tgui::Button::Ptr     _button_ok;
	tgui::Button::Ptr     _button_yes;
	tgui::Button::Ptr     _button_no;
	tgui::Button::Ptr     _button_okk;
	tgui::Button::Ptr     _button_cancel;
	tgui::Label::Ptr      _label;

	bool _button_ok_click;
	bool _button_yes_click;
	bool _button_no_click;
	bool _button_okk_click;
	bool _button_cancel_click;

	void fOkInit(sf::RenderWindow &_message_box_window, const std::string &message);
	void fYesNoInit(sf::RenderWindow &_message_box_window, const std::string &message);
	void fOkCancelInit(sf::RenderWindow &_message_box_window, const std::string &message);
	void fUpdate();
	void fSetLabel(sf::RenderWindow &_message_box_window, const std::string &message);
	void fDraw();

public:
	enum _elements
	{
		Ok,
		YesNo,
		OkCancel
	};

	MessBox(const sf::Event & event, sf::RenderWindow &window);
	bool fMessBoxType(const std::string &message, _elements el);
};