#include "stdafx.h"
#include "TileAnim.h"

TileAnim::TileAnim() : Tile()
{
    this->animation_factor = 0;
    this->animation_quantity = 0;
    this->animation_time = 0.0;

}

TileAnim::TileAnim(std::string Name, short int inter, float texture_size_w, float texture_size_h, char ass, short int anim_f, short int anim_q, float time)
    : Tile(Name, inter, texture_size_w, texture_size_h, ass)
{
    this->animation_factor = anim_f;
    this->animation_quantity = anim_q;
    this->animation_time = time;
}

void TileAnim::tile_animation()
{
    if (!animation_quantity) return;

    if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
    {

        sf::IntRect pos = tile_S.getTextureRect();
        pos.left += animation_factor;

        if (pos.left >= animation_factor * animation_quantity)
        {
            pos.left = pos.left - animation_factor * animation_quantity;
            tile_S.setTextureRect(pos);
        }
        tile_S.setTextureRect(pos);
        animationTimer.restart();
    }
}
