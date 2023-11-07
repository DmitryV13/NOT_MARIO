#include "stdafx.h"
#include "Eye_evil.h"


Eye_evil::Eye_evil(TileMap& map) :Enemy(map)
{
	{
		Eye_evil::init_texture();
		Eye_evil::init_sprite();
	}
}


void Eye_evil::init_texture()
{
	Texture tmp;
	if (!Enemy_T.loadFromFile("Textures/eye.png"))
	{
		std::cout << "Error -> Enemy -> couldn't load enemy texture" << std::endl;
	}

}
void Eye_evil::init_sprite()
{
	//Enemy_T = init_texture();
	Enemy_S.setTexture(Enemy_T);
	current_frame = IntRect(0, 0, 60, 55.5);
	Enemy_S.setTextureRect(current_frame);
}