#include "BoardEdit.hpp"

#include <iostream>

void BoardEdit::fLoadUiElems(sf::RenderWindow &window)
{

    _elems_combo = _theme->load("ComboBox");
    _elems_combo->setSize(200, 45);
    _elems_combo->setPosition(window.getSize().x - _elems_combo->getSize().x - 10,
                             5);

    _elems_list_box = _theme->load("ListBox");
    _elems_list_box->setSize(200, 300);
    _elems_list_box->setPosition(_elems_combo->getPosition().x,
                                 _elems_combo->getPosition().y + _elems_combo->getSize().y);

    _gui.add(_elems_list_box);
    _gui.add(_elems_combo);
}


void BoardEdit::fLoadElemsData()
{
    std::string response;
    std::string test = "{\"session_id\":\"1\"}";
    _client->fSendRequest(HttpClient::_POST, "/api/loadmynpcslist", test);
    _client->fGetResponse(response);
    _npc_data = json::parse(response.c_str());
    std::cout << _npc_data << std::endl;
    _client->fSendRequest(HttpClient::_POST, "/api/loadmyterrainslist", test);
    response = "";
    _client->fGetResponse(response);
    _terrain_data = json::parse(response.c_str());
    std::cout << _terrain_data << std::endl;
    _is_loaded = true;
}


void BoardEdit::fNPCTexturesLoader()
{
    _npc_text[0].loadFromFile("sprites/Creatures250/Goblin250.png");
    _npc_text[1].loadFromFile("sprites/Creatures250/Fairy250.png");
    _npc_text[2].loadFromFile("sprites/Creatures250/Golem250.png");
    _npc_text[3].loadFromFile("sprites/Creatures250/Dragon250.png");
    _npc_text[4].loadFromFile("sprites/Creatures250/Gremlin250.png");
    _npc_text[5].loadFromFile("sprites/Creatures250/Monk250.png");
    _npc_text[6].loadFromFile("sprites/Creatures250/Archer250.png");
    _npc_text[7].loadFromFile("sprites/Creatures250/Troglodyte.png");

    _terrain_text[0].loadFromFile("sprites/terrains/rock.png");
    _terrain_text[1].loadFromFile("sprites/terrains/water.png");
    _terrain_text[2].loadFromFile("sprites/terrains/snow.png");
    _terrain_text[3].loadFromFile("sprites/terrains/lava.png");
    _terrain_text[4].loadFromFile("sprites/terrains/shadow.png");
    _terrain_text[5].loadFromFile("sprites/terrains/tree.png");

    for (int i = 0; i <= 7; i++)
    {
        _npc_spr[i].setTexture(_npc_text[i]);
    }

    for (int i = 0; i <= 6; i++)
    {
        _terrain_spr[i].setTexture(_terrain_text[i]);
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
    _preview_el_sprite.setTexture(_terrain_text[_selected_prev_el]);
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
    _preview_el_sprite.setTexture(_npc_text[_selected_prev_el]);
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

BoardEdit::BoardEdit(const int &height, const int & width, const sf::Event & event, sf::RenderWindow &window, HttpClient* cl)
    : _load_data_thread(&BoardEdit::fLoadElemsData, this)
{
    _is_loaded = false;
    _is_setted_spawn_point = false;
    _client = cl;
    _gui.setWindow(window);
    _theme = tgui::Theme::create("sprites/Theme/Black.txt");
    _elems_unique_id_on_board = 0;
    this->_height = height;
    this->_width = width;
    this->_event = event;
    draw_window = true;
    _board_texture.loadFromFile("sprites/Back/Grid001.png");
    _board_texture.setRepeated(true);
    _board_sprite.setTexture(_board_texture);
    _cell_size = _board_sprite.getGlobalBounds().height/16.f;

    _board_sprite.setTextureRect(sf::IntRect(0, 0, _width*_cell_size, _height*_cell_size));

    _submit_button.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _submit_sprite.setTexture(_submit_button);
    _submit_sprite.setScale(0.5, 1);
    _submit_sprite.setPosition(window.getSize().x - _submit_sprite.getGlobalBounds().width,
                               window.getSize().y - _submit_sprite.getGlobalBounds().height);

    _spawn_point.setSize(sf::Vector2f(_cell_size, _cell_size));
    _spawn_point.setFillColor(sf::Color(0, 255, 0));
    _spawn_point.setPosition(-100, -100);

    _selected_elem_lbox = -1;
    _load_data_thread.launch();
    fNPCTexturesLoader();
    fLoadUiElems(window);
}

void BoardEdit::fUpdate(sf::RenderWindow & window)
{
    if (_is_loaded && _npc_data["status"] == "success")
    {
        _elems_combo->addItem("NPC", "npc");
        _elems_combo->addItem("Terrain", "terrain");
        _elems_combo->setSelectedItemById("npc");
        std::string quan = _npc_data["npcs_quantity"];
        _elems_list_box->removeAllItems();
        for (int i = 0; i < std::stoi(quan); i++)
        {
            _elems_list_box->addItem(_npc_data["list"][i]["npc"], std::to_string(i));
        }
        _is_loaded = false;
        _is_updated_list_box = true;
        _selected_combo_option = _elems_combo->getSelectedItemId();
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

    while (window.pollEvent(_event) && draw_window)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            draw_window = false;

        if (_event.type == sf::Event::Closed)
            window.close();

        // set spawn point
        if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Right)
        {
            if (_board_sprite.getGlobalBounds().contains(_event.mouseMove.x, _event.mouseMove.y))
            {
                _is_setted_spawn_point = true; //
                for (int i = 0; i < _width; i++)
                {
                    if (_event.mouseButton.x >= _cell_size*i && _event.mouseButton.x <= _cell_size*(i + 1))
                    {
                        _spawn_abs_posX = _cell_size*i;
                        _spawn_posX = i + 1;
                    }
                }

                for (int i = 0; i < _height; i++)
                {
                    if (_event.mouseButton.y >= _cell_size*i && _event.mouseButton.y <= _cell_size*(i + 1))
                    {
                        _spawn_abs_posY = _cell_size*i;
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
                    _elems_on_board.insert({ _elems_unique_id_on_board, _npc_spr[_selected_prev_el] });
                    _selected_elem_on_board = _elems_unique_id_on_board;
                    std::string id = _npc_data["list"][_selected_elem_lbox]["npc_id"];
                    _elems_on_board[_selected_elem_on_board].elem_id = id;
                }
                else if (_selected_combo_option == "terrain")
                {
                    _elems_on_board.insert({ _elems_unique_id_on_board, _terrain_spr[_selected_prev_el] });
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
                json elems_arr;
                for (auto &elems : _elems_on_board)
                {
                    if (elems.second.is_on_board)
                    {
                        json elem;
                        elem["id"]    = elems.second.elem_id;
                        elem["pos_x"] = std::to_string(elems.second.position_on_board.x);
                        elem["pos_y"] = std::to_string(elems.second.position_on_board.y);
                        elem["type"]  = elems.second.type;
                        elems_arr.push_back(elem);
                    }
                }
                if (_is_setted_spawn_point)
                {
                    json spawn_json;
                    spawn_json["pos_x"] = std::to_string(_spawn_posX);
                    spawn_json["pos_y"] = std::to_string(_spawn_posY);
                    spawn_json["type"]  = "spawn";
                    elems_arr.push_back(spawn_json);
                }

                _elems_json["data_count"] = _elems_on_board.size();
                _elems_json["data"] = elems_arr;
                std::cout << std::setw(2) << _elems_json;
            }
        }
        
        //LMB released
        if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
        {

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
                        if (_event.mouseButton.x >= _cell_size*i && _event.mouseButton.x <= _cell_size*(i + 1))
                        {
                            ssX = _cell_size*i;
                            posX = i + 1;
                            std::cout << "Texture X pos - " << posX << std::endl;
                        }
                    }

                    for (int i = 0; i < _height; i++)
                    {
                        if (_event.mouseButton.y >= _cell_size*i && _event.mouseButton.y <= _cell_size*(i + 1))
                        {
                            ssY = _cell_size*i;
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
    
    window.draw(_board_sprite);
    window.draw(_submit_sprite);
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

    if (_elems_on_board.size() > 0 && 
        _elems_on_board.find(_selected_elem_on_board) != _elems_on_board.end())
        window.draw(_elems_on_board[_selected_elem_on_board].elem_sprite);

    _gui.draw();
}
