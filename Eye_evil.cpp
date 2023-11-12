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
void Eye_evil::update_movement()
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
void Eye_evil::update_animation()
{

	if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 60;
				if (current_frame.left >= 360.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;

			}
			else
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
					current_frame.left = 0.f;
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
			if (looks_to_the_right)
			{
				if (search_for_enemies())
				{
					if (attention_counter == 3)current_frame.left = 0.f;
					attention_counter--;
					current_frame.left += 60;
				}
				if (current_frame.left >= 360.f)
				{
					current_frame.left = 180.f;
				}
				current_frame.top = 120;
				current_frame.width = 60;
			}
			else
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
			if (looks_to_the_left)
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
void Eye_evil::shot()
{

	if (looks_to_the_right)
	{
		laser_weapon* shot_las = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y, looks_to_the_right);
		laser.push_back(*shot_las);

		for (int j = (Enemy_S.getPosition().x / 60) + 2; j < TileFactory::m && j < j + 10 &&
			!sandbox->isBlock(Enemy_S.getPosition().y / 60, j); j++)
		{
			laser_weapon* shot_cur = new laser_weapon(*sandbox, 2, j * 60, Enemy_S.getPosition().y, looks_to_the_right);
			laser.push_back(*shot_cur);

		}
	}
	else
	{
		laser_weapon* shot_las = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x - 60, Enemy_S.getPosition().y, looks_to_the_right);
		laser.push_back(*shot_las);
		for (int j = (Enemy_S.getPosition().x / 60); j > 0 && j > j - 10 &&
			!sandbox->isBlock(Enemy_S.getPosition().y / 60, j); j--)
		{
			laser_weapon* shot_cur = new laser_weapon(*sandbox, 2, j * 60, Enemy_S.getPosition().y, looks_to_the_right);
			laser.push_back(*shot_cur);

		}
	}

}

void Eye_evil::attack()
{
	if (attention_counter == 1)shot();

	animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
	for (int i = 0; i < laser.size(); i++)
	{
		laser[i].update();
	}
	displacement.x = 0;
}

void Eye_evil::clear_shot()
{
	laser.clear();
}

bool Eye_evil::laser_existence()
{
	if (laser.empty())return false;
	else return true;
}

int Eye_evil::laser_length()
{
	return (int)laser.size();
}

void Eye_evil::draw_laser(int i, sf::RenderTarget& target)
{
	laser[i].render(target);
}
void Eye_evil::reset_attention()
{
	attention_counter = 3;
}
bool Eye_evil::search_for_enemies()
{
	int centerX = get_position().x / 60;
	int centerY = get_position().y / 60;

	if (looks_to_the_right)
	{
		for (int i = centerY - 1; i <= centerY + 1; i++)
		{
			for (int j = centerX + 1; j <= centerX + 5; j++)
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
	else
	{
		for (int i = centerY - 1; i <= centerY + 1; i++)
		{
			for (int j = centerX - 5; j <= centerX; j++)
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