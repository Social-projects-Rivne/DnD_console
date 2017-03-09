#include "Includes/PMPlayBoard.hpp"



void PMPlayBoard::fTextureLoader()
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

    sf::Texture dragonb;
    dragonb.loadFromFile("sprites/characters/dragonborn.png");
    _hero_text[0] = std::make_shared<sf::Texture>(dragonb);
    sf::Texture dwarf;
    dwarf.loadFromFile("sprites/characters/dwarf.png");
    _hero_text[1] = std::make_shared<sf::Texture>(dwarf);
    sf::Texture elf;
    elf.loadFromFile("sprites/characters/elf.png");
    _hero_text[2] = std::make_shared<sf::Texture>(elf);
    sf::Texture genasi;
    genasi.loadFromFile("sprites/characters/genasi.png");
    _hero_text[3] = std::make_shared<sf::Texture>(genasi);
    sf::Texture gnome;
    gnome.loadFromFile("sprites/characters/gnome.png");
    _hero_text[4] = std::make_shared<sf::Texture>(gnome);
    sf::Texture goliath;
    goliath.loadFromFile("sprites/characters/goliath.png");
    _hero_text[5] = std::make_shared<sf::Texture>(goliath);
    sf::Texture helf;
    helf.loadFromFile("sprites/characters/helf.png");
    _hero_text[6] = std::make_shared<sf::Texture>(helf);
    sf::Texture horc;
    horc.loadFromFile("sprites/characters/horc.png");
    _hero_text[7] = std::make_shared<sf::Texture>(horc);
    sf::Texture hing;
    hing.loadFromFile("sprites/characters/hing.png");
    _hero_text[8] = std::make_shared<sf::Texture>(hing);
    sf::Texture trif;
    trif.loadFromFile("sprites/characters/trif.png");
    _hero_text[9] = std::make_shared<sf::Texture>(trif);
    sf::Texture hum;
    hum.loadFromFile("sprites/characters/human.png");
    _hero_text[10] = std::make_shared<sf::Texture>(hum);

    for (int i = 0; i <= 5; i++)
    {
        sf::Sprite s;
        s.setTexture(*_terrain_text[i]);
        _terrain_spr[i] = std::make_shared<sf::Sprite>(s);
    }


    for (int i = 0; i <= 7; i++)
    {
        sf::Sprite s;
        s.setTexture(*_npc_text[i]);
        _npc_spr[i] = std::make_shared<sf::Sprite>(s);
    }

    for (int i = 0; i <= 10; i++)
    {
        sf::Sprite s;
        s.setTexture(*_hero_text[i]);
        _hero_spr[i] = std::make_shared<sf::Sprite>(s);
    }
}

void PMPlayBoard::fLoadBoardData()
{
    try
    {
        std::string sp_x = _board_data["spawn_x"];
        std::string sp_y = _board_data["spawn_y"];
        int spawn_x = std::stoi(sp_x) - 1;
        int spawn_y = std::stoi(sp_y) - 1;
        _spawn_abs_posX = _board_sprite.getPosition().x + _cell_size*spawn_x;
        _spawn_abs_posY = _board_sprite.getPosition().y + _cell_size*spawn_y;

        _spawn_posX = std::stoi(sp_x) + 1;
        _spawn_posY = std::stoi(sp_y) + 1;
        _spawn_point.setPosition(_spawn_abs_posX, _spawn_abs_posY);

        fLoadCharacter();
        _is_setted_spawn_point = true;
    }
    catch (const std::exception&)
    {
        _is_setted_spawn_point = false;
    }

    std::string elem_quan = _board_data["data_count"];
    for (int i = 0; i < std::stoi(elem_quan); i++)
    {
        if (_board_data["data"][i]["type"] == "npc")
        {
            std::cout << "npc";
            std::string npc_id = _board_data["data"][i]["id"];
            _elems_on_board.insert({ _elems_unique_id_on_board, *_npc_spr[std::stoi(npc_id) - 1] });
            int posX, posY, ssX, ssY;
            std::string x = _board_data["data"][i]["pos_x"];
            std::string y = _board_data["data"][i]["pos_y"];
            posX = std::stoi(x) - 1;
            posY = std::stoi(y) - 1;


            ssX = _board_sprite.getPosition().x + _cell_size*posX;
            ssY = _board_sprite.getPosition().y + _cell_size*posY;
            _elems_on_board[_elems_unique_id_on_board]
                .position_on_board = sf::Vector2i(posX + 1, posY + 1);

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
        else if (_board_data["data"][i]["type"] == "terrain")
        {
            std::cout << "terrain";
            std::string terr_id = _board_data["data"][i]["id"];
            _elems_on_board.insert({ _elems_unique_id_on_board, *_terrain_spr[std::stoi(terr_id) - 1] });
            int posX, posY, ssX, ssY;
            std::string x = _board_data["data"][i]["pos_x"];
            std::string y = _board_data["data"][i]["pos_y"];
            posX = std::stoi(x) - 1;
            posY = std::stoi(y) - 1;


            ssX = _board_sprite.getPosition().x + _cell_size*posX;
            ssY = _board_sprite.getPosition().y + _cell_size*posY;
            _elems_on_board[_elems_unique_id_on_board]
                .position_on_board = sf::Vector2i(posX + 1, posY + 1);

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

void PMPlayBoard::fLoadCharacter()
{
    std::string char_class = _char_data["race"];
    if (char_class == "Dragonborn")
    {
        _char_spr.setTexture(*_hero_text[0]);
    }
    else if (char_class == "Elf")
    {
        _char_spr.setTexture(*_hero_text[2]);
    }
    else if (char_class == "Gnome")
    {
        _char_spr.setTexture(*_hero_text[4]);
    }
    else if (char_class == "Half-Elf")
    {
        _char_spr.setTexture(*_hero_text[6]);
    }
    else if (char_class == "Half-Orc")
    {
        _char_spr.setTexture(*_hero_text[7]);
    }
    else if (char_class == "Halfling")
    {
        _char_spr.setTexture(*_hero_text[8]);
    }
    else if (char_class == "Human")
    {
        _char_spr.setTexture(*_hero_text[10]);
    }
    else if (char_class == "Trifling")
    {
        _char_spr.setTexture(*_hero_text[9]);
    }
    else if (char_class == "Genasi")
    {
        _char_spr.setTexture(*_hero_text[3]);
    }
    else if (char_class == "Goliath")
    {
        _char_spr.setTexture(*_hero_text[5]);
    }


    _char_spr.setScale(_cell_size / _char_spr.getGlobalBounds().width * _char_spr.getScale().x,
            _cell_size / _char_spr.getGlobalBounds().height * _char_spr.getScale().y);

    _char_spr.setPosition(_spawn_abs_posX, _spawn_abs_posY);

}


void PMPlayBoard::fLoadData()
{
    try
    {
        std::string response;
        std::string request = "{\"session_id\":\"" + _session_id + "\", \"board_id\": \"" + _board_id + "\"}";
        _http_client->fSendRequest(HttpClient::_POST, "/api/loadboard", request);
        _http_client->fGetResponse(response);
        _board_data = json::parse(response.c_str());
        std::cout << std::setw(2) << _board_data << std::endl;
        response = "";
        request = "{\"session_id\":\"" + _session_id + "\", \"character\": \"" + _char_id +"\"}";
        _http_client->fSendRequest(HttpClient::_POST, "/api/loaddefinedcharacter", request);
        _http_client->fGetResponse(response);
        _char_data = json::parse(response.c_str());
        std::cout << std::setw(2) << _char_data << std::endl;
        fLoadBoardData();
        _is_loaded = true;
    }
    catch (const std::exception &e)
    {

    }
}

PMPlayBoard::PMPlayBoard(const sf::Event &ev,
                         sf::RenderWindow &window,
                         HttpClient* cl,
                         const std::string &ses,
                         const int &width,
                         const int &height,
                         const std::string &b_id,
                         const std::string &c_id)
    : _load_b_data(&PMPlayBoard::fLoadData, this)
{
    _event       = ev;
    _http_client = cl;
    draw_window  = true;
    _is_loaded   = false;
    _width       = width;
    _height      = height;
    _board_id    = b_id;
    _char_id     = c_id;
    _session_id  = ses;

    _font.loadFromFile("arial.ttf");
    _board_texture.loadFromFile("sprites/Back/Grid001.png");
    _board_texture.setRepeated(true);
    _board_sprite.setTexture(_board_texture);
    _cell_size = _board_sprite.getGlobalBounds().height / 16.f;

    _board_sprite.setTextureRect(sf::IntRect(0, 0, _width*_cell_size, _height*_cell_size));
    _board_sprite.setPosition(5, 45);

    _back_btn_tex.loadFromFile("sprites/Interface/Button/LongMenuButton.png");
    _back_btn_spr.setTexture(_back_btn_tex);
    _back_btn_spr.setScale(0.5, 1);
    _back_btn_spr.setPosition(0, window.getSize().y - _back_btn_spr.getGlobalBounds().height);

    _back_txt.setString("Back");
    _back_txt.setCharacterSize(20);
    _back_txt.setFont(_font);

    _back_txt.setPosition(_back_btn_spr.getPosition().x +
        _back_btn_spr.getGlobalBounds().width / 2 -
        _back_txt.getGlobalBounds().width / 2,
        _back_btn_spr.getPosition().y +
        _back_btn_spr.getGlobalBounds().height / 2 -
        _back_txt.getGlobalBounds().height);

    fTextureLoader();
    try
    {
        _load_b_data.launch();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

void PMPlayBoard::fDraw(sf::RenderWindow & window)
{
        while (window.pollEvent(_event))
        {
            if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
            {
                if (_back_btn_spr.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    try
                    {
                        _load_b_data.terminate();
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << e.what();
                    }

                    draw_window = false;
                    break;
                }
            }
        }
}
void PMPlayBoard::fUpdate(sf::RenderWindow & window)
{
    window.draw(_board_sprite);
    for (auto& npc : _elems_on_board)
    {
        window.draw(npc.second.elem_sprite);
    }

    if (_is_setted_spawn_point)
    {
        window.draw(_char_spr);
    }

    window.draw(_back_btn_spr);
    window.draw(_back_txt);

}