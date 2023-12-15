#include "stdafx.h"
#include "kusaka.h"

kusaka::kusaka(TileMap& map, FloatRect* player_gl_b_, Vector2f* player_pos_, short* pl_hp_)
	:Enemy(map, player_gl_b_,player_pos_,pl_hp_)
{
	{
		kusaka::init_texture();
		kusaka::init_sprite();
		kusaka::setAt(10);
		kusaka::setHP(1000);
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

	current_area = IntRect(0, 0, 1280, 192);
	observation_area.setTextureRect(current_area);
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
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
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

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if(count_shot == 0)
			{
				current_frame.left = 0.f;
			}
			count_shot++;
			
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
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

	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
	//player_->changeHP(-attack_-(rand()%5));
	*pl_hp += -attack_ - (rand() % 5);
}


void kusaka::attack()
{
	if(animation_state != ENEMY_ANIMATION_STATES::ENEMY_SHOT)animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
	if (isPlayerInRadius(observation_area.getGlobalBounds(), *player_gl_b, 192))
	{
		if (count_jump == 0) {
			//jump(1.f);
			jump_towards_player();
			count_jump++;
		}
	}
	else reset_attention();
	if (sting())
	{
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;

		displacement.x = 0;
		displacement_max = 1.f;
		FloatRect en = get_global_bounds();
		FloatRect pl = *player_gl_b;
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

		if (blow_timer.getElapsedTime().asSeconds() >= 0.9) {
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			shot();
			clear_shot();
			displacement.x = 0;
			displacement_max = 1.f;
			
			blow_timer.restart();
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
	
	// displacement.x = 0;
}

void kusaka::clear_shot()
{
	count_shot = 0;
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
}

bool kusaka::search_for_enemies()
{
	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = *player_gl_b;

	PL_SIDE playerSide = getPlayerSide(player_pos->x, get_position().x);
	if (playerSide == PL_SIDE::RIGHT && look.intersects(pl))
	{
		player_l_r[1] = true;
		player_l_r[0] = false;
		return true;
	}
	else if(playerSide == PL_SIDE::LEFT && look.intersects(pl))
	{
		player_l_r[0] = true;
		player_l_r[1] = false;
		return true;
	}

	player_l_r[0] = false;
	player_l_r[1] = false;
	return false;


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



	/*int centerX = get_position().x / 64;
	int centerY = get_position().y / 64;


	for (int i = centerY - 1; i <= centerY + 1; i++)
	{
		for (int j = centerX + 1; j <= centerX + 10; j++)
		{
			if (i >= 0 && i < sandbox->getMapHeight()/64 && j >= 0 && j < sandbox->getMapWidth()/64)
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
			if (i >= 0 && i < sandbox->getMapHeight()/64 && j >= 0 && j < sandbox->getMapWidth()/64)
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
	return false;*/
}

void kusaka::reset_attention()
{
	count_shot = 0;
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump = 0;
}





