#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "HandleBoardElems.hpp"
#include "json.hpp"
#include "HttpClient.hpp"

using json = nlohmann::json;

class BoardEdit
{
private:
    //sfml event
    sf::Event _event;
    //

    //// TGUI ELEMS
    tgui::Gui           _gui;
    tgui::Theme::Ptr    _theme;
    tgui::ListBox::Ptr  _elems_list_box;
    tgui::ComboBox::Ptr _elems_combo;

    //// END OF TGUI ELEMS


    //handle TGUI combo
    sf::String _selected_combo_option;
    bool       _is_updated_list_box;
    int        _selected_elem_lbox;
    //

    // http thread
    sf::Thread _load_data_thread;
    bool _is_loaded;
    //

    //http client
    HttpClient* _client;
    json        _npc_data;
    json        _terrain_data;
    //

    //board size
    int _height, _width;
    float _cell_size;
    //

    // Spawn point
    int _spawn_abs_posX;
    int _spawn_abs_posY;
    int _spawn_posX;
    int _spawn_posY;
    sf::RectangleShape _spawn_point;
    bool               _is_setted_spawn_point;

    // buttons textures & sprites
    sf::Texture _submit_button;
    sf::Sprite  _submit_sprite;
    //

    // preview elem texture & sprite
    sf::Texture _preview_el_texture;
    sf::Sprite  _preview_el_sprite;
    //

    //board texture & sprite
    sf::Texture _board_texture;
    sf::Sprite  _board_sprite;
    //


    ////// Texture loader
    // npc textures
    sf::Texture _npc_text[8];
    sf::Sprite  _npc_spr[8];

    // terrain textres
    sf::Texture  _terrain_text[6];
    sf::Sprite   _terrain_spr[6];

    int         _selected_prev_el;
    //
    //////

    // npc & terrains on board
    int _elems_unique_id_on_board;
    int _selected_elem_on_board;
    json _elems_json;
    std::map<int, HandleBoardElems> _elems_on_board;
    //

    // mouse position and state handlers
    int mouseX;
    int mouseY;
    bool mouseInsideRect;
    bool dragging;
    sf::Vector2f mouseRectOffset;
    //

    // Load UI Elems
    void fLoadUiElems(sf::RenderWindow& window);

    //http data loader
    void fLoadElemsData();

    // NPC & Terrain Loader
    void fNPCTexturesLoader();
    void fLoadTerrPreview();
    void fLoadNPCPreview();
    void fLoadPreview();

public:
    bool draw_window;

    BoardEdit(const int &height, const int &width, const sf::Event &event, sf::RenderWindow &window, HttpClient* cl);
    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);

    //// Convert npcs and terrains on board to json
    //json fToJson();
};

