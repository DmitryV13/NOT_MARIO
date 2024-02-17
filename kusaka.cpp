#include "stdafx.h"
#include "kusaka.h"

kusaka::kusaka(TileMap& map, GeneralInfo* player_info,short regime, TextureManager* t_manager, int index, string name)
	: Enemy(map, player_info, regime, t_manager)
{
	{
		kusaka::init_sprite(index, name);
		kusaka::setAt(20);
		kusaka::setHP(1000);
		kusaka_state = ENEMY_STATE::SLEEPING;
		hp_damage_i = HP;
		kusaka_state_past = kusaka_state;
		KUSAKA_TAKING_DAMAGE_TIMER.restart();
		IDLE_timer.restart();
		DEATH_timer.restart();
		count_jm = 0;
		hp_bar->SET_ST_HP(HP);
	}
}

kusaka::kusaka(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y, TextureManager* t_manager, 
	int index, string name) 
	: Enemy(map, player_info_, pos_x, pos_y, t_manager)
{
	{
		kusaka::init_sprite(index, name);
		kusaka::setAt(20);
		kusaka::setHP(1000);
		kusaka_state = ENEMY_STATE::SLEEPING;
		hp_damage_i = HP;
		kusaka_state_past = kusaka_state;
		KUSAKA_TAKING_DAMAGE_TIMER.restart();
		IDLE_timer.restart();
		DEATH_timer.restart();
		count_jm = 0;
		hp_bar->SET_ST_HP(HP);
	}
}

void kusaka::init_sprite(int index, string name)
{
	current_area = IntRect(0, 0, 1280, 192);
	observation_area.setTextureRect(current_area);


	anim_area.setTexture(t_manager->getTexture(index, name));
	standard_frame = IntRect(0, 0, 90, 55);
	anim_area.setTextureRect(standard_frame);



	//Enemy_T = init_texture();
	//Enemy_S.setTexture(kusaka_t_);
	current_frame = IntRect(0, 0, 64, 55);
	Enemy_S.setTextureRect(current_frame);
}


void kusaka::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 0;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 281;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 281;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.05f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 0;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}

	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_MOVING_DOWN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 70;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 70;
			}


			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (count_shot == 0)
			{
				standard_frame.left = 0.f;
			}
			count_shot++;

			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 70;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 70;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			animation_counter_think--;
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 140;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 140;
			}


			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450.f)
				{
					standard_frame.left = 360.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 350;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540.f)
				{
					standard_frame.left = 450.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 350;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_RUN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 0;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.09f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450.f)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 208;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540.f)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = -90;
				standard_frame.top = 208;
			}

			anim_area.setTextureRect(standard_frame);
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
	animation_state = ENEMY_ANIMATION_STATE::ENEMY_SHOT;
	//player_->changeHP(-attack_-(rand()%5));
	player_info->changeHP(-attack_ - (rand() % 5));
}


void kusaka::attack()
{
	//if (animation_state != ENEMY_ANIMATION_STATE::ENEMY_SHOT)animation_state = ENEMY_ANIMATION_STATE::ENEMY_ATTENTION;
	//if (isPlayerInRadius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 192))
	//{
	//	if (count_jump == 0)
	//	{
	//		//jump(1.f);
	//		jump_towards_player();
	//		count_jump++;
	//	}
	//}
	//else reset_attention();
	if (sting())
	{
		displacement.x = 0;
		displacement_max = 1.f;
		FloatRect en = get_global_bounds();
		FloatRect pl = player_info->getGlobalBounds();
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

		if (blow_timer.getElapsedTime().asSeconds() >= 0.9)
		{
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SHOT;
			shot();
			//clear_shot();
			displacement.x = 0;
			displacement_max = 1.f;

			blow_timer.restart();
		}
	}
	else kusaka_state = ENEMY_STATE::IDLE;
	//else
	//{
	//	if (jump_tile || !on_ground)displacement_max = 1.f;
	//	else displacement_max = 5.f;
	//	if (player_l_r[0] && displacement.x > 0)
	//	{
	//		displacement.x = 0;
	//		moving = -1.f;
	//		looks_to_the_right = false;
	//		looks_to_the_left = true;
	//	}
	//	else if (player_l_r[0] && displacement.x < 0)
	//	{
	//		displacement.x = 0;
	//		//moving= 1.f;
	//		looks_to_the_right = false;
	//		looks_to_the_left = true;
	//	}
	//	else if (player_l_r[1] && displacement.x > 0)
	//	{
	//		displacement.x = 0;
	//		looks_to_the_right = true;
	//		looks_to_the_left = false;
	//		//moving = 1.f;
	//	}
	//	else
	//	{
	//		displacement.x = 0;
	//		moving = 1.f;
	//		looks_to_the_right = true;
	//		looks_to_the_left = false;
	//	}
	//	displacement.x += 10 * moving * acceleration;
	//}

	// displacement.x = 0;
}

void kusaka::clear_shot()
{
	count_shot = 0;
}

bool kusaka::search_for_enemies()
{
	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = player_info->getGlobalBounds();

	ORIENTATION playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (playerSide == ORIENTATION::RIGHT && look.intersects(pl))
	{
		player_l_r[1] = true;
		player_l_r[0] = false;
		return true;
	}
	else if (playerSide == ORIENTATION::LEFT && look.intersects(pl))
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
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump = 0;
}

void kusaka::reset_Timer()
{
	if (kusaka_state_past != kusaka_state)
	{
		IDLE_timer.restart();
		DEATH_timer.restart();
		kusaka_state_past = kusaka_state;
	}
}

void kusaka::update_movement()
{
	if (HP <= 0)kusaka_state = ENEMY_STATE::DEATH;
	if (hp_damage_i > HP && kusaka_state != ENEMY_STATE::DEATH)
	{
		kusaka_state = ENEMY_STATE::TAKING_DAMAGE;
	}
	//if (!search_for_enemies())clear_shot();
	switch (kusaka_state)
	{
	case ENEMY_STATE::IDLE:
		{
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_IDLE;
			if (search_for_enemies())
			{
				kusaka_state = ENEMY_STATE::ATTACKING;
			}
			if(kusaka_state_past == ENEMY_STATE::E_JUMPING)
			{
				kusaka_state = ENEMY_STATE::MOVING;
				break;
			}
			reset_Timer();

			if (update_collision_x() && update_collision_x_jump())
			{
				jump_flag = true;
				kusaka_state = ENEMY_STATE::E_JUMPING;
				break;
			}
			if (IDLE_timer.getElapsedTime().asSeconds() >= 1.5f)
			{
				
				 if (hit_a_wall())
				{
					kusaka_state = ENEMY_STATE::MOVING;
					moving *= -1.f;
					animation_state = ENEMY_ANIMATION_STATE::ENEMY_MOVING;
				}
				else
				{
					kusaka_state = ENEMY_STATE::MOVING;
				}
				if (rand() % 2 && !search_for_enemies())kusaka_state = ENEMY_STATE::SLEEPING;


				IDLE_timer.restart();
			}
			else
			{
				displacement.x = 0;
				displacement_max = 1.f;
			}
			//animation_state = ENEMY_ANIMATION_STATE::ENEMY_IDLE;

			break;
		}
	case ENEMY_STATE::E_JUMPING:
		{
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_JUMPING;
			kusaka_state_past = kusaka_state;
			if (on_ground && jump_flag)
			{
				jump(1.3f);
				on_ground = false;
				jump_tile = true;
				count_jm++;
				displacement_max = 3.f;
				displacement.x *= displacement_max;
			}

			else if (!canJumpForward() || count_jm > 4)
			{
				count_jm = 0;
				jump_flag = false;
				kusaka_state = ENEMY_STATE::IDLE;
				displacement_max = 1.f;
			}
			if (search_for_enemies())kusaka_state = ENEMY_STATE::ATTACKING;

			walk(moving);


			break;
		}
	case ENEMY_STATE::MOVING:
		{
			kusaka_state_past = kusaka_state;
			if (search_for_enemies())
			{
				kusaka_state = ENEMY_STATE::ATTACKING;
				reset_Timer();
				break;
			}
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_MOVING;
			if (update_collision_x())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					kusaka_state = ENEMY_STATE::E_JUMPING;
				}
				else moving *= -1.f;
			}
			if (rand() % 10 > 5)kusaka_state = ENEMY_STATE::IDLE;
			walk(moving);
			break;
		}
	case ENEMY_STATE::ATTACKING:
		{
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_ATTENTION;
			kusaka_state_past = kusaka_state;
			if (search_for_enemies())
			{
				kusaka_state = ENEMY_STATE::RUNNING;
			}
			if (isPlayerInRadius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 192))
			{
				if (count_jump == 0)
				{
					//jump(1.f);
					jump_towards_player();
					count_jump++;
					kusaka_state = ENEMY_STATE::E_JUMPING;
				}
			}
			else reset_attention();
			if (sting())
			{
				kusaka_state = ENEMY_STATE::SHOT;
			}
			if (update_collision_x())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					kusaka_state = ENEMY_STATE::E_JUMPING;
				}
				else moving *= -1.f;
			}

			walk(moving);
			break;
		}
	case ENEMY_STATE::SHOT:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SHOT;
			if (search_for_enemies() && (on_ground))
			{
				attack();
			}
			else
			{
				reset_attention();
				clear_shot();

				kusaka_state = ENEMY_STATE::IDLE;
			}
			walk(moving);
			break;
		}

	case ENEMY_STATE::DEATH:
		{

			kusaka_state_past = kusaka_state;
			displacement.x = 0;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_DEATH;
			break;
		}
	case ENEMY_STATE::TAKING_DAMAGE:
		{
			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_TAKING_DAMAGE;
			if (HP <= 0)
			{
				kusaka_state = ENEMY_STATE::DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				KUSAKA_TAKING_DAMAGE_TIMER.restart();
				hp_damage_i = HP;
			}
			if (KUSAKA_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 0.5f)
			{
				kusaka_state = ENEMY_STATE::IDLE;
			}

			break;
		}
	case ENEMY_STATE::RUNNING:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_RUN;
			if (search_for_enemies())
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
			else kusaka_state = ENEMY_STATE::IDLE;


			walk(moving);
			kusaka_state = ENEMY_STATE::ATTACKING;
			break;
		}

	case ENEMY_STATE::SLEEPING:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SLEEP;
			displacement.x = 0.f;
			if (search_for_enemies()) kusaka_state = ENEMY_STATE::IDLE;

			break;
		}

	default:
		{

			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SLEEP;
			kusaka_state = ENEMY_STATE::SLEEPING;
			break;
		}
	}


	/*if (step_right == max_step)
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
	}*/

	//if (on_ground && canMoveForward())
	//{
	//	// Враг может двигаться вперед
	//	moving *= -1.f;
	//}

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
	//walk(moving);
}

void kusaka::walk(const float dir_x)
{
	if (dir_x > 0)
	{
		looks_to_the_right = true;
		looks_to_the_left = false;
	}
	else
	{
		looks_to_the_right = false;
		looks_to_the_left = true;
	}

	//movement on the ground
	if (on_ground && kusaka_state != ENEMY_STATE::IDLE && kusaka_state != ENEMY_STATE::TAKING_DAMAGE &&
		kusaka_state != ENEMY_STATE::DEATH
		&& kusaka_state != ENEMY_STATE::SLEEPING && kusaka_state != ENEMY_STATE::SHOT)
	{
		displacement.x += dir_x * acceleration;
	}

	// limits
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	//logic when exposing a player
}

bool kusaka::update_collision_move_x()
{
	int blockSize = 64;
	int totalPixels = 0;
	int collidedPixels = 0;

	sf::Vector2f startPosition = get_position();
	sf::Vector2f newPosition = startPosition;

	for (float y = Enemy_S.getPosition().y; y < Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height; y++)
	{
		for (float x = Enemy_S.getPosition().x; x < Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width; x++)
		{
			int i = static_cast<int>(y / blockSize);
			int j = static_cast<int>(x / blockSize);
			++totalPixels;
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				++collidedPixels;
			}
		}
	}

	set_position(newPosition.x, newPosition.y);

	return (collidedPixels > totalPixels * 0.2);
}
