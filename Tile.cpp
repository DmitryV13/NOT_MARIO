#include "stdafx.h"
#include "Tile.h"


    Tile::Tile(){
        this->tileName = "Nun";
        this->player = false;
        this->interaction = 0;
        this->texture_size_W = 0;
        this->texture_size_H = 0;
        this->association = '`';
    
    }
    
    Tile::Tile(std::string Name, short int inter, float texture_size_w, float texture_size_h, char ass, TextureManager* t_manager){
        this->tileName = Name;
        this->texture_size_W = texture_size_w;
        this->texture_size_H = texture_size_h;
        this->interaction = inter;
        this->player = false;
        this->association = ass;
    
        init_texture(Name, t_manager);
    
    }

    Tile::~Tile(){
    }
    
    sf::Sprite Tile::render_tile(int i, int j){
        tile_S.setPosition(j * 64, i * 64);
        return tile_S;
    }
    
    void Tile::init_texture(std::string Name, TextureManager* t_manager){
        tile_S.setTexture(t_manager->getTexture(6, Name));
        tile_S.setTextureRect(sf::IntRect(0, 0, texture_size_W, texture_size_H));
    }
    
    bool Tile::give_player_info(){
        return player;
    }
    
    void Tile::tile_animation() {}
    
    void Tile::box_animation() {}
    
    short int Tile::get_interaction(){
        return interaction;
    }
    
    char Tile::give_tile_association() {
        return association;
    }
    
    void Tile::setTilePresence(bool presence) {
        player = presence;
    }



