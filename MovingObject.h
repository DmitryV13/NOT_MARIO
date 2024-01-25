#pragma once
#include "Object.h"
class MovingObject : public Object
{
private:
	float move_left;
	float move_right;
	float move_up;
	float move_down;
	float speed;
	bool flagMoveH;
	bool flagMoveV;
	bool DirectionLeft;
	bool DirectionRight;
	bool DirectionUp;
	bool DirectionDown;

public:
	MovingObject();
	MovingObject(std::string name, float position_x, float position_y, short int size_W, short int size_H);
	MovingObject(std::string name, float position_x, float position_y, short int size_W, short int size_H
		, float move_l, float move_r, float move_u, float move_d, float speed);
	bool moveLeft() override;
	bool moveRight() override;
	void moveHorizont() override;
	bool moveUp() override;
	bool moveDown() override;
	void moveVertically() override;
	std::pair<float, float> getVelocity() override;
};

