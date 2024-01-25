#pragma once
#include "AnimObject.h"
class Chest : public AnimObject
{
private:
	bool opened;
	// поля с данными
	
public:
	Chest();
	Chest(std::string name, float position_x, float position_y, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time);
	void useObject() override;
	void animation_object() override;
};

