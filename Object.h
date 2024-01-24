#pragma once

enum OBJECT_TYPE {
	OBJECT,
	ANIM_OBJECT,
	MOVING_OBJECT,
	MOVING_ANIM_OBJECT,
	SWITCH,
	CHEST,
};

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

	short int interaction;

	void init_texture();

public:
	Object();
	Object(std::string name, float position_x, float position_y, OBJECT_TYPE interaction, short int size_W, short int size_H);
	
	void render_object(sf::RenderTarget& target);
	virtual void animation_object();
	virtual void open_chest();
	virtual void close_chest();
	virtual void useSwitch();
	virtual bool moveLeft();
	virtual bool moveRight();
	virtual void moveHorizont();
	virtual bool moveUp();
	virtual bool moveDown();
	virtual void moveVertically();

};

