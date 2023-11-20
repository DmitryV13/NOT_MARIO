#include "stdafx.h"
#include "Tile.h"

    Tile::Tile() 
    {
        this->player = false;
        this->back_tile = ' ';
        this->front_tile = ' ';
        this->interaction = 0;
        this->animation_factor = 0;
        this->cord = new sf::IntRect();
    }
    
    Tile::Tile(sf::IntRect cord_, char f_b, char b_b, short int inter, short int anim_factor, short int anim_quantity) :
        cord(new sf::IntRect()),
        back_tile(b_b),
        front_tile(f_b), 
        interaction(inter), 
        animation_factor(anim_factor), 
        animation_quantity(anim_quantity)
    {
        cord->left = cord_.left;
        cord->top = cord_.top;
        cord->width = cord_.width;
        cord->height = cord_.height;
        this->player = false;
    }

    void Tile::tile_animation() 
    {
        if (!animation_quantity) return;
    
        if (animationTimer.getElapsedTime().asSeconds() >= 0.5f) 
        {
            cord->left += animation_factor;
            if (cord->left >= animation_factor * animation_quantity)
            {
            cord->left = cord->left - animation_factor * animation_quantity;
            }
            animationTimer.restart();
        }
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
        return false;
       // return player;
    }
    
    sf::IntRect* Tile::give_cord()
    {
        return cord;
    }

    void Tile::set_cord(sf::IntRect cord_)
    {
        cord->left = cord_.left;
        cord->top = cord_.top;
        cord->width = cord_.width;
        cord->height = cord_.height;
    } 

    void Tile::set_interaction(short int curr)
    {
        this->interaction;
    }


