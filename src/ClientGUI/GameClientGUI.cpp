#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Network.hpp"
#include "Includes/Character.hpp"
#include "Includes/UserActions.hpp"


class NPCUI
{
	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr _theme;
	tgui::EditBox::Ptr _npc_name;
	tgui::EditBox::Ptr _npc_type;
	tgui::ComboBox::Ptr _strength;
	tgui::ComboBox::Ptr _dexterity;
	tgui::ComboBox::Ptr _constitution;
	tgui::ComboBox::Ptr _inteligence;
	tgui::ComboBox::Ptr _wisdom;
	tgui::ComboBox::Ptr _charisma;
	tgui::Label::Ptr _strength_l;
	tgui::Label::Ptr _dexterity_l;
	tgui::Label::Ptr _constitution_l;
	tgui::Label::Ptr _inteligence_l;
	tgui::Label::Ptr _wisdom_l;
	tgui::Label::Ptr _charisma_l;
	tgui::ListBox::Ptr _npc_list;
	tgui::Button::Ptr _create_btn;
	tgui::Button::Ptr _back_btn;
	tgui::Button::Ptr _refresh_btn;
	tgui::Picture::Ptr _back;
	bool _combo_box;

	std::string data_strength;
	std::string data_dexterity;
	std::string data_constitution;
	std::string data_intelligence;
	std::string data_wisdom;
	std::string data_charisma;

	std::string _game_session;
	json npc_data;
	bool updated;

	bool create_pressed;


	void fLoadUI()
	{
		_theme = std::make_shared<tgui::Theme>("Game.txt");

		auto windowWidth = tgui::bindWidth(gui);
		auto windowHeight = tgui::bindHeight(gui);

		_theme = std::make_shared<tgui::Theme>("Game.txt");
		_back = std::make_shared<tgui::Picture>("Back.png");
		_back->setSize(tgui::bindMax(1280, windowWidth), tgui::bindMax(800, windowHeight));
		gui.add(_back);

		_npc_name = _theme->load("EditBox");
		_npc_name->setPosition(610, 85);
		_npc_name->setSize(160, 50);
		_npc_name->setDefaultText("Name");
		gui.add(_npc_name);

		_npc_type = _theme->load("EditBox");
		_npc_type->setPosition(820, 85);
		_npc_type->setSize(160, 50);
		_npc_type->setDefaultText("Type");
		gui.add(_npc_type);

		_strength_l = _theme->load("Label");
		_strength_l->setPosition(610, 145);
		_strength_l->setText("Strength");
		gui.add(_strength_l);

		_dexterity_l = _theme->load("Label");
		_dexterity_l->setPosition(820, 145);
		_dexterity_l->setText("Dexterity");
		gui.add(_dexterity_l);

		_constitution_l = _theme->load("Label");
		_constitution_l->setPosition(1030, 145);
		_constitution_l->setText("Constitution");
		gui.add(_constitution_l);

		_strength = _theme->load("ComboBox");
		_strength->setSize(160, 50);
		_strength->setPosition(610, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_strength->addItem(std::to_string(i));
		}
		gui.add(_strength);

		_dexterity = _theme->load("ComboBox");
		_dexterity->setSize(160, 50);
		_dexterity->setPosition(820, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_dexterity->addItem(std::to_string(i));
		}
		gui.add(_dexterity);

		_constitution = _theme->load("ComboBox");
		_constitution->setSize(160, 50);
		_constitution->setPosition(1030, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_constitution->addItem(std::to_string(i));
		}
		gui.add(_constitution);

		_inteligence_l = _theme->load("Label");
		_inteligence_l->setPosition(610, 245);
		_inteligence_l->setText("Intelligence");
		gui.add(_inteligence_l);

		_wisdom_l = _theme->load("Label");
		_wisdom_l->setPosition(820, 245);
		_wisdom_l->setText("Wisdom");
		gui.add(_wisdom_l);

		_charisma_l = _theme->load("Label");
		_charisma_l->setPosition(1030, 245);
		_charisma_l->setText("Charisma");
		gui.add(_charisma_l);

		_inteligence = _theme->load("ComboBox");
		_inteligence->setSize(160, 50);
		_inteligence->setPosition(610, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_inteligence->addItem(std::to_string(i));
		}
		gui.add(_inteligence);

		_wisdom = _theme->load("ComboBox");
		_wisdom->setSize(160, 50);
		_wisdom->setPosition(820, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_wisdom->addItem(std::to_string(i));
		}
		gui.add(_wisdom);

		_charisma = _theme->load("ComboBox");
		_charisma->setSize(160, 50);
		_charisma->setPosition(1030, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_charisma->addItem(std::to_string(i));
		}
		gui.add(_charisma);

		_create_btn = _theme->load("Button");
		_create_btn->setSize(160, 50);
		_create_btn->setPosition(1030, 375);
		_create_btn->setText("Create NPC");
		gui.add(_create_btn);

		_back_btn = _theme->load("Button");
		_back_btn->setSize(160, 50);
		_back_btn->setPosition(50, 665);
		_back_btn->setText("Back");
		gui.add(_back_btn);

		_refresh_btn = _theme->load("Button");
		_refresh_btn->setSize(400, 50);
		_refresh_btn->setPosition(50, 375);
		_refresh_btn->setText("Refresh NPCs List");
		gui.add(_refresh_btn);

		_npc_list = _theme->load("ListBox");
		_npc_list->setPosition(50, 85);
		_npc_list->setSize(400, 240);
		gui.add(_npc_list);

		_combo_box = true;

		_create_btn->connect("pressed", &NPCUI::fCreateNPC, this, _npc_name, _npc_type);
		_refresh_btn->connect("pressed", &NPCUI::Refresh, this);
		_back_btn->connect("pressed", &NPCUI::fdisable, this);
	}

	void fCreateNPC(tgui::EditBox::Ptr name, tgui::EditBox::Ptr type)
	{
		//character.fSetOwner(_game_session);

		Npc npc(_game_session,name->getText().toAnsiString(), type->getText().toAnsiString(),"1","100", data_strength, data_dexterity, data_constitution, data_intelligence, data_wisdom, data_charisma);

		std::string response;
		std::string request = npc.fToJson().dump();
		std::cout << request << std::endl;
		http_client->fSendRequest(HttpClient::_POST, "/api/addnpc", request);
		http_client->fGetResponse(response);
		std::cout << response << std::endl;
		_combo_box = false;
	}

	void fLoadNPCListBox()
	{

		std::string response;
		auto request = UserActions::fLoadMyNpcs(_game_session).dump();
		http_client->fSendRequest(HttpClient::_POST, "/api/loadmynpcslist", request);
		http_client->fGetResponse(response);
		npc_data = json::parse(response);
		std::cout << npc_data;
	}

	void Refresh()
	{
		fLoadNPCListBox();
		_npc_list->removeAllItems();
		updated = false;
	}

	void fdisable()
	{
		display_window = false;
	}
public:
	bool display_window;
	NPCUI(const sf::Event &event, sf::RenderWindow &window, std::string game_session)
	{

		display_window = true;
		_game_session = game_session;
		gui.setWindow(window);
		fLoadNPCListBox();
		updated = false;
		//_menu_option = NONE;
		fLoadUI();
		this->_event = event;
	}

	void fUpdate(sf::RenderWindow  &window)
	{

		while (window.pollEvent(_event))
		{
			if (_combo_box)
			{
				data_strength = _strength->getSelectedItem();
				data_dexterity = _dexterity->getSelectedItem();
				data_constitution = _constitution->getSelectedItem();
				data_intelligence = _inteligence->getSelectedItem();
				data_wisdom = _wisdom->getSelectedItem();
				data_charisma = _charisma->getSelectedItem();

			}
			else
			{
				_strength->deselectItem();
				_dexterity->deselectItem();
				_constitution->deselectItem();
				_inteligence->deselectItem();
				_wisdom->deselectItem();
				_charisma->deselectItem();
				_npc_name->setDefaultText(" ");
				_npc_type->setDefaultText(" ");
				_npc_type->setDefaultText(" ");
				_combo_box = true;

			}

			try
			{
				if (npc_data["status"] == "success" && !updated)
				{
					std::string quan = npc_data["npcs_quantity"];
					for (int i = 0; i < std::stoi(quan); i++)
					{

						_npc_list->addItem(npc_data["list"][i]["npc"], std::to_string(i));
					}
					updated = true;
				}
			}
			catch (const std::exception&)
			{

			}

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

class CharacterUI
{
	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr _theme;
	tgui::EditBox::Ptr _character_name;
	tgui::EditBox::Ptr _character_race;
	tgui::EditBox::Ptr _character_class;
	tgui::ComboBox::Ptr _strength;
	tgui::ComboBox::Ptr _dexterity;
	tgui::ComboBox::Ptr _constitution;
	tgui::ComboBox::Ptr _inteligence;
	tgui::ComboBox::Ptr _wisdom;
	tgui::ComboBox::Ptr _charisma;
	tgui::Label::Ptr _strength_l;
	tgui::Label::Ptr _dexterity_l;
	tgui::Label::Ptr _constitution_l;
	tgui::Label::Ptr _inteligence_l;
	tgui::Label::Ptr _wisdom_l;
	tgui::Label::Ptr _charisma_l;
	tgui::ListBox::Ptr _character_list;
	tgui::Button::Ptr _create_btn;
	tgui::Button::Ptr _back_btn;
	tgui::Button::Ptr _refresh_btn;
	tgui::Picture::Ptr _back;
	bool _combo_box;

	std::string data_strength;
	std::string data_dexterity;
	std::string data_constitution;
	std::string data_intelligence;
	std::string data_wisdom;
	std::string data_charisma;
	std::string _game_session;
	json character_data;
	bool updated;

	bool create_pressed;


	void fLoadUI()
	{
		_theme = std::make_shared<tgui::Theme>("Game.txt");

		auto windowWidth = tgui::bindWidth(gui);
		auto windowHeight = tgui::bindHeight(gui);

		_theme = std::make_shared<tgui::Theme>("Game.txt");
		_back = std::make_shared<tgui::Picture>("Back.png");
		_back->setSize(tgui::bindMax(1280, windowWidth), tgui::bindMax(800, windowHeight));
		gui.add(_back);

		_character_name = _theme->load("EditBox");
		_character_name->setPosition(610, 85);
		_character_name->setSize(160, 50);
		_character_name->setDefaultText("Name");
		gui.add(_character_name);

		_character_class = _theme->load("EditBox");
		_character_class->setPosition(820, 85);
		_character_class->setSize(160, 50);
		_character_class->setDefaultText("Class");
		gui.add(_character_class);


		_character_race = _theme->load("EditBox");
		_character_race->setPosition(1030, 85);
		_character_race->setSize(160, 50);
		_character_race->setDefaultText("Race");
		gui.add(_character_race);


		_strength_l = _theme->load("Label");
		_strength_l->setPosition(610, 145);
		_strength_l->setText("Strength");
		gui.add(_strength_l);

		_dexterity_l = _theme->load("Label");
		_dexterity_l->setPosition(820, 145);
		_dexterity_l->setText("Dexterity");
		gui.add(_dexterity_l);

		_constitution_l = _theme->load("Label");
		_constitution_l->setPosition(1030, 145);
		_constitution_l->setText("Constitution");
		gui.add(_constitution_l);

		_strength = _theme->load("ComboBox");
		_strength->setSize(160, 50);
		_strength->setPosition(610, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_strength->addItem(std::to_string(i));
		}
		gui.add(_strength);

		_dexterity = _theme->load("ComboBox");
		_dexterity->setSize(160, 50);
		_dexterity->setPosition(820, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_dexterity->addItem(std::to_string(i));
		}
		gui.add(_dexterity);

		_constitution = _theme->load("ComboBox");
		_constitution->setSize(160, 50);
		_constitution->setPosition(1030, 195);
		for (int i = 1; i <= 20; ++i)
		{
			_constitution->addItem(std::to_string(i));
		}
		gui.add(_constitution);

		_inteligence_l = _theme->load("Label");
		_inteligence_l->setPosition(610, 245);
		_inteligence_l->setText("Intelligence");
		gui.add(_inteligence_l);

		_wisdom_l = _theme->load("Label");
		_wisdom_l->setPosition(820, 245);
		_wisdom_l->setText("Wisdom");
		gui.add(_wisdom_l);

		_charisma_l = _theme->load("Label");
		_charisma_l->setPosition(1030, 245);
		_charisma_l->setText("Charisma");
		gui.add(_charisma_l);

		_inteligence = _theme->load("ComboBox");
		_inteligence->setSize(160, 50);
		_inteligence->setPosition(610, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_inteligence->addItem(std::to_string(i));
		}
		gui.add(_inteligence);

		_wisdom = _theme->load("ComboBox");
		_wisdom->setSize(160, 50);
		_wisdom->setPosition(820, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_wisdom->addItem(std::to_string(i));
		}
		gui.add(_wisdom);

		_charisma = _theme->load("ComboBox");
		_charisma->setSize(160, 50);
		_charisma->setPosition(1030, 295);
		for (int i = 1; i <= 20; ++i)
		{
			_charisma->addItem(std::to_string(i));
		}
		gui.add(_charisma);

		_create_btn = _theme->load("Button");
		_create_btn->setSize(160, 50);
		_create_btn->setPosition(1030, 375);
		_create_btn->setText("Create Character");
		gui.add(_create_btn);

		_back_btn = _theme->load("Button");
		_back_btn->setSize(160, 50);
		_back_btn->setPosition(50, 665);
		_back_btn->setText("Back");
		gui.add(_back_btn);

		_refresh_btn = _theme->load("Button");
		_refresh_btn->setSize(400, 50);
		_refresh_btn->setPosition(50, 375);
		_refresh_btn->setText("Refresh Character List");
		gui.add(_refresh_btn);

		_character_list = _theme->load("ListBox");
		_character_list->setPosition(50, 85);
		_character_list->setSize(400, 240);
		gui.add(_character_list);

		_combo_box = true;

		_create_btn->connect("pressed", &CharacterUI::fCreateCharacter, this, _character_name, _character_class, _character_race);
		_refresh_btn->connect("pressed", &CharacterUI::Refresh, this);
		_back_btn->connect("pressed", &CharacterUI::fdisable, this);
	}

	void fCreateCharacter(tgui::EditBox::Ptr name, tgui::EditBox::Ptr _class, tgui::EditBox::Ptr race)
	{
		//character.fSetOwner(_game_session);

		Character character(name->getText().toAnsiString(), race->getText().toAnsiString(), _class->getText().toAnsiString(), "0", "100", "1", data_strength, data_dexterity, data_constitution, data_intelligence, data_wisdom, data_charisma, _game_session);

		std::string response;
		std::string request = character.fToJson().dump();

		http_client->fSendRequest(HttpClient::_POST, "/api/addcharacter", request);
		http_client->fGetResponse(response);
		std::cout << response << std::endl;
		_combo_box = false;
	}

	void fLoadCharacterListBox()
	{

		std::string response;

		auto request = UserActions::fLoadMyCharacters(_game_session).dump();

		http_client->fSendRequest(HttpClient::_POST, "/api/loadmycharacterslist", request);
		http_client->fGetResponse(response);
		character_data = json::parse(response);
		std::cout << character_data;
	}

	void Refresh()
	{
		fLoadCharacterListBox();
		_character_list->removeAllItems();
		updated = false;
	}

	void fdisable()
	{
		display_window = false;
	}
public:
	bool display_window;
	CharacterUI(const sf::Event &event, sf::RenderWindow &window, std::string game_session)
	{

		display_window = true;
		_game_session = game_session;
		gui.setWindow(window);
		fLoadCharacterListBox();
		updated = false;
		//_menu_option = NONE;
		fLoadUI();
		this->_event = event;
	}

	void fUpdate(sf::RenderWindow  &window)
	{

		while (window.pollEvent(_event))
		{
			if (_combo_box)
			{
				data_strength = _strength->getSelectedItem();
				data_dexterity = _dexterity->getSelectedItem();
				data_constitution = _constitution->getSelectedItem();
				data_intelligence = _inteligence->getSelectedItem();
				data_wisdom = _wisdom->getSelectedItem();
				data_charisma = _charisma->getSelectedItem();

			}
			else
			{
				_strength->deselectItem();
				_dexterity->deselectItem();
				_constitution->deselectItem();
				_inteligence->deselectItem();
				_wisdom->deselectItem();
				_charisma->deselectItem();
				_character_name->setDefaultText(" ");
				_character_race->setDefaultText(" ");
				_character_class->setDefaultText(" ");
				_combo_box = true;

			}

			try
			{
				if (character_data["status"] == "success" && !updated)
				{
					std::string quan = character_data["character_quantity"];
					for (int i = 0; i < std::stoi(quan); i++)
					{

						_character_list->addItem(character_data["list"][i]["character"], std::to_string(i));
					}
					updated = true;
				}
			}
			catch (const std::exception&)
			{

			}

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




class DM_Mode
{

	enum _selected_menu
	{
		NONE,
		TERRAIN_MENU,
		NPC_MENU,
		BACK,
	};

	sf::Event _event;
	tgui::Gui gui;

	tgui::Theme::Ptr theme;
	tgui::Picture::Ptr _main;
	tgui::Picture::Ptr _menu;
	tgui::Picture::Ptr _logo;
	tgui::Button::Ptr _btn_Terrain;
	tgui::Button::Ptr _btn_NPC;
	tgui::Button::Ptr _btn_back;
	std::string _game_session;

	_selected_menu _menu_option;
	bool _terrain;
	bool _npc;
	bool _back;
	
	NPCUI *npc_menu;

	void fClickedNpC()
	{
		 _npc = true;
	}
	void fClickedTerrain()
	{
		_terrain = true;
	}

	void fdisable()
	{
		display_window = false;
	}

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
		_btn_Terrain = theme->load("Button");
		_btn_Terrain->setSize(275, 50);
		_btn_Terrain->setPosition(145, 270);
		_btn_Terrain->setText("Terrain menu");
		gui.add(_btn_Terrain);

		_btn_NPC = theme->load("Button");
		_btn_NPC->setSize(275, 50);
		_btn_NPC->setPosition(145, 350);
		_btn_NPC->setText("NPC menu");
		gui.add(_btn_NPC);

		_btn_back = theme->load("Button");
		_btn_back->setSize(275, 50);
		_btn_back->setPosition(145, 430);
		_btn_back->setText("Back");
		gui.add(_btn_back);

		_btn_back->connect("pressed", &DM_Mode::fdisable, this);
		_btn_NPC->connect("pressed", &DM_Mode::fClickedNpC, this);
	}

public:
	bool display_window;
	DM_Mode(const sf::Event &event, sf::RenderWindow &window, std::string game_session)
	{
		display_window = true;
		_game_session = game_session;
		gui.setWindow(window);
		_menu_option = NONE;
		fLoadUI();
		this->_event = event;
	}

	void fUpdate(sf::RenderWindow  &window)
	{
		switch (_menu_option)
		{
		case DM_Mode::NONE:
		{
			while (window.pollEvent(_event))
			{
				if (_event.type == sf::Event::Closed)
					window.close();
				
				if (_npc)
				{
					npc_menu = new NPCUI(_event, window, _game_session);
					_menu_option = DM_Mode::NPC_MENU;
				}

				gui.handleEvent(_event);
			}
		}
		break;
		case DM_Mode::TERRAIN_MENU:
		{
		}
		break;
		case DM_Mode::NPC_MENU:
		{
			npc_menu->fUpdate(window);
		}
		break;
		case DM_Mode::BACK:
			break;
		}
	}
	void fDraw(sf::RenderWindow & window)
	{
		switch (_menu_option)
		{
		case DM_Mode::NONE:
		{
			gui.draw();
		}
		break;
		case DM_Mode::NPC_MENU:
		{
			if (npc_menu->display_window)
				npc_menu->fDraw(window);
			else
			{
				delete npc_menu;
				_menu_option = DM_Mode::NONE;
				_npc = false;
			}
		}
		break;
		}
	}

};


class MeinMenu
{
	enum _selected_menu
	{
		NONE,
		PLAYER_MODE,
		DM_MODE,
		EXIT,
	};

	sf::Event _event;
	tgui::Gui gui;

	DM_Mode *dm;
	CharacterUI *character;

	tgui::Theme::Ptr theme;
	tgui::Picture::Ptr _main;
	tgui::Picture::Ptr _menu;
	tgui::Picture::Ptr _logo;
	tgui::Button::Ptr _btn_player;
	tgui::Button::Ptr _btn_dm;
	tgui::Button::Ptr _btn_exit;
	std::string _game_session;
	bool _dm_m;
	bool _player_m;
	bool _exit_m;
	_selected_menu _menu_option;

	void fExit_clicked()
	{

	}
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
		_btn_player = theme->load("Button");
		_btn_player->setSize(275, 50);
		_btn_player->setPosition(145, 270);
		_btn_player->setText("Player mode");
		gui.add(_btn_player);

		_btn_dm = theme->load("Button");
		_btn_dm->setSize(275, 50);
		_btn_dm->setPosition(145, 350);
		_btn_dm->setText("DM mode");
		gui.add(_btn_dm);

		_btn_exit = theme->load("Button");
		_btn_exit->setSize(275, 50);
		_btn_exit->setPosition(145, 430);
		_btn_exit->setText("Exit");
		gui.add(_btn_exit);
		_btn_player->connect("pressed", &MeinMenu::fPlayerMode_clicked, this);
		_btn_dm->connect("pressed", &MeinMenu::fDM_Mode_clicked, this);
		_btn_exit->connect("pressed", &MeinMenu::fExit_clicked, this);
	}
	void fPlayerMode_clicked()
	{
		_player_m = true;
	}
	void fDM_Mode_clicked()
	{
		_dm_m = true;
	}
public:
	bool display_window;

	MeinMenu(const sf::Event &event, sf::RenderWindow &window, std::string game_session)
	{

		display_window = true;
		_menu_option = NONE;
		_player_m = false;
		_dm_m = false;
		this->_game_session = game_session;
		window.create(sf::VideoMode(1280, 800), "Dungeons & Dragons");
		gui.setWindow(window);
		this->_event = event;
		fLoadUI();

	}
	void fUpdate(sf::RenderWindow  &window)
	{
		switch (_menu_option)
		{
		case MeinMenu::NONE:
		{
			while (window.pollEvent(_event))
			{
				if (_event.type == sf::Event::Closed)
					window.close();

				if (_dm_m)
				{
					dm = new DM_Mode(_event, window, _game_session);
					_menu_option = DM_MODE;
				}
				if (_player_m)
				{
					character = new CharacterUI(_event, window, _game_session);
					_menu_option = PLAYER_MODE;
				}


				gui.handleEvent(_event);
			}
		}
		break;
		case MeinMenu::PLAYER_MODE:
		{
			character->fUpdate(window);
		}
		break;
		case MeinMenu::DM_MODE:
		{
			dm->fUpdate(window);
		}
		break;
		case MeinMenu::EXIT:
			break;
		}
	}

	void fDraw(sf::RenderWindow & window)
	{
		switch (_menu_option)
		{
		case MeinMenu::NONE:
		{
			gui.draw();
		}
		break;
		case MeinMenu::PLAYER_MODE:
		{
			if (character->display_window)
				character->fDraw(window);
			else
			{
				delete character;
				_menu_option = MeinMenu::NONE;
				_player_m = false;
			}
		}
		break;
		case MeinMenu::DM_MODE:
		{
			if (dm->display_window)
				dm->fDraw(window);
			else
			{
				delete dm;
				_menu_option = MeinMenu::NONE;
				_dm_m = false;
			}
		}
		break;
		case MeinMenu::EXIT:
		{

		}
		break;
		}
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

	void fLoadUI()
	{
		theme = std::make_shared<tgui::Theme>("Black.txt");


		auto windowWidth = tgui::bindWidth(gui);
		auto windowHeight = tgui::bindHeight(gui);
		
		tgui::Picture::Ptr picture = std::make_shared<tgui::Picture>("register_screen.png");
		picture->setSize(tgui::bindMax(1200, windowWidth), tgui::bindMax(400, windowHeight));
		gui.add(picture);

		editBoxUsername = theme->load("EditBox");
		editBoxUsername->setSize(300, 40);
		editBoxUsername->setPosition(60, 55);
		editBoxUsername->setDefaultText("Username");
		gui.add(editBoxUsername, "Username");

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
public:
	bool display_window;

	RegisterUser(const sf::Event &event, sf::RenderWindow &window)
	{
		display_window = true;
		window.create(sf::VideoMode(1200, 400), "Dungeons & Dragons: Registration");
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
		
		auto windowWidth = tgui::bindWidth(gui);
		auto windowHeight = tgui::bindHeight(gui);
	
		tgui::Picture::Ptr picture = std::make_shared<tgui::Picture>("login_screen.png");
		picture->setSize(tgui::bindMax(850, windowWidth), tgui::bindMax(320, windowHeight));
		gui.add(picture);

		tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
		editBoxUsername->setSize(400, 40);
		editBoxUsername->setPosition(40, 55);
		editBoxUsername->setDefaultText("Username");
		gui.add(editBoxUsername, "Username");

		tgui::EditBox::Ptr editBoxPassword = theme->load("EditBox");
		editBoxPassword->setSize(400, 40);
		editBoxPassword->setPosition(40, 120);
		editBoxPassword->setPasswordCharacter('*');
		editBoxPassword->setDefaultText("Password");
		gui.add(editBoxPassword, "Password");

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
		//window.create(sf::VideoMode(850, 320), "Dungeons & Dragons: Login");

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
					menu = new MeinMenu(_event, window, _game_session);
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
				reg_button_click = false;
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
				main_menu = false;
			}
		}
		}

	}

};


int main()
{
	sf::RenderWindow window(sf::VideoMode(850, 320), "dnd");
	sf::Event event;
	LoginForm menu(event, window);
	while (window.isOpen())
	{
		menu.fUpdate(window);
		menu.fDraw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}