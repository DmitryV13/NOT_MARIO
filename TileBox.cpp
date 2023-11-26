#include "stdafx.h"
#include "TileBox.h"

TileBox::TileBox() : TileAnim() {}

TileBox::TileBox(std::string Name, short int inter, short int texture_size_w,short int texture_size_h, char ass, short int anim_f, short int anim_q, float time)
	: TileAnim(Name, inter, texture_size_w, texture_size_h, ass,  anim_f, anim_q, time) {}
