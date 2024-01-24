#include "stdafx.h"
#include "chest.h"

Chest::Chest() : AnimObject()
{
    object_type = OBJECT_TYPE::CHEST;
	this->opened = false;
}

Chest::Chest(std::string name, float position_x, float position_y, short int size_W, short int size_H, short int anim_factor, short int anim_quantity, float anim_time) 
	: AnimObject(name, position_x, position_y, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
    object_type = OBJECT_TYPE::CHEST;
	this->opened = false;
}

void Chest::useObject()
{
    if (opened) opened = false;
    opened = true;
}

void Chest::animation_object()
{
    if (opened)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.left += animation_factor;

            if (pos.left >= animation_factor * animation_quantity)
            {
                pos.left -= animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
    else
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.left -= animation_factor;

            if (pos.left < 0)
            {
                pos.left += animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
}
