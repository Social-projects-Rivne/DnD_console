#include "Includes/BoardEdit.hpp"

#include <iostream>

void BoardEdit::fLoadUiElems(sf::RenderWindow &window)
{
	_board_name_box = _theme->load("EditBox");
	_board_name_box->setSize(300, 35);
	_board_name_box->setPosition(5, 5);

    _elems_combo = _theme->load("ComboBox");
    _elems_combo->setSize(200, 45);
    _elems_combo->setPosition(window.getSize().x - _elems_combo->getSize().x - 10,
                             5);

    _elems_list_box = _theme->load("ListBox");
    _elems_list_box->setSize(200, 300);
    _elems_list_box->setPosition(_elems_combo->getPosition().x,
                                 _elems_combo->getPosition().y + _elems_combo->getSize().y);

    _gui.add(_board_name_box);
    _gui.add(_elems_list_box);
    _gui.add(_elems_combo);
}


void BoardEdit::fLoadElemsData()
{
    try
    {
        std::string response;
        std::string request = "{\"session_id\":\"" + _session_id + "\", \"board_id\": \"" + _board_id + "\"}";
        _client->fSendRequest(HttpClient::_POST, "/api/loadmynpcslist", request);
        _client->fGetResponse(response);
        _npc_data = json::parse(response.c_str());
        std::cout << _npc_data << std::endl;
        _client->fSendRequest(HttpClient::_POST, "/api/loadmyterrainslist", request);
        response = "";
        _client->fGetResponse(response);
        _terrain_data = json::parse(response.c_str());
        std::cout << _terrain_data << std::endl;
        response = "";
        _client->fSendRequest(HttpClient::_POST, "/api/loadboard", request);
        _client->fGetResponse(response);
        
        std::cout << response;
        _old_board_data = json::parse(response.c_str());
        _board_name = _old_board_data["board"];
        std::cout << _old_board_data << std::endl;
        try
        {
            fLoadOldElems();
        }
        catch (const std::exception&e)
        {

        }
        _is_loaded = true;
    }
    catch (const std::exception&e)
    {
        std::cout << e.what() << std::endl;
    }
}


void BoardEdit::fNPCTexturesLoader()
{
    sf::Texture gobl;
    gobl.loadFromFile("sprites/Creatures250/Goblin250.png");
    _npc_text[0] = std::make_shared<sf::Texture>(gobl);
    sf::Texture fairy;
    fairy.loadFromFile("sprites/Creatures250/Fairy250.png");
    _npc_text[1] = std::make_shared<sf::Texture>(fairy);
    sf::Texture golem;
    golem.loadFromFile("sprites/Creatures250/Golem250.png");
    _npc_text[2] = std::make_shared<sf::Texture>(golem);
    sf::Texture dragon;
    dragon.loadFromFile("sprites/Creatures250/Dragon250.png");
    _npc_text[3] = std::make_shared<sf::Texture>(dragon);
    sf::Texture gremlin;
    gremlin.loadFromFile("sprites/Creatures250/Gremlin250.png");
    _npc_text[4] = std::make_shared<sf::Texture>(gremlin);
    sf::Texture monk;
    monk.loadFromFile("sprites/Creatures250/Monk250.png");
    _npc_text[5] = std::make_shared<sf::Texture>(monk);
    sf::Texture archer;
    archer.loadFromFile("sprites/Creatures250/Archer250.png");
    _npc_text[6] = std::make_shared<sf::Texture>(archer);
    sf::Texture trogl;
    trogl.loadFromFile("sprites/Creatures250/Troglodyte.png");
    _npc_text[7] = std::make_shared<sf::Texture>(trogl);


    sf::Texture rock;
    rock.loadFromFile("sprites/terrains/rock.png");
    _terrain_text[0] = std::make_shared<sf::Texture>(rock);
    sf::Texture water;
    water.loadFromFile("sprites/terrains/water.png");
    _terrain_text[1] = std::make_shared<sf::Texture>(water);
    sf::Texture snow;
    snow.loadFromFile("sprites/terrains/snow.png");
    _terrain_text[2] = std::make_shared<sf::Texture>(snow);
    sf::Texture lava;
    lava.loadFromFile("sprites/terrains/lava.png");
    _terrain_text[3] = std::make_shared<sf::Texture>(lava);
    sf::Texture shadow;
    shadow.loadFromFile("sprites/terrains/shadow.png");
    _terrain_text[4] = std::make_shared<sf::Texture>(shadow);
    sf::Texture tree;
    tree.loadFromFile("sprites/terrains/tree.png");
    _terrain_text[5] = std::make_shared<sf::Texture>(tree);

    for (int i = 0; i <= 7; i++)
    {
        sf::Sprite s;
        s.setTexture(*_npc_text[i]);
        _npc_spr[i] = std::make_shared<sf::Sprite>(s);
    }

    for (int i = 0; i <= 5; i++)
    {
        sf::Sprite s;
        s.setTexture(*_terrain_text[i]);
        _terrain_spr[i] = std::make_shared<sf::Sprite>(s);
    }
}

void BoardEdit::fLoadTerrPreview()
{
    std::string elem_type = _terrain_data["list"][_selected_elem_lbox]["type"];
    if (elem_type == "blocking")
    {
        _selected_prev_el = 0;
    }
    else if (elem_type == "difficult")
    {
        _selected_prev_el = 1;
    }
    else if (elem_type == "challenging")
    {
        _selected_prev_el = 2;
    }
    else if (elem_type == "hindering")
    {
        _selected_prev_el = 3;
    }
    else if (elem_type == "obscured")
    {
        _selected_prev_el = 4;
    }
    else if (elem_type == "cover")
    {
        _selected_prev_el = 5;
    }
    _preview_el_sprite.setTexture(*_terrain_text[_selected_prev_el]);
    _preview_el_sprite.setPosition(_elems_list_box->getPosition().x, _elems_list_box->getPosition().y + _elems_list_box->getSize().y + 10);

}

void BoardEdit::fLoadNPCPreview()
{
    std::string elem_type = _npc_data["list"][_selected_elem_lbox]["type"];
    if (elem_type == "Elf")
    {
        _selected_prev_el = 0;
    }
    else if (elem_type == "Fey")
    {
        _selected_prev_el = 1;
    }
    else if (elem_type == "Giant")
    {
        _selected_prev_el = 2;
    }
    else if (elem_type == "Dragon")
    {
        _selected_prev_el = 3;
    }
    else if (elem_type == "Goblin")
    {
        _selected_prev_el = 4;
    }
    else if (elem_type == "Human")
    {
        _selected_prev_el = 5;
    }
    else if (elem_type == "Kobold")
    {
        _selected_prev_el = 6;
    }
    else if (elem_type == "Orc")
    {
        _selected_prev_el = 7;
    }
    else
    {
        _selected_prev_el = 0;
    }
    _preview_el_sprite.setTexture(*_npc_text[_selected_prev_el]);
    _preview_el_sprite.setPosition(_elems_list_box->getPosition().x, _elems_list_box->getPosition().y + _elems_list_box->getSize().y + 10);
    _preview_el_sprite.setScale(0.5, 0.5);
    
}

void BoardEdit::fLoadPreview()
{
    std::cout << "inside" << std::endl;
    if (_selected_combo_option.toAnsiString() == "npc")
    {
        std::cout << "Preview of: " << _npc_data["list"][_selected_elem_lbox]["npc"] << std::endl;
        fLoadNPCPreview();
    }
    else if (_selected_combo_option.toAnsiString() == "terrain")
    {
        std::cout << "Preview of: " << _terrain_data["list"][_selected_elem_lbox]["terrain"] << std::endl;
        fLoadTerrPreview();
    }
}

void BoardEdit::fUploadData()
{
	_load_data_thread.wait();
    json elems_arr;
    int count = 0;
    for (auto &elems : _elems_on_board)
    {
        if (elems.second.is_on_board)
        {
            if (elems.second.position_on_board.x <= 0 || elems.second.position_on_board.y <= 0)
                continue;
            json elem;
            elem["id"]    = elems.second.elem_id;
            elem["pos_x"] = std::to_string(elems.second.position_on_board.x);
            elem["pos_y"] = std::to_string(elems.second.position_on_board.y);
            elem["type"]  = elems.second.type;
            elems_arr.push_back(elem);
            count++;
        }
    }
    if (_is_setted_spawn_point)
    {
        _upload_data["spawn_x"] = std::to_string(_spawn_posX);
        _upload_data["spawn_y"] = std::to_string(_spawn_posY);
    }
    _upload_data["data_count"] = std::to_string(count);
    _upload_data["name"]       = _board_name_box->getText().toAnsiString();
    _upload_data["board_id"]   = _board_id;
    _upload_data["data"] = elems_arr;
    std::cout << std::setw(2) << _upload_data;
    _upload_data["session_id"] = _session_id;


    //// send to server
    std::string response;
    _client->fSendRequest(HttpClient::_POST, "/api/editboard", _upload_data.dump());
    _client->fGetResponse(response);

    _upload_response = json::parse(response);
    std::cout << std::setw(2) << _upload_response;

}

void BoardEdit::fLoadOldElems()
{
    try
    {
        std::string sp_x = _old_board_data["spawn_x"];
        std::string sp_y = _old_board_data["spawn_y"];
        int spawn_x = std::stoi(sp_x) - 1;
        int spawn_y = std::stoi(sp_y) - 1;
        _spawn_abs_posX = _board_sprite.getPosition().x + _cell_size*spawn_x;
        _spawn_abs_posY = _board_sprite.getPosition().y + _cell_size*spawn_y;

        _spawn_posX = std::stoi(sp_x) + 1;
        _spawn_posY = std::stoi(sp_y) + 1;
        _spawn_point.setPosition(_spawn_abs_posX, _spawn_abs_posY);

        _is_setted_spawn_point = true;
    }
    catch (const std::exception&)
    {
        _is_setted_spawn_point = false;
    }

    std::string elem_quan = _old_board_data["data_count"];
    for (int i = 0; i < std::stoi(elem_quan); i++)
    {
        if (_old_board_data["data"][i]["type"] == "npc")
        {
            std::cout << "npc";
            std::string npc_id = _old_board_data["data"][i]["id"];
            _elems_on_board.insert({ _elems_unique_id_on_board, *_npc_spr[std::stoi(npc_id)-1] });
            int posX, posY, ssX, ssY;
            std::string x = _old_board_data["data"][i]["pos_x"];
            std::string y = _old_board_data["data"][i]["pos_y"];
            posX = std::stoi(x) - 1;
            posY = std::stoi(y) - 1;


            ssX = _board_sprite.getPosition().x + _cell_size*posX;
            ssY = _board_sprite.getPosition().y + _cell_size*posY;
            _elems_on_board[_elems_unique_id_on_board]
                .position_on_board = sf::Vector2i(posX+1, posY+1);

            _elems_on_board[_elems_unique_id_on_board]
                .position = sf::Vector2i(ssX, ssY);

            _elems_on_board[_elems_unique_id_on_board]
                .elem_sprite.setPosition(ssX, ssY);

            _elems_on_board[_elems_unique_id_on_board].elem_sprite.setScale
                (_cell_size / _elems_on_board[_elems_unique_id_on_board].elem_sprite.getGlobalBounds().width *
                    _elems_on_board[_elems_unique_id_on_board].elem_sprite.getScale().x,
                    _cell_size / _elems_on_board[_elems_unique_id_on_board].elem_sprite.getGlobalBounds().height *
                    _elems_on_board[_elems_unique_id_on_board].elem_sprite.getScale().y);

            _elems_on_board[_elems_unique_id_on_board].type = "npc";
            _elems_on_board[_elems_unique_id_on_board].is_on_board = true;
            _elems_on_board[_elems_unique_id_on_board].elem_id = npc_id;

            _elems_unique_id_on_board++;
        }
        else if (_old_board_data["data"][i]["type"] == "terrain")
        {
            std::cout << "terrain";
            std::string terr_id = _old_board_data["data"][i]["id"];
            _elems_on_board.insert({ _elems_unique_id_on_board, *_terrain_spr[std::stoi(terr_id) - 1] });
            int posX, posY, ssX, ssY;
            std::string x = _old_board_data["data"][i]["pos_x"];
            std::string y = _old_board_data["data"][i]["pos_y"];
            posX = std::stoi(x) - 1;
            posY = std::stoi(y) - 1;


            ssX = _board_sprite.getPosition().x + _cell_size*posX;
            ssY = _board_sprite.getPosition().y + _cell_size*posY;
            _elems_on_board[_elems_unique_id_on_board]
                .position_on_board = sf::Vector2i(posX+1, posY+1);

            _elems_on_board[_elems_unique_id_on_board]
                .position = sf::Vector2i(ssX, ssY);

            _elems_on_board[_elems_unique_id_on_board]
                .elem_sprite.setPosition(ssX, ssY);

            _elems_on_board[_elems_unique_id_on_board].elem_sprite.setScale
                (_cell_size / _elems_on_board[_elems_unique_id_on_board].elem_sprite.getGlobalBounds().width *
                    _elems_on_board[_elems_unique_id_on_board].elem_sprite.getScale().x,
                    _cell_size / _elems_on_board[_elems_unique_id_on_board].elem_sprite.getGlobalBounds().height *
                    _elems_on_board[_elems_unique_id_on_board].elem_sprite.getScale().y);

            _elems_on_board[_elems_unique_id_on_board].type = "npc";
            _elems_on_board[_elems_unique_id_on_board].is_on_board = true;
            _elems_on_board[_elems_unique_id_on_board].elem_id = terr_id;

            _elems_unique_id_on_board++;
        }
    }
}


BoardEdit::BoardEdit(const int &height,
		             const int & width,
		             const std::string & board_id,
					 const sf::Event & event,
					 sf::RenderWindow &window,
					 HttpClient* cl,
                     const std::string &ses)
    : _load_data_thread(&BoardEdit::fLoadElemsData, this), _upload_thread(&BoardEdit::fUploadData, this)
{
    _session_id = ses;
	_board_id = board_id;
	_is_uploaded = false;
    _is_loaded = false;
    _is_setted_spawn_point = false;
    _client = cl;
    _gui.setWindow(window);
    _theme = tgui::Theme::create("sprites/Theme/Black.txt");
    fLoadUiElems(window);
    _elems_unique_id_on_board = 0;
    this->_height = height;
    this->_width = width;
    this->_event = event;
    draw_window = true;
    _font.loadFromFile("arial.ttf");
    _board_texture.loadFromFile("sprites/Back/Grid001.png");
    _board_texture.setRepeated(true);
    _board_sprite.setTexture(_board_texture);
    _cell_size = _board_sprite.getGlobalBounds().height / 16.f;

    _board_sprite.setTextureRect(sf::IntRect(0, 0, _width*_cell_size, _height*_cell_size));
    _board_sprite.setPosition(5, 45);

    _submit_button.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _submit_sprite.setTexture(_submit_button);
    _submit_sprite.setScale(0.5, 1);
    _submit_sprite.setPosition(window.getSize().x - _submit_sprite.getGlobalBounds().width,
        window.getSize().y - _submit_sprite.getGlobalBounds().height);

    _back_btn_tex.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _back_btn_spr.setTexture(_back_btn_tex);
    _back_btn_spr.setScale(0.5, 1);
    _back_btn_spr.setPosition(0, window.getSize().y - _back_btn_spr.getGlobalBounds().height);

    _spawn_point.setSize(sf::Vector2f(_cell_size, _cell_size));
    _spawn_point.setFillColor(sf::Color(0, 255, 0, 133));
    _spawn_point.setPosition(-100, -100);

    _submit_txt.setString("Submit");
    _submit_txt.setCharacterSize(20);
    _submit_txt.setFont(_font);
    _back_txt.setString("Back");
    _back_txt.setCharacterSize(20);
    _back_txt.setFont(_font);
    
    _submit_txt.setPosition(_submit_sprite.getPosition().x +
        _submit_sprite.getGlobalBounds().width / 2 -
        _submit_txt.getGlobalBounds().width / 2,
        _submit_sprite.getPosition().y +
        _submit_sprite.getGlobalBounds().height / 2 -
        _submit_txt.getGlobalBounds().height);

    _back_txt.setPosition(_back_btn_spr.getPosition().x +
        _back_btn_spr.getGlobalBounds().width / 2 -
        _back_txt.getGlobalBounds().width / 2,
        _back_btn_spr.getPosition().y +
        _back_btn_spr.getGlobalBounds().height / 2 -
        _back_txt.getGlobalBounds().height);



    _selected_elem_lbox = -1;
    fNPCTexturesLoader();
    _load_data_thread.launch();
}

void BoardEdit::fUpdate(sf::RenderWindow & window)
{
    try
    {

        if (_is_loaded && _npc_data["status"] == "success" || _npc_data["status"] == "warning")
        {
            _board_name_box->setText(_board_name);
            _elems_combo->addItem("NPC", "npc");
            _elems_combo->addItem("Terrain", "terrain");
            _elems_combo->setSelectedItemById("npc");
            std::string quan = _npc_data["npcs_quantity"];
            _elems_list_box->removeAllItems();
            for (int i = 0; i < std::stoi(quan); i++)
            {
                _elems_list_box->addItem(_npc_data["list"][i]["npc"], std::to_string(i));
            }
            _is_updated_list_box = true;
            _selected_combo_option = _elems_combo->getSelectedItemId();
            _is_loaded = false;
        }

        if (_elems_combo->getSelectedItemId() != _selected_combo_option)
        {
            _is_updated_list_box = false;
            _selected_combo_option = _elems_combo->getSelectedItemId();
        }

        if (!_is_updated_list_box)
        {
            if (_selected_combo_option.toAnsiString() == "npc")
            {
                _elems_list_box->removeAllItems();
                if (_npc_data["status"] == "success")
                {
                    std::string quan = _npc_data["npcs_quantity"];
                    for (int i = 0; i < std::stoi(quan); i++)
                    {
                        _elems_list_box->addItem(_npc_data["list"][i]["npc"], std::to_string(i));
                    }
                }
            }
            else if (_selected_combo_option.toAnsiString() == "terrain")
            {
                _elems_list_box->removeAllItems();
                if (_terrain_data["status"] == "success")
                {
                    std::string quan = _terrain_data["terrains_quantity"];
                    for (int i = 0; i < std::stoi(quan); i++)
                    {
                        _elems_list_box->addItem(_terrain_data["list"][i]["terrain"], std::to_string(i));
                    }
                }
            }
            _is_updated_list_box = true;
        }

    }
    catch (const std::exception&)
    {

    }
    while (window.pollEvent(_event) && draw_window)
    {
        if (_event.type == sf::Event::Closed)
            window.close();

        // set spawn point
        if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Right)
        {
            if (_board_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
            {
                _is_setted_spawn_point = true; //
                for (int i = 0; i < _width; i++)
                {
                    if (_event.mouseButton.x >= _board_sprite.getPosition().x + _cell_size*i &&
                        _event.mouseButton.x <= _board_sprite.getPosition().x + _cell_size*(i + 1))
                    {
                        _spawn_abs_posX = _board_sprite.getPosition().x + _cell_size*i;
                        _spawn_posX = i + 1;
                    }
                }

                for (int i = 0; i < _height; i++)
                {
                    if (_event.mouseButton.y >= _board_sprite.getPosition().y + _cell_size*i &&
                    	_event.mouseButton.y <= _board_sprite.getPosition().y + _cell_size*(i + 1))
                    {
                        _spawn_abs_posY = _board_sprite.getPosition().y + _cell_size*i;
                        _spawn_posY = i + 1;
                    }
                }

                for (auto& npc : _elems_on_board)
                {
                    if (npc.second.position_on_board.x == _spawn_posX &&
                        npc.second.position_on_board.y == _spawn_posY)
                    {
                        _is_setted_spawn_point = false;
                        break;
                    }
                }

                if (_is_setted_spawn_point)
                {
                    _spawn_point.setPosition(_spawn_abs_posX, _spawn_abs_posY);
                }
                else
                {
                    _spawn_abs_posX = -1000;
                    _spawn_abs_posY = -1000;
                }
            }
            else
            {
                _is_setted_spawn_point = false;
            }
        }


        if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
        {
            // handle dragging for npcs in menu
            if (_preview_el_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
            {
                if (_selected_combo_option == "npc")
                {
                    _elems_on_board.insert({ _elems_unique_id_on_board, *_npc_spr[_selected_prev_el] });
                    _selected_elem_on_board = _elems_unique_id_on_board;
                    std::string id = _npc_data["list"][_selected_elem_lbox]["npc_id"];
                    _elems_on_board[_selected_elem_on_board].elem_id = id;
                }
                else if (_selected_combo_option == "terrain")
                {
                    _elems_on_board.insert({ _elems_unique_id_on_board, *_terrain_spr[_selected_prev_el] });
                    _selected_elem_on_board = _elems_unique_id_on_board;
                    std::string id = _terrain_data["list"][_selected_elem_lbox]["terrain_id"];
                    _elems_on_board[_selected_elem_on_board].elem_id = id;
                }

                _elems_on_board[_selected_elem_on_board].elem_sprite.setScale
                    (_cell_size / _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().width * 
                        _elems_on_board[_selected_elem_on_board].elem_sprite.getScale().x,
                     _cell_size / _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().height * 
                        _elems_on_board[_selected_elem_on_board].elem_sprite.getScale().y);
                _elems_on_board[_selected_elem_on_board].type    = _selected_combo_option;

                dragging = true;
                _elems_on_board[_selected_elem_on_board].elem_sprite.setPosition(
                    _event.mouseButton.x - (_cell_size/2),
                    _event.mouseButton.y - (_cell_size/2));

                mouseRectOffset.x = _event.mouseButton.x - _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().left 
                     - _elems_on_board[_selected_elem_on_board].elem_sprite.getOrigin().x;
                mouseRectOffset.y = _event.mouseButton.y - _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().top 
                     - _elems_on_board[_selected_elem_on_board].elem_sprite.getOrigin().y;

            }


            //handle dragging for npcs on board
            for (auto& npc : _elems_on_board)
            {
                if (npc.second.elem_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    _selected_elem_on_board = npc.first;
                    dragging = true;
                    mouseRectOffset.x = _event.mouseButton.x - npc.second.elem_sprite.getGlobalBounds().left - npc.second.elem_sprite.getOrigin().x;
                    mouseRectOffset.y = _event.mouseButton.y - npc.second.elem_sprite.getGlobalBounds().top - npc.second.elem_sprite.getOrigin().y;
                    break;
                }
            }

            if (_submit_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
            {
            	_upload_thread.launch();
            }
        }
        
        //LMB released
        if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
        {
            if (_back_btn_spr.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
            {
                try
                {
                    _load_data_thread.terminate();
                    _upload_thread.terminate();
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what();
                }
                draw_window = false;
            }

            if (_elems_list_box->getPosition().x <= _event.mouseButton.x &&
                _elems_list_box->getPosition().x + _elems_list_box->getSize().x >= _event.mouseButton.x &&
                _elems_list_box->getPosition().y <= _event.mouseButton.y &&
                _elems_list_box->getPosition().y + _elems_list_box->getSize().y >= _event.mouseButton.y)
            {
                std::string tmp = _elems_list_box->getSelectedItemId().toAnsiString();
                try
                {
                    _selected_elem_lbox = std::stoi(tmp);
                    fLoadPreview();
                }
                catch (const std::exception&)
                {
                    _selected_elem_lbox = -1;
                }
                std::cout << _selected_elem_lbox;
            }


            if (dragging)
            {

                _elems_on_board[_selected_elem_on_board].elem_sprite.setColor(sf::Color(255, 255, 255));

                if (_board_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    int ssX = 0;
                    int ssY = 0;

                    int posX = 0;
                    int posY = 0;

                    for (int i = 0; i < _width; i++)
                    {
                        if (_event.mouseButton.x >= _board_sprite.getPosition().x + _cell_size*i &&
                        	_event.mouseButton.x <= _board_sprite.getPosition().x + _cell_size*(i + 1))
                        {
                            ssX = _board_sprite.getPosition().x + _cell_size*i;
                            posX = i + 1;
                            std::cout << "Texture X pos - " << posX << std::endl;
                        }
                    }

                    for (int i = 0; i < _height; i++)
                    {
                        if (_event.mouseButton.y >= _board_sprite.getPosition().y + _cell_size*i &&
                        	_event.mouseButton.y <= _board_sprite.getPosition().y + _cell_size*(i + 1))
                        {
                            ssY = _board_sprite.getPosition().y + _cell_size*i;
                            posY = i + 1;
                            std::cout << "Texture Y pos - " << posY << std::endl;
                        }
                    }

                    if (_elems_unique_id_on_board <= _selected_elem_on_board) _elems_unique_id_on_board++;

                    for (auto& npc : _elems_on_board)
                    {
                        if (npc.first == _selected_elem_on_board)
                        {
                            _elems_on_board[_selected_elem_on_board].elem_sprite.setPosition(ssX, ssY);
                            _elems_on_board[_selected_elem_on_board].position_on_board.x = posX;
                            _elems_on_board[_selected_elem_on_board].position_on_board.y = posY;
                            _elems_on_board[_selected_elem_on_board].position.x = ssX;
                            _elems_on_board[_selected_elem_on_board].position.y = ssY;
                            _elems_on_board[_selected_elem_on_board].is_on_board = true;
                            continue;
                        }

                        if (npc.second.position.x <= _event.mouseButton.x &&
                            npc.second.position.x + _cell_size >= _event.mouseButton.x &&
                            npc.second.position.y <= _event.mouseButton.y &&
                            npc.second.position.y + _cell_size >= _event.mouseButton.y)
                        {
                            auto del = _elems_on_board.find(_selected_elem_on_board);
                            _elems_on_board.erase(del);
                            std::cout << "\nDeleted\n";
                        }
                    }
                    if (_spawn_abs_posX <= _event.mouseButton.x &&
                        _spawn_abs_posX + _cell_size >= _event.mouseButton.x &&
                        _spawn_abs_posY <= _event.mouseButton.y &&
                        _spawn_abs_posY + _cell_size >= _event.mouseButton.y)
                    {
                        auto del = _elems_on_board.find(_selected_elem_on_board);
                        _elems_on_board.erase(del);
                        std::cout << "\nDeleted\n";
                    }

                }
                else
                {
                    auto del = _elems_on_board.find(_selected_elem_on_board);
                    _elems_on_board.erase(del);
                    std::cout << "\nDeleted\n";
                }

            }

            dragging = false;
        }

        if (_event.type == sf::Event::MouseMoved)
        {

            mouseX = _event.mouseMove.x;
            mouseY = _event.mouseMove.y;
            if (dragging)
            {
                if (_board_sprite.getGlobalBounds().contains(_event.mouseMove.x, _event.mouseMove.y))
                {
                    _elems_on_board[_selected_elem_on_board].elem_sprite.setColor(sf::Color(0, 255, 0));
                    for (auto& npc : _elems_on_board)
                    {

                        if (npc.second.position.x <= _event.mouseMove.x &&
                            npc.second.position.x + _cell_size >= _event.mouseMove.x &&
                            npc.second.position.y <= _event.mouseMove.y &&
                            npc.second.position.y + _cell_size >= _event.mouseMove.y &&
                            npc.first != _selected_elem_on_board)
                        {
                            _elems_on_board[_selected_elem_on_board].elem_sprite.setColor(sf::Color(255, 0, 0));
                            //std::cout << "Ins";
                        }
                    }
                    if (_spawn_abs_posX <= _event.mouseMove.x &&
                        _spawn_abs_posX + _cell_size >= _event.mouseMove.x &&
                        _spawn_abs_posY <= _event.mouseMove.y &&
                        _spawn_abs_posY + _cell_size >= _event.mouseMove.y)
                    {
                        _elems_on_board[_selected_elem_on_board].elem_sprite.setColor(sf::Color(255, 0, 0));
                    }
                }
                else
                {
                    _elems_on_board[_selected_elem_on_board].elem_sprite.setColor(sf::Color(255, 0, 0, 183));
                }
            }

        }
        _gui.handleEvent(_event);
    }
    if (dragging)
    {
        _elems_on_board[_selected_elem_on_board].elem_sprite.setPosition(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y);
    }
}

void BoardEdit::fDraw(sf::RenderWindow & window)
{

    _gui.draw();
    window.draw(_board_sprite);

    for (auto& npc : _elems_on_board)
    {
        if (npc.first == _selected_elem_on_board) continue;
        window.draw(npc.second.elem_sprite);
    }

    if (_is_setted_spawn_point)
    {
        window.draw(_spawn_point);
    }

    if (_selected_elem_lbox > -1 && !dragging)
    {
        window.draw(_preview_el_sprite);
    }

    window.draw(_back_btn_spr);
    window.draw(_back_txt);

    window.draw(_submit_sprite);
    window.draw(_submit_txt);

    if (_elems_on_board.size() > 0 && 
        _elems_on_board.find(_selected_elem_on_board) != _elems_on_board.end())
        window.draw(_elems_on_board[_selected_elem_on_board].elem_sprite);
}


