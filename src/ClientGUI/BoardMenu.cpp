#include "BoardMenu.hpp"

#include <iostream>

bool BoardMenu::fCheckCell(int x, int y)
{
    return false;
}

void BoardMenu::fLoadNpcs(sf::RenderWindow &window)
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

BoardMenu::BoardMenu(const int &height,const int & width, const sf::Event & event, sf::RenderWindow &window)
{
    this->_height = height;
    this->_width = width;
    this->_event = event;
    _board_texture.loadFromFile("sprites/Back/Grid001.png");
    _board_texture.setRepeated(true);
    _board_sprite.setTexture(_board_texture);

    _board_elems_texture.loadFromFile("sprites/Interface/ControlScreen/Panels/PanelBottom.png");
    _board_elems_sprite.setTexture(_board_elems_texture);
    _board_elems_sprite.setScale(0.7, 0.6);



    _cell_size = _board_sprite.getGlobalBounds().height/16.f;

    _board_sprite.setTextureRect(sf::IntRect(0, 0, _height*_cell_size, _width*_cell_size));


    fLoadNpcs(window);
}

void BoardMenu::fUpdate(sf::RenderWindow & window)
{
    while (window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            window.close();


        if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
        {
            mouseClicked = true;
            int i = 0;
            for (auto& npc : _npc_sprites)
            {
                if (npc.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                {
                    dragging = true;
                    mouseRectOffset.x = _event.mouseButton.x - npc.getGlobalBounds().left - npc.getOrigin().x;
                    mouseRectOffset.y = _event.mouseButton.y - npc.getGlobalBounds().top - npc.getOrigin().y;
                    _selected_npc = i;

                    for (int it = 0; it < _board_npc_pos.size(); ++it)
                    {
                        if (_selected_npc == _board_npc_pos[it])
                        {
                            _board_npc_pos.erase(_board_npc_pos.begin() + it);
                            _board_elems.erase(_board_elems.begin() + it);
                        }
                    }


                    if (!_board_sprite.getGlobalBounds().contains(_event.mouseButton.x, _event.mouseButton.y))
                    {
                        _prev_pos_x = npc.getPosition().x;
                        _prev_pos_y = npc.getPosition().y;
                    }
                }
                i++;
            }
        }
        

        //LMB released
        if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
        {
            if (dragging)
            {
                _npc_sprites[_selected_npc].setColor(sf::Color(255, 255, 255));
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
                    _npc_sprites[_selected_npc].setPosition(ssX, ssY);
                    _board_elems.push_back(sf::Vector2i(posX, posY));
                    _board_npc_pos.push_back(_selected_npc);
                }
                else
                {
                    _npc_sprites[_selected_npc].setPosition(_prev_pos_x, _prev_pos_y);
                }

            }

            mouseClicked = false;
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
                        _npc_sprites[_selected_npc].setColor(sf::Color(0, 255, 0, 183));
                    }
                    else
                    {
                        _npc_sprites[_selected_npc].setColor(sf::Color(255, 0, 0, 183));
                    }
                
            }

        }
    }
    if (dragging)
    {
        _npc_sprites[_selected_npc].setPosition(mouseX - mouseRectOffset.x, mouseY - mouseRectOffset.y);
    }
}


void BoardMenu::fDraw(sf::RenderWindow & window)
{

    window.draw(_board_sprite);

    _board_elems_sprite.setPosition(window.getSize().x - _board_elems_sprite.getGlobalBounds().width, 0);

    window.draw(_board_elems_sprite);

    for (auto& npc : _npc_sprites)
    {
        window.draw(npc);
    }

}

BoardMenu::~BoardMenu()
{
}
