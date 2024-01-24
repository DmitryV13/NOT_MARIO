#include "stdafx.h"
#include "MovingObject.h"

MovingObject::MovingObject() : Object()
{
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingObject::MovingObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H)
	: Object(name, position_x, position_y, interaction, size_W, size_H)
{
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingObject::MovingObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
	, float move_l, float move_r, float move_u, float move_d, float speed) 
	: Object(name, position_x, position_y, interaction, size_W, size_H)
{
	this->move_left = position_x - move_l;
	this->move_right = position_x + move_r;
	this->move_up = position_y - move_u;
	this->move_down = position_y + move_d;
	this->speed = speed;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

bool MovingObject::moveLeft()
{
	if (position_x > move_left) {
		position_x = position_x - speed;
		return true;
	}
	return false;
}

bool MovingObject::moveRight()
{
	if (position_x < move_right) {
		position_x = position_x + speed;
		return true;
	}
	return false;
}

void MovingObject::moveHorizont()
{
	if (!flagMoveH) {
		if (!moveLeft()) {
			flagMoveH = true;
			return;
		}
		return;
	}
	else {
		if (!moveRight()) {
			flagMoveH = false;
			return;
		}
		return;
	}
}

bool MovingObject::moveUp()
{
	if (position_y > move_up) {
		position_y = position_y - speed;
		return true;
	}
	return false;
}

bool MovingObject::moveDown()
{
	if (position_y < move_down) {
		position_y = position_y + speed;
		return true;
	}
	return false;
}

void MovingObject::moveVertically()
{
	if (!flagMoveV) {
		if (!moveUp()) {
			flagMoveV = true;
			return;
		}
		return;
	}
	else {
		if (!moveDown()) {
			flagMoveV = false;
			return;
		}
		return;
	}
}
