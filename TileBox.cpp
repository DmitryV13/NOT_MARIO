#include "stdafx.h"
#include "TileBox.h"

TileBox::TileBox() : TileAnim() {}

TileBox::TileBox(std::string Name, short int inter, short int texture_size_w,short int texture_size_h, char ass, short int anim_f, short int anim_q, float time)
	: TileAnim(Name, inter, texture_size_w, texture_size_h, ass,  anim_f, anim_q, time) {}

void TileBox::open_box()
{
    open = true;
}

void TileBox::close_box()
{
    open = false;
}

void TileBox::box_animation()
{ 
    if (open) 
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = tile_S.getTextureRect();
            pos.left += animation_factor;

            if (pos.left >= animation_factor * animation_quantity)
            {
                pos.left -= animation_factor;
                tile_S.setTextureRect(pos);
                return;
            }
            tile_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
    else
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = tile_S.getTextureRect();
            pos.left -= animation_factor;

            if (pos.left < 0)
            {
                pos.left += animation_factor;
                tile_S.setTextureRect(pos);
                return;
            }
            tile_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }

}
