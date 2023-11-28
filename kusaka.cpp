#include "stdafx.h"
#include "kusaka.h"

kusaka::kusaka(TileMap& map, Player& pl) :Enemy(map, pl)
{
	{
		kusaka::init_texture();
		kusaka::init_sprite();
	}
}


void kusaka::init_texture()
{
	if (!kusaka_t_.loadFromFile("Textures/kusaka.png"))
	{
		std::cout << "Error -> Enemy_kusaka -> couldn't load enemy_kusaka texture" << std::endl;
	}
}

void kusaka::init_sprite()
{
	//Enemy_T = init_texture();
	Enemy_S.setTexture(kusaka_t_);
	current_frame = IntRect(0, 0, 90, 55);
	Enemy_S.setTextureRect(current_frame);
}

void kusaka::update_movement()
{
	//decision explorer
	if (on_ground)
	{
		if (update_collision_x())
		{
			if (!update_collision_x_jump() )
			{
				jump(1);
				on_ground = false;
				jump_tile = true;
			}
			else moving *= -1.f;
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

void kusaka::update_animation()
{
	if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 90;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
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
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 90;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
				current_frame.top = 0;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.05f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 90;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
				current_frame.top = 0;
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
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = 90;
				current_frame.top = 70;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
				current_frame.top = 70;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 90;
				current_frame.top = 70;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
				current_frame.top = 70;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			animation_counter_think--;
			if (looks_to_the_right)
			{
				current_frame.left += 90;
				if (current_frame.left >= 810.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 90;
				current_frame.top = 140;
			}
			else
			{
				current_frame.left += 90;
				if (current_frame.left >= 900.f)
				{
					current_frame.left = 90.f;
				}
				current_frame.width = -90;
				current_frame.top = 140;
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

void kusaka::shot()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_SHOT;
}

void kusaka::attack()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
	if(player_contact())
	{
		if (count_jump == 0) {
			//jump(1.f);
			jump_towards_player();
			count_jump++;
		}
	}
	if (sting())
	{
		
		shot();
		displacement.x = 0;
		displacement_max = 1.f;
		FloatRect en = get_global_bounds();
		FloatRect pl = sandbox->get_player_glob_bound();
		if (pl.left < en.left)
		{
			if (looks_to_the_right)
			{
				looks_to_the_right = false;
				looks_to_the_left = true;
			}
		}
		else if (pl.left > en.left)
		{
			if (looks_to_the_left)
			{
				looks_to_the_right = true;
				looks_to_the_left = false;
			}
		}
	}
	else
	{
		if (jump_tile || !on_ground)displacement_max = 1.f;
		else displacement_max = 5.f;
		if (player_l_r[0] && displacement.x > 0)
		{
			displacement.x = 0;
			moving = -1.f;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r[0] && displacement.x < 0)
		{
			displacement.x = 0;
			//moving= 1.f;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r[1] && displacement.x > 0)
		{
			displacement.x = 0;
			looks_to_the_right = true;
			looks_to_the_left = false;
			//moving = 1.f;
		}
		else
		{
			displacement.x = 0;
			moving = 1.f;
			looks_to_the_right = true;
			looks_to_the_left = false;
		}
		displacement.x += 10 * moving * acceleration;
	}
	if(!player_contact())
	{
		reset_attention();
	}
	// displacement.x = 0;
}

void kusaka::clear_shot()
{
}

bool kusaka::search_for_enemies()
{
	// int centerX = get_position().x / 60;
	// int centerY = get_position().y / 60;
	//
	//
	// for (int i = centerY - 3;  i <= centerY + 3; i++)
	// {
	// 	for (int j = centerX - 6; j <= centerX + 6; j++)
	// 	{
	// 		if (i >= 0 && i < 40 && j >= 0 && j < TileFactory::m && i < TileFactory::n && i > 0)
	// 		{
	// 			if (sandbox->isOccupied(i, j))
	// 			{
	// 				return true;
	// 			}
	// 		}
	// 	}
	// }
	//
	// return false;
	int centerX = get_position().x / 60;
	int centerY = get_position().y / 60;


	for (int i = centerY - 1; i <= centerY + 1; i++)
	{
		for (int j = centerX + 1; j <= centerX + 10; j++)
		{
			if (i >= 0 && i < 40 && j >= 0 && j < 200)
			{
				if (sandbox->isOccupied(i, j))
				{
					player_l_r[1] = true;
					player_l_r[0] = false;
					return true;
				}
			}
		}
	}


	for (int i = centerY - 1; i <= centerY + 1; i++)
	{
		for (int j = centerX - 10; j <= centerX; j++)
		{
			if (i >= 0 && i < 40 && j >= 0 && j < 200)
			{
				if (sandbox->isOccupied(i, j))
				{
					player_l_r[0] = true;
					player_l_r[1] = false;
					return true;
				}
			}
		}
	}

	player_l_r[0] = false;
	player_l_r[1] = false;
	return false;
}

void kusaka::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump = 0;
}



