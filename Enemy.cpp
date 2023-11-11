﻿#include "stdafx.h"
#include "Enemy.h"

#include "laser_weapon.h"
#include "TileMap.h"


sf::Vector2f Enemy::generate_random_start_position(int mapWidth, int mapHeight)
{
	//  randomized distribution
	int maxAttempts = 100000;

	for (int i = 0; i < maxAttempts; i++)
	{
		int x = 60 + rand() % (mapWidth - 60 * 2 + 1);
		int y = 60 + rand() % (mapHeight - 60 * 2 + 1);

		int centerX = (x + 60) / 60;
		int centerY = (y + 60) / 60;

		bool collisionDetected = false;
		if (sandbox->isBlock(centerY, centerX))
		{
			collisionDetected = true;
		}
		else
		{
			for (int dx = -2; dx <= 2; dx++)
			{
				for (int dy = -3; dy <= 3; dy++)
				{
					int blockX = (x + dx) / 60;
					int blockY = (y + dy) / 60;
					if (sandbox->isBlock(blockY, blockX))
					{
						collisionDetected = true;
						break;
					}
				}
				if (collisionDetected)
				{
					break;
				}
			}
		}
		if (!collisionDetected)
		{
			return sf::Vector2f(x, y);
		}
	}
	return sf::Vector2f(0, 0);
}

void Enemy::init_variables()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_IDLE;
}

Enemy::Enemy(TileMap& map)
{
	sandbox = &map;
	init_variables();
	init_animation();
	init_physics();
	/*start_position = generate_random_start_position(sandbox->getMapWidth(), sandbox->getMapHeight());
	set_position(start_position.x, start_position.y);*/

	set_position(60,60);
}

sf::Vector2f Enemy::get_position() const
{
	return Enemy_S.getPosition();
}

const FloatRect Enemy::get_global_bounds() const
{
	return Enemy_S.getGlobalBounds();
}

void Enemy::reset_attention()
{
	attention_counter = 3;
}

void Enemy::set_position(const float x, const float y)
{
	Enemy_S.setPosition(x, y);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(Enemy_S);
	
}

void Enemy::update()
{
	update_movement();
	update_animation();
	update_physics();
}

void Enemy::reset_animation_timer()
{
	animation_timer.restart();
	animation_switch = true;
}

bool Enemy::search_for_enemies()
{
	int centerX = get_position().x / 60;
	int centerY = get_position().y / 60;

	if(looks_to_the_right)
	{
		for (int i = centerY-1; i <= centerY + 1; i++)
		{
			for (int j = centerX+1; j <= centerX + 5; j++)
			{
				if (i >= 0 && i < 40 && j >= 0 && j < 200)
				{
					if (sandbox->isOccupied(i, j))
					{
						return true;
					}
				}
			}
		}
	}else
	{
		for (int i = centerY - 1; i <= centerY + 1 ; i++)
		{
			for (int j = centerX - 5; j <= centerX ; j++)
			{
				if (i >= 0 && i < 40 && j >= 0 && j < 200)
				{
					if (sandbox->isOccupied(i, j))
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Enemy::laser_existence()
{
	if (laser.empty())return false;
	else return true;
}

int Enemy::laser_length()
{
	return (int)laser.size();  
}

void Enemy::draw_laser(int i, sf::RenderTarget& target)
{
	laser[i].render(target);
}


void Enemy::update_animation()
{

	if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if(looks_to_the_right)
			{
				current_frame.left += 60;
			if (current_frame.left >= 360.f)
			{
				current_frame.left = 0.f;
			}
			current_frame.width = 60;
			current_frame.top = 0;
			
			}else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
			
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_IDLE)
	{
		
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			animation_counter_think--;
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 360.f)
				{
					current_frame.left =0.f;
				}
				current_frame.width = 60;
				current_frame.top = 180;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420.f)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 180;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if(looks_to_the_right)
			{
				if(search_for_enemies())
			{
				if(attention_counter == 3)current_frame.left = 0.f;
				attention_counter--;
				current_frame.left += 60;
			}
			if (current_frame.left >= 360.f)
			{
				current_frame.left = 180.f;
			}
			current_frame.top = 120;
			current_frame.width = 60;
			}else
			{
				if (search_for_enemies())
				{
					if (attention_counter == 3)current_frame.left = 60.f;
					attention_counter--;
					current_frame.left += 60;
				}
				if (current_frame.left >= 420.f)
				{
					current_frame.left = 240.f;
				}
				current_frame.top = 120;
				current_frame.width = -60;
			}
			

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_JUMPING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if(looks_to_the_left)
			{
				current_frame.left += 60;
			if (current_frame.left >= 420.f)
			{
				current_frame.left = 60.f;
			}
			current_frame.width = -60;
			current_frame.top = 60;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 360.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 60;
			}
			

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING_DOWN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 360.f)
				{
					current_frame.left = 180.f;
				}
				current_frame.width = 60;
				current_frame.top = 60;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420.f)
				{
					current_frame.left = 240.f;
				}
				current_frame.width = -60;
				current_frame.top = 60;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}


	else
	{
		animation_timer.restart();
	}
}

void Enemy::init_animation()
{
	animation_switch = true;
	animation_timer.restart();
}

const bool& Enemy::get_animation_switch()
{
	bool tmpSwitch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmpSwitch;
}

void Enemy::init_physics()
{
	displacement_max = 1.f;
	attention_counter = 3;
	displacement_min = 0.3f;
	acceleration = 0.4f;
	deceleration = 0.77f;
	gravity = 2.5f;
	velocity_max_y = 15.f;
	on_ground = false;
	jump_velocity = 7.f;
	moving = 1.f;
	step_left = 0;
	step_right = 0;
	jump_tile = false;
	displacement.x = 0.f;
	displacement.y = 0.f;

	looks_to_the_left = false;
	looks_to_the_right = true;
	animation_counter_think = 0;
}

void Enemy::walk(const float dir_x)
{
	if (dir_x > 0) {
		looks_to_the_right = true;
		looks_to_the_left = false;
	}
	else
	{
		looks_to_the_right = false;
		looks_to_the_left = true;
	}
	//movement on the ground
	if (on_ground)
	{
		displacement.x += dir_x * acceleration;
	}

	// limits
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}

	if (animation_counter_think > 2) {
		displacement.x = 0;
		animation_state = Enemy_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = Enemy_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = Enemy_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = Enemy_ANIMATION_STATES::ENEMY_MOVING;

	//logic when exposing a player
	if (search_for_enemies())
	{
		if (attention_counter == 1)shot();
		
		animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
		for (int i = 0; i < laser.size(); i++)
		{
			laser[i].update();
		}
		displacement.x = 0;
	}
	else {
		reset_attention();
		clear_shot();
	}
}

void Enemy::update_movement()
{
	//decision explorer
	if (on_ground)
	{
		if (update_collision_x())
		{
			if (!update_collision_x_jump())
			{
				jump(-65);
				on_ground = false;
				jump_tile = true;
			}
			else moving *= -1.f;
		}
		if (Enemy_S.getPosition().x <= 0)
		{
			displacement.x = 0;
		}
		if (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width > sandbox->getMapWidth())
		{
			displacement.x = 0;
		}
	}
	//step limits
	if (step_right == max_step)
	{
		moving *= -1.f;
		step_right = 0;
		animation_counter_think = 12;
		
	}
	if (step_left == max_step)
	{
		animation_counter_think = 12;
		moving *= -1.f;
		step_left = 0;
		
	}
	

	//turning when approaching the map boundaries
	if (displacement.x + Enemy_S.getPosition().x <= 0.f ||
		Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width + displacement.y > sandbox->getMapWidth())
	{
		moving *= -1.f;
	}

	//in case of random map generation
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<int> decision_to_think(0, 10000);
	// int rand = decision_to_think(gen);
	// if(rand <25)
	// {
	// 	animation_counter_think = 12;
	// 	moving *= -1.f;
	// }
	walk(moving);
}

//ground contact
void Enemy::reset_jump_access()
{
	displacement.y = 0.f;
	on_ground = true;
	jump_tile = false;
}

void Enemy::shot()
{
	if(looks_to_the_right)
	{
		laser_weapon *shot_las = new laser_weapon(*sandbox, 1,Enemy_S.getPosition().x,Enemy_S.getPosition().y,looks_to_the_right);
	laser.push_back(*shot_las);
	for (int j = (Enemy_S.getPosition().x / 60) + 2; j < TileFactory::m && j < j + 10 && 
		!sandbox->isBlock(Enemy_S.getPosition().y / 60,j); j++)
		{
		 laser_weapon *shot_cur = new laser_weapon(*sandbox, 2,j*60, Enemy_S.getPosition().y,looks_to_the_right);
		 laser.push_back(*shot_cur);

		}
	}
	else
	{
		laser_weapon* shot_las = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x-60, Enemy_S.getPosition().y,looks_to_the_right);
		laser.push_back(*shot_las);
		for (int j = (Enemy_S.getPosition().x / 60) ; j > 0 && j > j - 10 &&
			!sandbox->isBlock(Enemy_S.getPosition().y / 60, j); j--)
		{
			laser_weapon* shot_cur = new laser_weapon(*sandbox, 2, j * 60, Enemy_S.getPosition().y, looks_to_the_right);
			laser.push_back(*shot_cur);

		}
	}
	
}

void Enemy::clear_shot()
{
	laser.clear();
}

//jump handling
void Enemy::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = 5.5f;
	}
}


void Enemy::update_physics()
{
	// gravity
	displacement.y += 1.f * gravity;
	if (std::abs(displacement.y) > velocity_max_y)
	{
		displacement.y = velocity_max_y * ((displacement.y > 0.f) ? 1.f : -1.f);
	}
	//jumping
	if (jump_tile)
	{
		displacement.y -= jump_velocity;
		//jumping onto a block
		displacement.x += moving * acceleration;
		//jump deceleratin
		jump_velocity *= 0.96;
	}
	// deceleration
	displacement *= deceleration;
	// limits
	if (std::abs(displacement.x) < displacement_min || update_collision_x())
	{
		displacement.x = 0.f;
	}
	if (std::abs(displacement.y) < displacement_min || update_collision_y())
	{
		displacement.y = 0.f;
	}
	//step counter
	if (displacement.x > 0)
		step_right++;
	if (displacement.x < 0)
		step_left++;

	Enemy_S.move(displacement);
}

// collision x
bool Enemy::update_collision_x()
{
	bool wasCollision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = Enemy_S.getPosition().y / 60; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 60; i
	     ++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 60; j < (Enemy_S.getPosition().x + displacement.x +
			     Enemy_S.getGlobalBounds().width) / 60; j++)
		{
			if (sandbox->isBlock(i, j))
			{
				wasCollision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	Enemy_S.setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}

//resolving jump collision
bool Enemy::update_collision_x_jump()
{
	bool wasCollision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = Enemy_S.getPosition().y / 60; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 60; i
	     ++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 60; j < (Enemy_S.getPosition().x + displacement.x +
			     Enemy_S.getGlobalBounds().width) / 60; j++)
		{
			if (sandbox->isBlock(i - 1, j))
			{
				wasCollision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	Enemy_S.setPosition(newPosition.x, newPosition.y);
	return wasCollision;
}

//collision y
bool Enemy::update_collision_y()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(Enemy_S.getPosition().x, Enemy_S.getPosition().y);

	for (int i = (Enemy_S.getPosition().y + displacement.y) / 60; i < (Enemy_S.getPosition().y + displacement.y +
		     Enemy_S.getGlobalBounds().height) / 60; i++)
	{
		for (int j = Enemy_S.getPosition().x / 60; j < (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width) / 60;
		     j++)
		{
			if (sandbox->isBlock(i, j))
			{
				wasCollision = true;
				if (displacement.y > 0)
				{
					reset_jump_access();
					newPosition.y = (i * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().height);
				}
				if (displacement.y < 0)
				{
					reset_jump_access();
					newPosition.y = i * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}

	set_position(newPosition.x, newPosition.y);
	return wasCollision;
}
