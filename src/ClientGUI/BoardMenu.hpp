#pragma once
#include "SFML\Graphics.hpp"
#include "HandleBoardElems.hpp"
#include <memory>

class BoardMenu
{
private:
    //sfml event
    sf::Event _event;
    //board size
    int _height, _width;
    float _cell_size;

    //board ui
    sf::Texture _board_elems_texture;
    sf::Sprite  _board_elems_sprite;

    //board texture & sprite
    sf::Texture _board_texture;
    sf::Sprite  _board_sprite;

    //npc & terrain textures
    std::vector<std::shared_ptr<sf::Texture>> _npc_textures;
    std::vector<std::shared_ptr<sf::Texture>> _terrain_textures;

    //npc & terrain sprites in menu
    std::vector<sf::Sprite>  _npc_sprites;
    std::vector<sf::Sprite>  _terrain_sprites;

    // npc & terrains on board
    int _npc_id_on_board;
    int _selected_npc_on_board;
    std::map<int, HandleBoardElems> _npc_on_board;


    //store elements on board
    std::vector<sf::Vector2i> _board_elems;
    std::vector<int>          _board_npc_pos;


    int _drag_pos_x;
    int _drag_pos_y;
    int _prev_pos_x;
    int _prev_pos_y;
    int mouseX;
    int mouseY;
    int _selected_npc;
    bool mouseInsideRect;
    bool dragging;
    sf::Vector2f mouseRectOffset;



    void fCloneNpc(const sf::Sprite &sprite);
    bool fCheckCell(int x, int y);
    void fLoadNpcs(sf::RenderWindow &window);
public:
    BoardMenu(const int &height, const int &width, const sf::Event &event, sf::RenderWindow &window);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);

    ~BoardMenu();
};

