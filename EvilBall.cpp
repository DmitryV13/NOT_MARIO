#include "stdafx.h"
#include "EvilBall.h"


EvilBall::EvilBall(TileMap& map) :Enemy(map)
{
	{
		EvilBall::init_texture();
		EvilBall::init_sprite();
	}
}


void EvilBall::init_texture()
{
	Texture tmp;
	if (!Enemy_T.loadFromFile("Textures/Enemies/eye.png"))
	{
		std::cout << "Error -> Enemy -> couldn't load enemy texture" << std::endl;
	}

}
void EvilBall::init_sprite()
{
	//Enemy_T = init_texture();
	Enemy_S.setTexture(Enemy_T);
	currentFrame = IntRect(0, 0, 60, 55.5);
	Enemy_S.setTextureRect(currentFrame);
}