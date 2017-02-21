#include "Includes/TerrainForm.hpp"

void TerrainForm::fInitUIElements()
{
    _theme = std::make_shared<tgui::Theme>("Interface/Game.txt");

    auto windowWidth = tgui::bindWidth(_gui);
    auto windowHeight = tgui::bindHeight(_gui);

    _theme = std::make_shared<tgui::Theme>("Interface/Game.txt");
    _back = std::make_shared<tgui::Picture>("Interface/Back.png");
    _back->setSize(tgui::bindMax(1280, windowWidth), tgui::bindMax(800, windowHeight));
    _gui.add(_back);

    _terrain_name = _theme->load("EditBox");
    _terrain_name->setPosition(610, 85);
    _terrain_name->setSize(160, 50);
    _terrain_name->setDefaultText("Name");
    _gui.add(_terrain_name, "Name");

    _terrain_type = _theme->load("EditBox");
    _terrain_type->setPosition(610, 135);
    _terrain_type->setSize(160, 50);
    _terrain_type->setDefaultText("Type");
    _gui.add(_terrain_type, "Type");

    _terrain_width = _theme->load("EditBox");
    _terrain_width->setPosition(610, 185);
    _terrain_width->setSize(160, 50);
    _terrain_width->setDefaultText("Width");
    _gui.add(_terrain_width, "Width");

    _terrain_height = _theme->load("EditBox");
    _terrain_height->setPosition(610, 235);
    _terrain_height->setSize(160, 50);
    _terrain_height->setDefaultText("Height");
    _gui.add(_terrain_height, "Height");

    _terrain_description = _theme->load("EditBox");
    _terrain_description->setPosition(610, 285);
    _terrain_description->setSize(160, 50);
    _terrain_description->setDefaultText("Description");
    _gui.add(_terrain_description, "Description");

    _create_btn = _theme->load("Button");
    _create_btn->setSize(160, 50);
    _create_btn->setPosition(1030, 335);
    _create_btn->setText("Create Terrain");
    _gui.add(_create_btn);

    _back_btn = _theme->load("Button");
    _back_btn->setSize(160, 50);
    _back_btn->setPosition(50, 665);
    _back_btn->setText("Back");
    _gui.add(_back_btn);

    _refresh_btn = _theme->load("Button");
    _refresh_btn->setSize(400, 50);
    _refresh_btn->setPosition(50, 375);
    _refresh_btn->setText("Refresh Terrain List");
    _gui.add(_refresh_btn);

    _terrain_list = _theme->load("ListBox");
    _terrain_list->setPosition(50, 85);
    _terrain_list->setSize(400, 240);
    _gui.add(_terrain_list);



    _create_btn->connect("pressed", &TerrainForm::fCreateTerrain, this, _terrain_name, _terrain_type, _terrain_width, _terrain_height, _terrain_description);
    _refresh_btn->connect("pressed", &TerrainForm::fRefresh, this);
    _back_btn->connect("pressed", &TerrainForm::fDisable, this);
}

void TerrainForm::fCreateTerrain(tgui::EditBox::Ptr name, tgui::EditBox::Ptr type, tgui::EditBox::Ptr width, tgui::EditBox::Ptr height, tgui::EditBox::Ptr description)
{
    Terrain terrain(_game_session, name->getText().toAnsiString(), type->getText().toAnsiString(), width->getText().toAnsiString(), height->getText().toAnsiString(), description->getText().toAnsiString());
    std::string response;
    std::string request = terrain.fTerrain_To_Json().dump();
    std::cout << request << std::endl;
    _http_client->fSendRequest(HttpClient::_POST, "/api/addterrain", request);
    _http_client->fGetResponse(response);
}

void TerrainForm::fLoadNPCListBox()
{

    std::string response;
    auto request = UserActions::fLoadMyNpcs(_game_session).dump();
    std::cout << request << std::endl;

    _http_client->fSendRequest(HttpClient::_POST, "/api/loadmyterrainslist", request);
    _http_client->fGetResponse(response);
    _terrain_data = json::parse(response);
    std::cout << _terrain_data;
}

void TerrainForm::fRefresh()
{
    fLoadNPCListBox();
    _terrain_list->removeAllItems();
    _updated = false;
}

void TerrainForm::fDisable()
{
    display_window = false;
}

TerrainForm::TerrainForm(const sf::Event &event, sf::RenderWindow &window, std::string game_session, HttpClient *http_client)
{

    display_window = true;
    _game_session = game_session;
    _http_client = http_client;
    _gui.setWindow(window);
    fLoadNPCListBox();
    _updated = false;
    fInitUIElements();
    this->_event = event;
}

void TerrainForm::fUpdate(sf::RenderWindow  &window)
{

    while (window.pollEvent(_event))
    {
        try
        {
            if (_terrain_data["status"] == "success" && !_updated)
            {
                std::string quan = _terrain_data["terrains_quantity"];
                for (int i = 0; i < std::stoi(quan); i++)
                {

                    _terrain_list->addItem(_terrain_data["list"][i]["terrain"], std::to_string(i));
                }
                _updated = true;
            }
        }
        catch (const std::exception&)
        {

        }

        if (_event.type == sf::Event::Closed)
            window.close();

        _gui.handleEvent(_event);
    }
}
void TerrainForm::fDraw(sf::RenderWindow & window)
{
    _gui.draw();
}
