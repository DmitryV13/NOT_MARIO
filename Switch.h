#pragma once
#include "AnimObject.h"
#include "MovingObject.h"
class Switch : public AnimObject
{
private:
	bool on;
	Object* obj;
public:
	Switch ();
	Switch (std::string name, float position_x, float position_y, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time);
	Switch(std::string name, float position_x, float position_y, short int size_W, short int size_H
		, short int anim_factor, short int anim_quantity, float anim_time, Object *obj);

	void render_object(sf::RenderTarget& target);
	void useObject() override;
	void animation_object() override;
};

