#include "stdafx.h"
#include "EyeEvil.h"


EyeEvil::EyeEvil(TileMap& map, GeneralInfo* player_info)
	: Enemy(map, player_info)
{
	{
		EyeEvil::init_texture();
		EyeEvil::init_sprite();
		EyeEvil::setAt(20);
		EyeEvil::setHP(1000);
		hp_damage_i = HP;
		eye_state = eye_state_past = EYE_EVIL_STATE::IDLE;
		IDLE_timer.restart();
		ATTACKING_timer.restart();
		DEATH_timer.restart();
	}
}


void EyeEvil::init_texture()
{
	if (!Enemy_T.loadFromFile("Textures/Enemies/eye.png"))
	{
		std::cout << "Error -> Enemy -> couldn't load enemy texture" << std::endl;
	}
}

void EyeEvil::init_sprite()
{
	current_area = IntRect(0, 0, 640, 67);
	observation_area.setTextureRect(current_area);

	Enemy_S.setTexture(Enemy_T);
	current_frame = IntRect(0, 0, 60, 55.4);
	Enemy_S.setTextureRect(current_frame);
}

void EyeEvil::reset_Timer()
{
	if (eye_state_past != eye_state)
	{
		IDLE_timer.restart();
		DEATH_timer.restart();
		ATTACKING_timer.restart();
		eye_state_past = eye_state;
	}
}

void EyeEvil::changeHP(short i)
{
	if(eye_state != EYE_EVIL_STATE::TAKING_DAMAGE && eye_state != EYE_EVIL_STATE::DEATH)Enemy::changeHP(i);
}

void EyeEvil::update_movement()
{
	if (HP <= 0)eye_state = EYE_EVIL_STATE::DEATH;
	if (hp_damage_i > HP && eye_state != EYE_EVIL_STATE::DEATH)
	{
		eye_state = EYE_EVIL_STATE::TAKING_DAMAGE;
	}
	if (!search_for_enemies())clear_shot();
	switch (eye_state)
	{
	case EYE_EVIL_STATE::IDLE:
		{
			if (search_for_enemies() && ATTACKING_timer.getElapsedTime().asSeconds() >= 6.1f)
				eye_state =
					EYE_EVIL_STATE::ATTACKING;
			reset_Timer();
			if (hit_a_wall() && update_collision_x_jump())
				{
					jump_flag = true;
					eye_state = EYE_EVIL_STATE::JUMPING;
					//animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
				break;
				}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (IDLE_timer.getElapsedTime().asSeconds() >= 1.5f)
			{
				
				 if (hit_a_wall())
				{
					eye_state = EYE_EVIL_STATE::MOVING;

					moving *= -1.f;
					animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
				}
				else
				{
					eye_state = EYE_EVIL_STATE::MOVING;
				}


				blow_timer.restart();
			}
			else
			{
				displacement.x = 0;
				displacement_max = 1.f;
			}
			//animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;

			break;
		}
	case EYE_EVIL_STATE::JUMPING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
			eye_state_past = eye_state;
			if (on_ground && jump_flag)
			{
				jump(1.2);
				on_ground = false;
				jump_tile = true;
			}
			else if (!canJumpForward() || canMoveForward())
			{
				jump_flag = false;
				eye_state = EYE_EVIL_STATE::IDLE;
			}
			walk(moving);


			break;
		}
	case EYE_EVIL_STATE::MOVING:
		{
			eye_state_past = eye_state;
			if (search_for_enemies())
			{
				eye_state = EYE_EVIL_STATE::ATTACKING;
				reset_Timer();
			}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			if (hit_a_wall())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					eye_state = EYE_EVIL_STATE::JUMPING;
				}
				else moving *= -1.f;
			}
			walk(moving);
			break;
		}
	case EYE_EVIL_STATE::ATTACKING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;


			if (search_for_enemies() && ATTACKING_timer.getElapsedTime().asSeconds() <= 5.1f)
			{
				attack();
			}
			else
			{
				reset_attention();
				clear_shot();
				reset_Timer();
				eye_state = EYE_EVIL_STATE::IDLE;
			}
			break;
		}
	case EYE_EVIL_STATE::DEATH:
		{
			displacement.x = 0;
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			break;
		}
	case EYE_EVIL_STATE::TAKING_DAMAGE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			if (HP <= 0)
			{
				eye_state = EYE_EVIL_STATE::DEATH;
				break;
			}

			if (hp_damage_i > HP)
			{
				hp_damage_i = HP;
			}
			else
			{
				eye_state = EYE_EVIL_STATE::IDLE;
			}

			break;
		}

	default:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			eye_state = EYE_EVIL_STATE::IDLE;
		}
	}
	//decision explorer
	/*if (on_ground)
	{
		if (update_collision_x())
		{
			if (!update_collision_x_jump())
			{
				jump(1);
				on_ground = false;
				jump_tile = true;
			}
			else moving *= -1.f;
		}
	}*/
	//step limits
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
	//if (on_ground && !canMoveForward())
	//{
	//	// Враг может двигаться вперед
	//	walk(moving);
	//}
	//else
	//{
	//	// Враг не может двигаться вперед, разворачиваемся
	//	moving *= -1.f;
	//}
	if (moving > 0)
	{
		looks_to_the_right = true;
		looks_to_the_left = false;
	}
	else
	{
		looks_to_the_right = false;
		looks_to_the_left = true;
	}


	//walk(moving);
}

void EyeEvil::walk(const float dir_x)
{
	//movement on the ground
	if (on_ground && eye_state != EYE_EVIL_STATE::IDLE)
	{
		displacement.x += dir_x * acceleration;
	}
	if (eye_state == EYE_EVIL_STATE::JUMPING)
	{
		displacement_max = 2.2f;
		displacement.x = 2 * moving * displacement_max;
	}
	else displacement_max = 1.f;

	// limits
	/*if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	if (animation_counter_think > 2 && animation_state != ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		displacement.x = 0;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;*/


	//logic when exposing a player
}

void EyeEvil::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_JUMPING)
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

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (attention_counter == 3)current_frame.left = 0.f;
				attention_counter--;
				current_frame.left += 60;

				if (current_frame.left >= 360.f)
				{
					current_frame.left = 300.f;
				}
				current_frame.top = 240;
				current_frame.width = 60;
			}
			else
			{
				if (attention_counter == 3)current_frame.left = 60.f;
				attention_counter--;
				current_frame.left += 60;

				if (current_frame.left >= 420.f)
				{
					current_frame.left = 360.f;
				}
				current_frame.top = 240;
				current_frame.width = -60;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.05f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (attention_counter == 3)current_frame.left = 60.f;
				attention_counter--;
				current_frame.left += 60;

				if (current_frame.left >= 300.f)
				{
					current_frame.left = 240.f;
				}
				current_frame.top = 240;
				current_frame.width = 60;
			}
			else
			{
				if (attention_counter == 3)current_frame.left = 180.f;
				attention_counter--;
				current_frame.left += 60;

				if (current_frame.left >= 360.f)
				{
					current_frame.left = 300.f;
				}
				current_frame.top = 240;
				current_frame.width = -60;
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

void EyeEvil::shot()
{
	if (looks_to_the_right)
	{
		laserFL = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y,
		                           looks_to_the_right, player_info);
		laser = new laser_weapon(*sandbox, 2, Enemy_S.getPosition().x + 64, Enemy_S.getPosition().y,
		                         looks_to_the_right, player_info);
		//laser_weapon* shot_las = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y, looks_to_the_right);
		/*laser.push_back(*shot_las);

		for (int j = (Enemy_S.getPosition().x / 60) + 2; j < TileFactory::m && j < j + 5 &&
			!sandbox->isBlock(Enemy_S.getPosition().y / 60, j); j++)
		{
			laser_weapon* shot_cur = new laser_weapon(*sandbox, 2, j * 60, Enemy_S.getPosition().y, looks_to_the_right);
			laser.push_back(*shot_cur);

		}*/
	}
	else
	{
		laserFL = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y,
		                           looks_to_the_right, player_info);
		laser = new laser_weapon(*sandbox, 2, Enemy_S.getPosition().x - 64, Enemy_S.getPosition().y,
		                         looks_to_the_right, player_info);
		//laser_weapon* shot_las = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x - 60, Enemy_S.getPosition().y, looks_to_the_right);
		/*laser.push_back(*shot_las);
		for (int j = (Enemy_S.getPosition().x / 60); j > 0 && j > j - 5 &&
			!sandbox->isBlock(Enemy_S.getPosition().y / 60, j); j--)
		{
			laser_weapon* shot_cur = new laser_weapon(*sandbox, 2, j * 60, Enemy_S.getPosition().y, looks_to_the_right);
			laser.push_back(*shot_cur);

		}*/
	}
}


void EyeEvil::attack()
{
	PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if ((playerSide == PL_SIDE::LEFT && looks_to_the_left) || (playerSide == PL_SIDE::RIGHT && looks_to_the_right))
	{
		if (attention_counter == 1)
		{
			attention_counter--;
			shot();
		}

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;

		if (laser_existence())
		{
			laser->update();
			laserFL->update();
		}
		displacement.x = 0;
	}
	else clear_shot();
}

void EyeEvil::clear_shot()
{
	//laser.clear();
	delete laser;
	delete laserFL;
	laserFL = nullptr;
	laser = nullptr;
}

bool EyeEvil::laser_existence()
{
	if (laserFL == nullptr)return false;
	else return true;
}

//int EyeEvil::laser_length()
//{
//	return (int)laser.size();
//}

void EyeEvil::draw_laser(int i, sf::RenderTarget& target)
{
	if (HP >= 0)laserFL->render_FL(target);
	if (HP >= 0)laser->render(target);
}

void EyeEvil::reset_attention()
{
	attention_counter = 3;
}


bool EyeEvil::search_for_enemies()
{
	FloatRect en = observation_area.getGlobalBounds();
	FloatRect pl = player_info->getGlobalBounds();
	PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (playerSide == PL_SIDE::RIGHT && looks_to_the_right)
	{
		return en.intersects(pl);
	}
	else if (playerSide == PL_SIDE::LEFT && looks_to_the_left)
	{
		return en.intersects(pl);
	}


	/*int centerX = get_position().x / 64;
	int centerY = get_position().y / 64;

	if (looks_to_the_right)
	{
		for (int i = centerY - 1; i <= centerY + 1; i++)
		{
			for (int j = centerX + 1; j <= centerX + 5; j++)
			{
				if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
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
				if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
				{
					if (sandbox->isOccupied(i, j))
					{
						return true;
					}
				}
			}
		}
	}

	return false;*/
	return false;
}
