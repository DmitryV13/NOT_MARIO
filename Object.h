#pragma once
#include "OBJECT_TYPE.h"

class Object
{
protected:
	sf::Texture object_T;
	sf::Sprite	object_S;
	std::string objectName;

	short int texture_size_W;
	short int texture_size_H;

	float position_x;
	float position_y;

	short object_type;

	void init_texture();

public:
	Object();
	Object(std::string name, float position_x, float position_y, short int size_W, short int size_H);
	sf::FloatRect getGlobalBounds();
	void render_object(sf::RenderTarget& target);
	virtual std::pair<float, float> getVelocity();
	virtual void animation_object();
	virtual void useObject();
	virtual bool moveLeft();
	virtual bool moveRight();
	virtual void moveHorizont();
	virtual bool moveUp();
	virtual bool moveDown();
	virtual void moveVertically();
	short getOType();
};

