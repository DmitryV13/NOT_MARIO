#include "stdafx.h"
#include "map/Switch.h"

Switch::Switch() : AnimObject()
{
    object_type = OBJECT_TYPE::SWITCH;
	this->on = false;
	this->obj = nullptr;
}

Switch::Switch(std::string name, float position_x, float position_y, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time)
	: AnimObject (name, position_x, position_y, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
    object_type = OBJECT_TYPE::SWITCH;
	this->on = false;
	this->obj = nullptr;
}

Switch::Switch(std::string name, float position_x, float position_y, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time, Object* obj)
	: AnimObject(name, position_x, position_y, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
    object_type = OBJECT_TYPE::SWITCH;
	this->on = false;
	this->obj = obj;
}

void Switch::render_object(sf::RenderTarget& target)
{
    object_S.setPosition(sf::Vector2f(position_x, position_y));
    target.draw(object_S);
    if (obj) {
        obj->render_object(target);
    }
}

void Switch::useObject()
{
	if (on == false) {
		on = true;
        return;
	}
	else on = false;
    //std::cout << "call" << std::endl;
}

void Switch::animation_object()
{
    //std::cout << "jdcbfhvbhfevbc";
    if (on == true )
    {   
        if (obj != nullptr) {
            obj->moveLeft();
            obj->moveUp();
            //obj->animation_object();
        }
       
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.position.x += animation_factor;

            if (pos.position.x >= animation_factor * animation_quantity)
            {
                pos.position.x -= animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
    else
    {   
        if (obj != nullptr) {
            obj->moveRight();
            obj->moveDown();
            //obj->animation_object();
        }
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.position.x -= animation_factor;

            if (pos.position.x < 0)
            {
                pos.position.x += animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
}
