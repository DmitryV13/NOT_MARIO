#include "stdafx.h"
#include "Wolf_Boss.h"


Wolf_Boss::Wolf_Boss(TileMap& map) : Enemy(map)
{
	{
		Wolf_Boss::init_texture();
		Wolf_Boss::init_sprite();
		moving_prev = 1.f;
	}
}

void Wolf_Boss::init_texture()
{
	if (!Wolf_Boss_t_.loadFromFile("Textures/boss.png"))
	{
		std::cout << "Error -> Enemy_Wolf_Boss -> couldn't load enemy_Wolf_Boss texture" << std::endl;
	}
}

void Wolf_Boss::init_sprite()
{
	Enemy_S.setTexture(Wolf_Boss_t_);
	current_frame = IntRect(0, 0, 200, 180);
	Enemy_S.setTextureRect(current_frame);
}

void Wolf_Boss::update_movement()
{
	moving_prev = moving;
	//decision explorer
	if (on_ground)
	{
		if (update_collision_x())
		{
			moving *= -1.f;
			
		}
	}
	//step limits
	if (step_right == max_step)
	{
		moving_prev = moving *= -1.f;
		step_right = 0;
		animation_counter_think = 12;
	}
	if (step_left == max_step)
	{
		animation_counter_think = 12;
		moving_prev = moving *= -1.f;
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

void Wolf_Boss::update_animation()
{
	if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 200;
				if (current_frame.left >= 200.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 240;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 200;
				if (current_frame.left >= 400.f)
				{
					current_frame.left = 200.f;
				}
				current_frame.width = -200;
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
			if (looks_to_the_right)
			{
				current_frame.left += 200;
				if (current_frame.left >= 200.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 200;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 200;
				if (current_frame.left >= 200.f)
				{
					current_frame.left = 200.f;
				}
				current_frame.width = -200;
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
				current_frame.left += 200;
				if (current_frame.left >= 200.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 200;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 200;
				if (current_frame.left >= 200.f)
				{
					current_frame.left = 200.f;
				}
				current_frame.width = -200;
				current_frame.top = 0;
			}
			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}

	/*else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_MOVING_DOWN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 70;
				if (current_frame.left >= 140.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 70;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -70;
				current_frame.top = 0;
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
				current_frame.left += 70;
				if (current_frame.left >= 140.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 70;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -70;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == Enemy_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 70;
				if (current_frame.left >= 140.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 70;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -70;
				current_frame.top = 0;
			}
			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}*/


	else
	{
		animation_timer.restart();
	}
}

void Wolf_Boss::shot()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_SHOT;

}

void Wolf_Boss::attack()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;

	

	if (player_contact()) {

		displacement_max = 10.f;
		if (sting())shot();//attack description

	}else
	{
		displacement_max = 5.f;
		
		if(moving_prev != moving)
		{
			count_anger++;
			
			displacement.x = 0;
			moving = 0.f;
			animation_state = Enemy_ANIMATION_STATES::ENEMY_IDLE;
			if(looks_to_the_right)
			{
				looks_to_the_left = true;
				looks_to_the_right = false;
			}
			else
			{
				looks_to_the_left = false;
				looks_to_the_right = true;
			}

		}else if(count_anger > 10)
		{
			moving = moving_prev;
		}
		
		//if (player_l_r[0] && displacement.x > 0)
		//{
		//	displacement.x = 0;
		//	moving = -1.f;
		//	looks_to_the_right = false;
		//	looks_to_the_left = true;
		//}
		//else if (player_l_r[0] && displacement.x < 0)
		//{
		//	displacement.x = 0;
		//	//moving= 1.f;
		//	looks_to_the_right = false;
		//	looks_to_the_left = true;
		//}
		//else if (player_l_r[1] && displacement.x > 0)
		//{
		//	displacement.x = 0;
		//	looks_to_the_right = true;
		//	looks_to_the_left = false;
		//	//moving = 1.f;
		//}
		//else
		//{
		//	displacement.x = 0;
		//	moving = 1.f;
		//	looks_to_the_right = true;
		//	looks_to_the_left = false;
		//}
		
	}
	
		displacement.x += 10 * moving * acceleration;





	/*if (sting())
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
	}*/

	
	// displacement.x = 0;
}
void Wolf_Boss::clear_shot()
{
}

bool Wolf_Boss::search_for_enemies()
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

	
	for (int i = centerY - 10; i <= centerY + 10; i++)
	{
		for (int j = centerX +1; j <= centerX + 20; j++)
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


	for (int i = centerY - 10; i <= centerY + 10; i++)
	{
		for (int j = centerX - 20; j <= centerX; j++)
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

void Wolf_Boss::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	}
