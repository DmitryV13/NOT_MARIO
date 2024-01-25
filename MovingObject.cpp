#include "stdafx.h"
#include "MovingObject.h"

MovingObject::MovingObject() : Object()
{
	object_type = OBJECT_TYPE::MOVING_OBJECT;
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingObject::MovingObject(std::string name, float position_x, float position_y, short int size_W, short int size_H)
	: Object(name, position_x, position_y, size_W, size_H)
{
	object_type = OBJECT_TYPE::MOVING_OBJECT;
	this->move_left = position_x - 0;
	this->move_right = position_x + 0;
	this->move_up = position_y - 0;
	this->move_down = position_y + 0;
	this->speed = 0;
	this->flagMoveH = false;
	this->flagMoveV = false;
}

MovingObject::MovingObject(std::string name, float position_x, float position_y, short int size_W, short int size_H
	, float move_l, float move_r, float move_u, float move_d, float speed) 
	: Object(name, position_x, position_y, size_W, size_H)
{
	object_type = OBJECT_TYPE::MOVING_OBJECT;
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
		DirectionLeft = true;
		return true;
	}
	DirectionLeft = false;
	return false;
}

bool MovingObject::moveRight()
{
	if (position_x < move_right) {
		position_x = position_x + speed;
		DirectionRight = true;
		return true;
	}
	DirectionRight = false;
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
		DirectionUp = true;
		return true;
	}
	DirectionUp = false;
	return false;
}

bool MovingObject::moveDown()
{
	if (position_y < move_down) {
		position_y = position_y + speed;
		DirectionDown = true;
		return true;
	}
	DirectionDown = false;
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

std::pair<float, float> MovingObject::getVelocity()
{
	if (DirectionLeft) return std::pair<float, float>(-speed, 0);
	else if (DirectionRight) return std::pair<float, float>(speed, 0);
	else if (DirectionUp) return std::pair<float, float>(0, -speed);
	else if (DirectionDown) return std::pair<float, float>(0, speed);
	else return std::pair<float, float>(0, 0);
}
