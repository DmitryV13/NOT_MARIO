#pragma once
#include "TileAnim.h"
class TileBox : public TileAnim
{
private:
	bool open = false;
	//поля с обьектсами типа оружия, мб бустеров и так далее.

public:

	TileBox();
	TileBox(std::string Name, short int inter, short int texture_size_w, short int texture_size_h, char ass, short int anim_f, short int anim_q, float time);
	void open_box();
	void close_box();
	void box_animation();
};


