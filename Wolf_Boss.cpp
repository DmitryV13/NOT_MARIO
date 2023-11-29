#include "stdafx.h"
#include "Wolf_Boss.h"


Wolf_Boss::Wolf_Boss(TileMap& map, Player& pl) : Enemy(map, pl)
{
	Wolf_Boss::init_texture();
	Wolf_Boss::init_sprite();
	Wolf_Boss::init_physics();
}

void Wolf_Boss::init_physics()
{
	rand_ = 0;
	awakening = false;
	retreat_counter = 0;
	max_retreat_duration = 100;
	boss_state = Boss_STATE::SLEEP;
	displacement_max = 2.5f;
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
	attention_counter = 3;
	looks_to_the_left = false;
	looks_to_the_right = true;
	animation_counter_think = 0;
	max_step = 1000;
	pl_contact = false;
	pl_cont_jump = false;
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

PL_Side Wolf_Boss::getPlayerSide(float playerX, float enemyX)
{
	if (playerX < enemyX)
	{
		return PL_Side::LEFT;
	}
	else
	{
		return PL_Side::RIGHT;
	}
}

void Wolf_Boss::update_movement()
{
	if (!awakening)
	{
		if (search_for_enemies())
		{
			awakening = true;
			boss_state = Boss_STATE::IDLE;
		}
	}
	else
	{
		float distanceToPlayer = std::abs(player_->getPosition().x - get_position().x);
		switch (boss_state)
		{
		case Boss_STATE::SLEEP:
			{
				displacement.x = 0.f;
				animation_state = Enemy_ANIMATION_STATES::ENEMY_SLEEP;
				break;
			}
		case Boss_STATE::IDLE:
			{
				retreat_counter++;
				displacement.x = 0.f;
				animation_state = Enemy_ANIMATION_STATES::ENEMY_IDLE;
				if (retreat_counter >= max_retreat_duration)
				{
					PL_Side playerSide = getPlayerSide(player_->getPosition().x, get_position().x);
					if (playerSide == PL_Side::LEFT)
					{
						looks_to_the_left = true;
						looks_to_the_right = false;
						if (moving > 0)moving *= -1.f;
					}
					else
					{
						looks_to_the_left = false;
						looks_to_the_right = true;
						if (moving < 0)moving *= -1.f;
					}

					retreat_counter = 0;
					boss_state = Boss_STATE::ATTACKING;
				}
				break;
			}

		case Boss_STATE::MOVING:
			{
			std::cout << "Moving\n";

				if (on_ground)
				{
					if (update_collision_x())
					{
						moving *= -1.f;
						look(moving);
					}
				}
				if (step_right == max_step)
				{
					looks_to_the_left = true;
					looks_to_the_right = false;
					moving *= -1.f;
					boss_state = Boss_STATE::RETREATING;
					reset_step();
				}
				if (step_left == max_step)
				{
					looks_to_the_left = false;
					looks_to_the_right = true;
					moving *= -1.f;
					boss_state = Boss_STATE::RETREATING;
					reset_step();
				}
				if (player_contact())
				{
					pl_contact = true;
					attack();
				}
				else reset_attention();
				/*if (distanceToPlayer > 10 * 60)
				{
					boss_state = Boss_STATE::RETREATING;
					break;
				}*/
				//��������� �������� � ������� ������, � ��� �� ���������� ��� ������������� � ������ ��� �����������
				walk(moving);
				break;
			}

		case Boss_STATE::JUMPING:
			{
				if (on_ground)
				{
					if (update_collision_x())
					{
						moving *= -1.f;
						look(moving);
					}
				}
				if (step_right == max_step)
				{
					looks_to_the_left = true;
					looks_to_the_right = false;
					moving *= -1.f;
					reset_step();
				}
				if (step_left == max_step)
				{
					looks_to_the_left = false;
					looks_to_the_right = true;
					moving *= -1.f;
					reset_step();
				}
				/*if (distanceToPlayer > 10 * 60)
				{
					boss_state = Boss_STATE::RETREATING;
					break;
				}*/
				walk(moving);

				
				if (!pl_cont_jump && count_anger >99)
				{
					count_anger = 0;
					reset_step();
					boss_state = Boss_STATE::RETREATING;
				}
				
				if ((std::abs(player_->getPosition().x - get_position().x) < 7 * 60) && (std::abs(player_->getPosition().x - get_position().x) > 3 * 60)
					&& ((getPlayerSide(player_->getPosition().x, get_position().x) == PL_Side::LEFT && looks_to_the_left) ||
						(getPlayerSide(player_->getPosition().x, get_position().x) == PL_Side::RIGHT && looks_to_the_right)) || pl_cont_jump)
				{
					if (!pl_cont_jump)distance = (player_->getPosition().x - get_position().x);

					//jump_towardsS_player();
					count_anger++;
					if (count_anger == 10)
					{
						if ((distance) > 0)jump(1.4);
						else jump(1.5);
						std::cout << "jump\n";
						//jump(1);
						count_anger++;
						pl_cont_jump = true;
					}
					if (pl_cont_jump && on_ground && count_anger == 100)
					{
						shot();

						Enemy_S.setPosition(get_position().x - (distance),
							get_position().y);
						pl_cont_jump = false;
						count_anger++;
					}

				}
				else pl_contact = true;
				break;
			}

		case Boss_STATE::ATTACKING:
			{
			
				if (rand_ == 0)
				{
					rand_++;
					boss_state = Boss_STATE::JUMPING;
				}
				else if(rand_ == 1)
				{
					rand_++;
					boss_state = Boss_STATE::MOVING;
				}
				else if(rand_ == 2)
				{
					rand_ ++;
					boss_state = Boss_STATE::HOWL;
				}else
				{
					rand_ = 0;
					boss_state = Boss_STATE::TORMENT;
				}

				//�������� ��� ���� 
				break;
			}


		case Boss_STATE::RETREATING:
			{
				retreat_counter++;
				displacement.x = 0.f;

				animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
				if (retreat_counter >= max_retreat_duration)
				{
					retreat_counter = 0;
					boss_state = Boss_STATE::IDLE;
				}
				break;
			}
		case Boss_STATE::HOWL:
			{
			PL_Side playerSide = getPlayerSide(player_->getPosition().x, get_position().x);
			if (playerSide == PL_Side::LEFT)
			{
				looks_to_the_left = true;
				looks_to_the_right = false;
				if (moving > 0)moving *= -1.f;
			}
			else
			{
				looks_to_the_left = false;
				looks_to_the_right = true;
				if (moving < 0)moving *= -1.f;
			}
				animation_state = Enemy_ANIMATION_STATES::ENEMY_SHOT;
				retreat_counter++;
				displacement.x = 0;
				std::cout << "HOWL\n";
				if(retreat_counter>100)
				{
					shot_HOWL();
					retreat_counter = 0;
					boss_state = Boss_STATE::RETREATING;
				}
				break;
			}
		case Boss_STATE::TORMENT:
			std::cout << "TORMENT";
			{
			PL_Side playerSide = getPlayerSide(player_->getPosition().x, get_position().x);
			if (!sting() && retreat_counter == 0) {
				if (playerSide == PL_Side::LEFT)
				{
					looks_to_the_left = true;
					looks_to_the_right = false;
					if (moving > 0)moving *= -1.f;
					
					attack();
					walk(moving);
				}
				else
				{
					looks_to_the_left = false;
					looks_to_the_right = true;
					if (moving < 0)moving *= -1.f;
					attack();
					walk(moving);
				}
			}

				if(sting() && retreat_counter < 50)
				{
					retreat_counter++;
					displacement.x = 0;
					bite();
				}
				if(retreat_counter == 50)
				{
					retreat_counter++;
					moving *= -1.f;
					walk(moving);
				}
				if(retreat_counter>50 && retreat_counter<300)
				{
					retreat_counter++;
					walk(moving);

				}
				if(retreat_counter > 299)
				{
					retreat_counter = 0;
					boss_state = Boss_STATE::RETREATING;
					reset_attention();

				}


			break;
			}
		}
	}
	if (!search_for_enemies() && awakening)

	{
		std::cout << "pppppppppp";

		if (on_ground)
		{
			if (update_collision_x())
			{
				moving *= -1.f;
				look(moving);
			}
		}
		if (step_right == max_step)
		{
			moving *= -1.f;
			reset_step();
		}
		if (step_left == max_step)
		{
			moving *= -1.f;
			reset_step();
		}

		if (moving > 0)
		{
			looks_to_the_left = true;
			looks_to_the_right = false;
		}
		else
		{
			looks_to_the_left = false;
			looks_to_the_right = true;
		}

		walk(moving);
	}

	////decision explorer
	/*if (on_ground)
	{
		if (update_collision_x())
		{
			moving *= -1.f;
		}
	}*/
	////step limits
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
}

void Wolf_Boss::look(float direction)
{
	if (direction > 0)
	{
		looks_to_the_right = true;
		looks_to_the_left = false;
	}
	else
	{
		looks_to_the_right = false;
		looks_to_the_left = true;
	}
}
void Wolf_Boss::bite()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_BITE;

}

void Wolf_Boss::reset_step()
{
	step_left = 0;
	step_right = 0;
	pl_contact = false;
}


void Wolf_Boss::shot()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_SHOT;
}

void Wolf_Boss::attack()
{
	animation_state = Enemy_ANIMATION_STATES::ENEMY_ATTENTION;
	//jump_towards_player();

	displacement_max = 10.f;
	displacement.x += moving * displacement_max;

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


	//displacement.x += 10 * moving * acceleration;


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
	int centerX = get_position().x / 60;
	int centerY = get_position().y / 60;
	int dist = 30;


	for (int i = centerY - 10; i <= centerY + 10; i++)
	{
		for (int j = centerX - dist; j <= centerX + dist; j++)
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


	return false;
}

void Wolf_Boss::reset_attention()
{
	displacement_max = 2.5f;
	displacement.x += moving * acceleration;
}

void Wolf_Boss::walk(const float dir_x)
{
	/*if (dir_x > 0)
	{
		looks_to_the_right = true;
		looks_to_the_left = false;
	}
	else
	{
		looks_to_the_right = false;
		looks_to_the_left = true;
	}*/
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

	if (displacement.x != 0.0f) { look(displacement.x); }
	/*if (animation_counter_think > 2 && animation_state != Enemy_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		displacement.x = 0;
		animation_state = Enemy_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = Enemy_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = Enemy_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = Enemy_ANIMATION_STATES::ENEMY_MOVING;*/


	//logic when exposing a player
	/*if (search_for_enemies() && ((on_ground) || (jump_tile)))
	{
		attack();
	}
	else
	{
		reset_attention();
		clear_shot();
	}*/
}


void Wolf_Boss::update_physics()
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

		displacement.x = 2 * moving * displacement_max;
		//jump deceleratin
		jump_velocity *= 0.96;
	}
	// deceleration
	displacement *= deceleration;

	// limits

	if (update_collision_x())
	{
		displacement.x = 0.f;
	}
	if (update_collision_y())
	{
		displacement.y = 0.f;
	}
	//step counter
	if ((displacement.x > 0 && pl_contact) || !pl_cont_jump)
		step_right++;
	if ((displacement.x < 0 && pl_contact )|| !pl_cont_jump)
		step_left++;
	//if (player_contact())displacement.x *= 1.3f;
	Enemy_S.move(displacement);
}


void Wolf_Boss::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = dir_y * 5.5f;
	}
}

void Wolf_Boss::shot_HOWL()
{


}
