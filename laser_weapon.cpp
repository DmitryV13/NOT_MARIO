#include "stdafx.h"
#include "laser_weapon.h"
#include "Enemy.h"

laser_weapon::laser_weapon(TileMap& map, int compar, float i, float j, bool direction)
{
	dir_x = direction;
	init_physics();
	sandbox = &map;
	init_variables(compar);

	init_texture();
	init_sprite();
	set_position(i, j);
}

const bool& laser_weapon::get_animation_switch()
{
	bool tmpSwitch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmpSwitch;
}

sf::Vector2f laser_weapon::get_position() const
{
	return laser_S.getPosition();
}

const FloatRect laser_weapon::get_global_bounds() const
{
	return laser_S.getGlobalBounds();
}

void laser_weapon::set_position(const float x, const float y)
{
	laser_S.setPosition(x, y);
}

void laser_weapon::render(sf::RenderTarget& target)
{
	target.draw(laser_S);
}

//void laser_weapon::update(sf::Vector2f pos_Enemy)
void laser_weapon::update()
{
	//FIXED:add a provision
	//set_position(pos_Enemy.x, pos_Enemy.y);
	update_animation();
}

void laser_weapon::update_animation()
{
	if (animation_state == LASER_ANIMATION_STATES::LASER_FIRST)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (dir_x)
			{
				current_frame.top += 60;
				if (current_frame.top >= 180.f)
				{
					current_frame.top = 0.f;
				}
				current_frame.width = 120;
			}
			else
			{
				current_frame.top += 60;
				if (current_frame.top >= 180.f)
				{
					current_frame.top = 0.f;
				}
				current_frame.left = 120;
				current_frame.width = -120;
			}
				laser_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == LASER_ANIMATION_STATES::LASER_NEXT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			current_frame.left = 120;
			current_frame.top += 60;
			if (current_frame.top >= 180.f)
			{
				current_frame.top = 0.f;
			}
			current_frame.width = 60;

			laser_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
}

void laser_weapon::reset_animation_timer()
{
	animation_timer.restart();
	animation_switch = true;
}


void laser_weapon::init_texture()
{
	if (!laser_T.loadFromFile("Textures/laser.png"))
	{
		std::cout << "Error -> laser -> couldn't load laser texture" << std::endl;
	}
}


void laser_weapon::init_sprite()
{
	if (LASER_ANIMATION_STATES::LASER_FIRST == animation_state && dir_x)
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(0, 0, 120, 60);
		laser_S.setTextureRect(current_frame);
	}
	else
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(120, 0, -120, 60);
		laser_S.setTextureRect(current_frame);
	}
	if(LASER_ANIMATION_STATES::LASER_NEXT == animation_state)
	{
		laser_S.setTexture(laser_T);
		current_frame = IntRect(120, 0, 60, 60);
		laser_S.setTextureRect(current_frame);
	}
}

void laser_weapon::init_variables(int compar)
{
	if (compar == first)
		animation_state = LASER_ANIMATION_STATES::LASER_FIRST;
	else animation_state = LASER_ANIMATION_STATES::LASER_NEXT;
}

void laser_weapon::init_animation()
{
	animation_switch = true;
	animation_timer.restart();
}

void laser_weapon::init_physics()
{
	first = 1;
	next = 2;
}
