#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	this->objectName = "default";
	this->position_x = 0;
	this->position_y = 0;
	this->interaction = 0;
	this->texture_size_W = 0;
	this->texture_size_H = 0;
}

Object::Object(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H)
{
	this->objectName = name;
	this->position_x = position_x;
	this->position_y = position_y;
	this->interaction = interaction;
	this->texture_size_W = size_W;
	this->texture_size_H = size_H;
	init_texture();
}

void Object::init_texture()
{
	if (!object_T.loadFromFile("Textures/Textures_map/" + objectName + ".png"))
	{
		std::cout << "Error -> Object -> couldn't load texture";
	}
	object_S.setTexture(object_T);
	object_S.setTextureRect(sf::IntRect(0, 0, texture_size_W, texture_size_H));
}

void Object::render_object(sf::RenderTarget& target)
{
	object_S.setPosition(position_x, position_y);
	target.draw(object_S);
}

void Object::animation_object(){}

bool Object::moveLeft() { return false; }

bool Object::moveRight() { return false; }

void Object::moveHorizont(){}

bool Object::moveUp() { return false; }

bool Object::moveDown() { return false; }

void Object::moveVertically(){}

void Object::open_chest(){}

void Object::close_chest(){}

void Object::useSwitch(){}
