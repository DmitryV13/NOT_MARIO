#pragma once
#include "AnimObject.h"
class MovingAnimObject : public AnimObject
{
private:
	float move_left;
	float move_right;
	float move_up;
	float move_down;
	float speed;
	bool flagMoveH;
	bool flagMoveV;

public:
	MovingAnimObject();
	MovingAnimObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time);
	MovingAnimObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time, float move_l, float move_r, float move_u, float move_d, float speed);
	bool moveLeft() override;
	bool moveRight() override;
	void moveHorizont() override;
	bool moveUp() override;
	bool moveDown() override;
	void moveVertically() override;

};

