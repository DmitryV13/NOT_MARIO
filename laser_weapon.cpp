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
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (dir_x)
			{
				current_frame.left = 0;
				current_frame.top += 60;
				if (current_frame.top >= 180.f)
				{
					current_frame.top = 0.f;
				}
				current_frame.width = 60;
			}
			else
			{
				current_frame.left = 0;

				current_frame.top += 60;
				if (current_frame.top >= 180.f)
				{
					current_frame.top = 0.f;
				}
				current_frame.left = 60;
				current_frame.width = -60;
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
	if (LASER_ANIMATION_STATES::LASER_NEXT == animation_state)
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

bool laser_weapon::update_collision_x(float x)
{
	bool wasCollision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	int i = (laser_S.getPosition().y + laser_S.getGlobalBounds().height) / 60;
	/*for (int i = laser_S.getPosition().y / 60; i < (laser_S.getPosition().y + laser_S.getGlobalBounds().height) / 60; i
	     ++)
	{*/
	int j = (laser_S.getPosition().x + x +
		laser_S.getGlobalBounds().width) / 60;
	/*for (int j = (laser_S.getPosition().x + x) / 60; j < (laser_S.getPosition().x + x +
		     laser_S.getGlobalBounds().width) / 60; j++)
	{*/
	if (sandbox->isBlock(i, j) || j <= 0 || j >= 200)
	{
		wasCollision = true;
		if (x >= 0)
		{
			newPosition.x = j * sandbox->getSizeTexture() - laser_S.getGlobalBounds().width;
		}
		if (x < 0)
		{
			newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
		}
	}
	//}
	//}
	//laser_S.setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}

sf::Vector2f laser_weapon::calculateEndPosition(float x)
{
	sf::Vector2f newPosition(get_position().x, get_position().y);
	int j;
	int i = (laser_S.getPosition().y) / 60;
	if (dir_x)j = (laser_S.getPosition().x + x + laser_S.getGlobalBounds().width) / 60;
	else j = (laser_S.getPosition().x + x) / 60;
	
	int g = 0;
	while (!sandbox->isBlock(i, j) && j > 0 && j < 200 && g < 60)
	{
		g++;
		newPosition.x += x/2;
		i = (newPosition.y) / 60;
		if (dir_x)j = (newPosition.x + laser_S.getGlobalBounds().width) / 60;
		else j = (newPosition.x) / 60;
	}
	if (dir_x) {
		newPosition.x = (j - 2) * 60;
	}
	else {
		newPosition.x = (j + 1) * 60;
	}
	return newPosition;
}
void laser_weapon::render_FL(sf::RenderTarget& target)
{
	float x = dir_x ? 60.0f : -60.0f;

	sf::Vector2f startPosition = get_position();
	sf::Vector2f endPosition = calculateEndPosition(x);
	if (startPosition == endPosition)return;

	if (dir_x)
	{
		endPosition.x += 30;
		update_animation();
		laser_S.setPosition(startPosition);
		target.draw(laser_S);

		current_frame.left = 128;
		current_frame.width = -100;
		laser_S.setTextureRect(current_frame);
		if(endPosition.x>=startPosition.x)
		{
			laser_S.setPosition(endPosition);
			target.draw(laser_S);
		}
		
		
		laser_S.setPosition(startPosition);
		current_frame.width = 120;
		current_frame.left = 0;
		laser_S.setTextureRect(current_frame);

	}

	else
	{
		endPosition.x -= 30;
		laser_S.setPosition(startPosition);
		target.draw(laser_S);
		
		current_frame.width = 90;
		current_frame.left = 10;
		laser_S.setTextureRect(current_frame);
		if (endPosition.x+60 < startPosition.x)
		{
			laser_S.setPosition(endPosition);
			target.draw(laser_S);
		}
		
		laser_S.setPosition(startPosition);
		current_frame.left = 60;
		current_frame.width = -60;
		laser_S.setTextureRect(current_frame);
	}

}
void laser_weapon::render(sf::RenderTarget& target)
{
	float x = dir_x ? 60.0f : -60.0f;
	
	sf::Vector2f startPosition = get_position();
	sf::Vector2f currentPosition = startPosition;
	sf::Vector2f endPosition = calculateEndPosition(x);
	
	if (startPosition == endPosition)return;
	if (dir_x)
	{
		
		endPosition.x += 30;
		
		while (currentPosition.x <= endPosition.x)
		{
			
			laser_S.setPosition(currentPosition);
			target.draw(laser_S);
			
			currentPosition.x += 60.0f;
		}
		laser_S.setPosition(startPosition);
	}

	else
	{

		while (currentPosition.x >= endPosition.x)
		{
			laser_S.setPosition(currentPosition);
			target.draw(laser_S);
			

			currentPosition.x -= 60.0f;
		}
		laser_S.setPosition(startPosition);
	}
}
