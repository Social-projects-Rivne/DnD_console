#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "HttpClient.hpp"
#include "HandleBoardElems.hpp"

using json = nlohmann::json;

class PMPlayBoard
{
private:
    //sfml event
    sf::Event _event;
    
    //http client
    HttpClient *_http_client;
    std::string _session_id;
    json        _board_data;
    json        _char_data;
    //

    //board texture & sprite
    sf::Texture _board_texture;
    sf::Sprite  _board_sprite;
    int         _cell_size;
    int         _width;
    int         _height;
    //

    //buttons
    sf::Font    _font;
    sf::Texture _back_btn_tex;
    sf::Sprite  _back_btn_spr;
    sf::Text    _back_txt;
    //


    std::string _board_id;
    std::string _char_id;
    //spawn pos
    int _spawn_abs_posX;
    int _spawn_abs_posY;
    int _spawn_posX;
    int _spawn_posY;
    sf::RectangleShape _spawn_point;
    bool               _is_setted_spawn_point;
    //

    // npc & terrains on board
    int _elems_unique_id_on_board;
    std::map<int, HandleBoardElems> _elems_on_board;
    //

    //Hero texture
    sf::Sprite  _char_spr;
    //


    // npc textures
    std::shared_ptr<sf::Texture> _npc_text[8];
    std::shared_ptr<sf::Sprite>  _npc_spr[8];

    //hero textures
    std::shared_ptr<sf::Texture> _hero_text[11];
    std::shared_ptr<sf::Sprite>  _hero_spr[11];

    // terrain textres
    std::shared_ptr<sf::Texture> _terrain_text[6];
    std::shared_ptr<sf::Sprite>   _terrain_spr[6];
    //


    //sfml thread
    sf::Thread _load_b_data;
    bool       _is_loaded;
    //

    void fTextureLoader();
    void fLoadBoardData();
    void fLoadCharacter();
    void fLoadData();

public:
    bool draw_window;

    PMPlayBoard(const sf::Event &ev, 
                sf::RenderWindow &window, 
                HttpClient* cl, 
                const std::string &ses,
                const int &width,
                const int &height,
                const std::string &b_id,
                const std::string &c_id);

    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);
};