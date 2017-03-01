#include "BoardEdit.hpp"

#include <iostream>

void BoardEdit::fLoadUiElems()
{
    _elems_list_box = _theme->load("ListBox");
    _elems_list_box->setSize(200, 300);
    _elems_list_box->setPosition(300, 50);

    _elems_combo = _theme->load("ComboBox");
    _elems_combo->setSize(200, 45);
    _elems_combo->setPosition(300, 0);

    _gui.add(_elems_list_box);
    _gui.add(_elems_combo);
}

void BoardEdit::fLoadNpcs(sf::RenderWindow &window)
{
    

    sf::Texture npc;
    npc.loadFromFile("sprites/Creatures/SkeletonWarrior60.png");
    //Troglodyte60.png
    sf::Texture npc2;
    npc2.loadFromFile("sprites/Creatures/Troglodyte60.png");
    
    sf::Texture npc3;
    npc3.loadFromFile("sprites/Creatures/EliteWizzard60.png");

    _npc_textures.push_back(std::make_shared<sf::Texture>(npc));

    

    sf::Sprite npcspr;
    npcspr.setTexture(*_npc_textures[_npc_textures.size() - 1]);
    npcspr.setScale(_cell_size / npcspr.getGlobalBounds().width, _cell_size / npcspr.getGlobalBounds().height);

    _npc_textures.push_back(std::make_shared<sf::Texture>(npc2));
    sf::Sprite npc2s;
    npc2s.setTexture(*_npc_textures[_npc_textures.size()-1]);
    npc2s.setScale(_cell_size / npc2s.getGlobalBounds().width, _cell_size / npc2s.getGlobalBounds().height);

    _npc_textures.push_back(std::make_shared<sf::Texture>(npc3));
    sf::Sprite npc3s;
    npc3s.setTexture(*_npc_textures[_npc_textures.size() - 1]);
    npc3s.setScale(_cell_size / npc3s.getGlobalBounds().width, _cell_size / npc3s.getGlobalBounds().height);

    _npc_sprites.push_back(npcspr);
    _npc_sprites.push_back(npc2s);
    _npc_sprites.push_back(npc3s);


    int i = 1;
    for (auto& npc : _npc_sprites)
    {
        npc.setPosition(window.getSize().x - _board_elems_sprite.getGlobalBounds().width + (npc.getGlobalBounds().width*i), 75);
        i++;
    }


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
}

void BoardEdit::fLoadTerrPreview()
{
}

void BoardEdit::fLoadNPCPreview()
{
    std::string elem_type = _npc_data["list"][_selected_elem_lbox]["type"];
    if (elem_type == "Elf")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Goblin250.png");
    }
    else if (elem_type == "Fey")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Fairy250.png");
    }
    else if (elem_type == "Giant")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Golem250.png");
    }
    else if (elem_type == "Dragon")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Dragon250.png");
    }
    else if (elem_type == "Goblin")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Gremlin250.png");
    }
    else if (elem_type == "Human")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Monk250.png");
    }
    else if (elem_type == "Kobold")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Archer250.png");
    }
    else if (elem_type == "Orc")
    {
        _preview_el_texture.loadFromFile("sprites/Creatures250/Troglodyte.png");
    }
    else
    {

    }
    _preview_el_sprite.setTexture(_preview_el_texture);
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
    else if (_selected_combo_option.toAnsiString() == "terr")
    {
        std::cout << "Preview of: " << _terrain_data["list"][_selected_elem_lbox]["terrain"] << std::endl;
        fLoadTerrPreview();
    }
}

BoardEdit::BoardEdit(const int &height, const int & width, const sf::Event & event, sf::RenderWindow &window, HttpClient* cl)
    : _load_data_thread(&BoardEdit::fLoadElemsData, this)
{
    _is_loaded = false;
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

    _board_elems_texture.loadFromFile("sprites/Interface/ControlScreen/Panels/PanelBottom.png");
    _board_elems_sprite.setTexture(_board_elems_texture);
    _board_elems_sprite.setScale(0.7, 0.6);

    _cell_size = _board_sprite.getGlobalBounds().height/16.f;

    _board_sprite.setTextureRect(sf::IntRect(0, 0, _width*_cell_size, _height*_cell_size));

    _submit_button.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _submit_sprite.setTexture(_submit_button);
    _submit_sprite.setScale(0.5, 1);
    _submit_sprite.setPosition(window.getSize().x - _submit_sprite.getGlobalBounds().width,
                               window.getSize().y - _submit_sprite.getGlobalBounds().height);

    _selected_elem_lbox = -1;
    _load_data_thread.launch();
    fLoadUiElems();
    fLoadNpcs(window);
}

void BoardEdit::fUpdate(sf::RenderWindow & window)
{
    if (_is_loaded && _npc_data["status"] == "success")
    {
        _elems_combo->addItem("NPC", "npc");
        _elems_combo->addItem("Terrain", "terr");
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
        else if (_selected_combo_option.toAnsiString() == "terr")
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

        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            window.close();

        if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
        {
            // handle dragging for npcs in menu
            for (auto& npc : _npc_sprites)
            {
                if (npc.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    _elems_on_board.insert({ _elems_unique_id_on_board, npc });
                    dragging = true;
                    mouseRectOffset.x = _event.mouseButton.x - npc.getGlobalBounds().left - npc.getOrigin().x;
                    mouseRectOffset.y = _event.mouseButton.y - npc.getGlobalBounds().top - npc.getOrigin().y;
                    _selected_elem_on_board = _elems_unique_id_on_board;
                    _elems_on_board[_selected_elem_on_board].type = "npc";
                }
            }

            if (_preview_el_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
            {
                _elems_on_board.insert({ _elems_unique_id_on_board, _preview_el_sprite });
                _selected_elem_on_board = _elems_unique_id_on_board;
                dragging = true;
                mouseRectOffset.x = _event.mouseButton.x - _preview_el_sprite.getGlobalBounds().left - _preview_el_sprite.getOrigin().x;
                mouseRectOffset.y = _event.mouseButton.y - _preview_el_sprite.getGlobalBounds().top -  _preview_el_sprite.getOrigin().y;
                _elems_on_board[_selected_elem_on_board].elem_sprite.setScale
                    (_cell_size / _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().width * 
                        _elems_on_board[_selected_elem_on_board].elem_sprite.getScale().x,
                     _cell_size / _elems_on_board[_selected_elem_on_board].elem_sprite.getGlobalBounds().height * 
                        _elems_on_board[_selected_elem_on_board].elem_sprite.getScale().y);
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
                        elem["id"] = std::to_string(elems.first);
                        elem["pos_x"] = std::to_string(elems.second.position_on_board.x);
                        elem["pos_y"] = std::to_string(elems.second.position_on_board.y);
                        elem["type"]  = elems.second.type;
                        elems_arr.push_back(elem);
                    }
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

    _board_elems_sprite.setPosition(window.getSize().x - _board_elems_sprite.getGlobalBounds().width, 0);

    window.draw(_board_elems_sprite);
    window.draw(_submit_sprite);

    for (auto& npc : _npc_sprites)
    {
        window.draw(npc);
    }

    for (auto& npc : _elems_on_board)
    {
        if (npc.first == _selected_elem_on_board) continue;
        window.draw(npc.second.elem_sprite);
    }

    if (_elems_on_board.size() > 0 && 
        _elems_on_board.find(_selected_elem_on_board) != _elems_on_board.end())
        window.draw(_elems_on_board[_selected_elem_on_board].elem_sprite);

    if (_selected_elem_lbox > -1)
    {
        window.draw(_preview_el_sprite);
    }

    _gui.draw();
}
