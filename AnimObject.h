#pragma once
#include "Object.h"
using sf::Clock;

class AnimObject : public Object
{
protected:
	short int animation_factor;
	short int animation_quantity;
	float animation_time;
	Clock animationTimer;

public:
	AnimObject();
	AnimObject(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H
		,short int anim_factor, short int anim_quantity, float anim_time);
	void animation_object() override;

};

