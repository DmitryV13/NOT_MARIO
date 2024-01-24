#include "stdafx.h"
#include "Switch.h"

Switch::Switch() : AnimObject()
{
	this->on = false;
	this->obj = nullptr;
}

Switch::Switch(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time)
	: AnimObject (name, position_x, position_y, interaction,  size_W, size_H, anim_factor, anim_quantity, anim_time)
{
	this->on = false;
	this->obj = nullptr;
}

Switch::Switch(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time, Object* obj)
	: AnimObject(name, position_x, position_y, interaction, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
	this->on = false;
	this->obj = obj;
}

void Switch::useSwitch()
{
	if (!on) {
		on = true;
	}
	else on = false;
}

void Switch::animation_object()
{
    if (on)
    {   
        if (obj) {
            obj->moveLeft();
            obj->moveUp();
        }
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
        if (obj) {
            obj->moveRight();
            obj->moveDown();
        }
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
