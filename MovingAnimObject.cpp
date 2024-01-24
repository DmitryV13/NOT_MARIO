#include "stdafx.h"
#include "MovingAnimObject.h"

MovingAnimObject::MovingAnimObject() : AnimObject()
{
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingAnimObject::MovingAnimObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time)
		: AnimObject(name, position_x, position_y, interaction, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingAnimObject::MovingAnimObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
	, short int anim_factor, short int anim_quantity, float anim_time, float move_l, float move_r, float move_u, float move_d, float speed)
		: AnimObject(name, position_x, position_y, interaction, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
	this->move_left = position_x - move_l;
	this->move_right = position_x + move_r;
	this->move_up = position_y - move_u;
	this->move_down = position_y + move_d;
	this->speed = speed;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

bool MovingAnimObject::moveLeft()
{
	if (position_x > move_left) {
		position_x = position_x - speed;
		return true;
	}
	return false;
}

bool MovingAnimObject::moveRight()
{
	if (position_x < move_right) {
		position_x = position_x + speed;
		return true;
	}
	return false;
}

void MovingAnimObject::moveHorizont()
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

bool MovingAnimObject::moveUp()
{
	if (position_y > move_up) {
		position_y = position_y - speed;
		return true;
	}
	return false;
}

bool MovingAnimObject::moveDown()
{
	if (position_y < move_down) {
		position_y = position_y + speed;
		return true;
	}
	return false;
}

void MovingAnimObject::moveVertically()
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
