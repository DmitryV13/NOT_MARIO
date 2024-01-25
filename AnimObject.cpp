#include "stdafx.h"
#include "AnimObject.h"

AnimObject::AnimObject() : Object()
{
    object_type = OBJECT_TYPE::ANIM_OBJECT;
    this->animation_factor = 0;
    this->animation_quantity = 0;
    this->animation_time = 0.0;
}

AnimObject::AnimObject(std::string name, float position_x, float position_y, short int size_W, short int size_H, 
    short int anim_factor, short int anim_quantity, float anim_time) : Object(name, position_x, position_y, size_W, size_H)
{
    object_type = OBJECT_TYPE::ANIM_OBJECT;
    this->animation_factor = anim_factor;
    this->animation_quantity = anim_quantity;
    this->animation_time = anim_time;
}

void AnimObject::animation_object()
{
    if (!animation_quantity) return;

    if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
    {
        sf::IntRect pos = object_S.getTextureRect();
        pos.left += animation_factor;

        if (pos.left >= animation_factor * animation_quantity)
        {
            pos.left = pos.left - animation_factor * animation_quantity;
            object_S.setTextureRect(pos);
        }
        object_S.setTextureRect(pos);
        animationTimer.restart();
    }
}
