#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	object_type = OBJECT_TYPE::OBJECT;
	this->objectName = "default";
	this->position_x = 0;
	this->position_y = 0;
	this->texture_size_W = 0;
	this->texture_size_H = 0;
}

Object::Object(std::string name, float position_x, float position_y, short int size_W, short int size_H)
{
	object_type = OBJECT_TYPE::OBJECT;
	this->objectName = name;
	this->position_x = position_x;
	this->position_y = position_y;
	this->texture_size_W = size_W;
	this->texture_size_H = size_H;
	init_texture();
}

sf::FloatRect Object::getGlobalBounds()
{
	return object_S.getGlobalBounds();
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

std::pair<float, float> Object::getVelocity()
{
	return std::pair<float, float>(0,0);
}

void Object::animation_object(){}

void Object::useObject(){}

bool Object::moveLeft() { return false; }

bool Object::moveRight() { return false; }

void Object::moveHorizont(){}

bool Object::moveUp() { return false; }

bool Object::moveDown() { return false; }

void Object::moveVertically(){}

short Object::getOType(){
	return object_type;
}
