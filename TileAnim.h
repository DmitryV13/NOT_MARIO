#pragma once
#include "Tile.h"

class TileAnim : public Tile
{
protected:

	short int animation_factor;
	short int animation_quantity;
	float animation_time;
	Clock animationTimer;

public:

	TileAnim();
	TileAnim(std::string Name, short int inter, short int texture_size_w, short int texture_size_h, char ass, short int anim_f, short int anim_q, float time);
	~TileAnim() override;
	void tile_animation();

};


