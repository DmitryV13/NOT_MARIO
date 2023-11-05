#include "stdafx.h"
#include "Tile.h"


    Tile::Tile() {
        this->back_tile = ' ';
        this->front_tile = ' ';
        this->player = false;
        this->cord = sf::IntRect();
    }

    Tile::Tile(sf::IntRect cord_, char f_b, char b_b) : cord(cord_), front_tile(f_b), back_tile(b_b) {
        this->player = false;
    }


    void Tile::setTilePresence(bool presence){
        player = presence;
    }
    
    char Tile::give_front_tile()
    {
        return front_tile;
    }
    
    char Tile::give_back_tile()
    {
        return back_tile;
    }
    
    bool Tile::give_player_info()
    {
        return player;
    }
    
    sf::IntRect Tile::give_cord()
    {
        return cord;
    }