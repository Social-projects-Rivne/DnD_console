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
    std::string         _session_id;
    //// TGUI ELEMS
    tgui::Gui           _gui;
    tgui::Theme::Ptr    _theme;
    tgui::ListBox::Ptr  _elems_list_box;
    tgui::ComboBox::Ptr _elems_combo;
    tgui::EditBox::Ptr  _board_name_box;

    //// END OF TGUI ELEMS


    //handle TGUI combo
    sf::String _selected_combo_option;
    bool       _is_updated_list_box;
    int        _selected_elem_lbox;
    //

    // http thread
    sf::Thread _load_data_thread;
    bool _is_loaded;

    sf::Thread _upload_thread;
    bool _is_uploaded;
    //

    //http client
    HttpClient* _client;
    json        _npc_data;
    json        _terrain_data;
    json        _upload_data;
    json        _upload_response;
    json        _old_board_data;
    //

    //board data
    std::string _board_id;
    std::string _board_name;
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
    sf::Font    _font;
    sf::Texture _submit_button;
    sf::Sprite  _submit_sprite;
    sf::Text    _submit_txt;
    sf::Texture _back_btn_tex;
    sf::Sprite  _back_btn_spr;
    sf::Text    _back_txt;
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
    std::shared_ptr<sf::Texture> _npc_text[8];
    std::shared_ptr<sf::Sprite>  _npc_spr[8];

    // terrain textres
    std::shared_ptr<sf::Texture> _terrain_text[6];
    std::shared_ptr<sf::Sprite>   _terrain_spr[6];

    int         _selected_prev_el;
    //
    //////

    // npc & terrains on board
    int _elems_unique_id_on_board;
    int _selected_elem_on_board;
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
    void fUploadData();
    void fLoadOldElems();

public:
    bool draw_window;

    BoardEdit(const int &height,
    		  const int &width,
			  const std::string &id,
			  const sf::Event &event,
			  sf::RenderWindow &window,
			  HttpClient* cl,
              const std::string &ses);
    void fUpdate(sf::RenderWindow &window);
    void fDraw(sf::RenderWindow &window);


};

