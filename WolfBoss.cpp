#include "stdafx.h"
#include "WolfBoss.h"


WolfBoss::WolfBoss(TileMap& map, GeneralInfo* player_info)
	: Enemy(map, player_info)
{
	WolfBoss::init_texture();
	WolfBoss::init_sprite();
	WolfBoss::init_physics();
	WolfBoss::setAt(50);
	WolfBoss::setHP(5000);
}

void WolfBoss::init_physics()
{
	hp_damage_i = HP;
	boss_state_TORMENT = false;
	boss_state_past = BOSS_STATE::IDLE;
	BOSS_TAKING_DAMAGE_TIMER.restart();
	IDLE_timer.restart();
	DEATH_timer.restart();
	Shot_timer.restart();
	count_jm = 0;
	rand_ = 0;
	awakening = false;
	retreat_counter = 0;
	max_retreat_duration = 100;
	boss_state = BOSS_STATE::SLEEP;
	
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

void WolfBoss::init_texture()
{
	if (!Wolf_Boss_t_.loadFromFile("Textures/Enemies/wolf.png"))
	{
		std::cout << "Error -> Enemy_Wolf_Boss -> couldn't load enemy_Wolf_Boss texture" << std::endl;
	}
}

void WolfBoss::init_sprite()
{
	current_area = IntRect(0, 0, 2000, 200);
	observation_area.setTextureRect(current_area);

	standard_frame = IntRect(0, 0, 128, 128);
	observation_area.setTextureRect(current_area);


	Enemy_S.setTexture(Wolf_Boss_t_);
	current_frame = IntRect(0, 0, 128, 128);
	Enemy_S.setTextureRect(current_frame);
}

void WolfBoss::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.15f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				current_frame.left += 128;
				if (current_frame.left >= 384.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 128;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 128;
				if (current_frame.left >= 512.f)
				{
					current_frame.left = 128.f;
				}
				current_frame.width = -128;
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
			if (looks_to_the_right)
			{
				current_frame.left += 128;
				if (current_frame.left >= 384.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 128;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 128;
				if (current_frame.left >= 512.f)
				{
					current_frame.left = 128.f;
				}
				current_frame.width = -128;
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
				current_frame.left += 128;
				if (current_frame.left >= 384.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 128;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 128;
				if (current_frame.left >= 512.f)
				{
					current_frame.left = 128.f;
				}
				current_frame.width = -128;
				current_frame.top = 0;
			}
			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}

	/*else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
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

PL_SIDE WolfBoss::getPlayerSide(float playerX, float enemyX)
{
	if (playerX < enemyX)
	{
		return PL_SIDE::LEFT;
	}
	else
	{
		return PL_SIDE::RIGHT;
	}
}

void WolfBoss::reset_Timer()
{
	if (boss_state_past != boss_state)
	{
		count_anim = 0;
		IDLE_timer.restart();
		DEATH_timer.restart();
		blow_timer.restart();
		Shot_timer.restart();
		RETREATING_timer.restart();
		Jumping_att_timer.restart();
		boss_state_past = boss_state;
		distance = (player_info->getPosition().x - get_position().x);
	}
}

void WolfBoss::update_movement()
{
	if (HP <= 0) {
		boss_state = BOSS_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP)
	{
		boss_state = BOSS_STATE::TAKING_DAMAGE;
	}
	if (!sting())boss_state_TORMENT = false;
	float distanceToPlayer = std::abs(player_info->getPosition().x - get_position().x);
	switch (boss_state)
	{
	case BOSS_STATE::SLEEP:
		{
			std::cout << "sleep\n";
			displacement.x = 0.f;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
			if (isPlayerInRadius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 500))
			{
				reset_Timer();
				if(IDLE_timer.getElapsedTime().asSeconds() >= 1.5f)
				{
						boss_state = BOSS_STATE::IDLE;
				}
			
			}
			break;
		}
	case BOSS_STATE::IDLE:
		{
			std::cout << "idle\n";

			reset_Timer();
			//retreat_counter++;
			displacement.x = 0.f;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (IDLE_timer.getElapsedTime().asSeconds() >= 2.5f)
			{
				PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
				if (playerSide == PL_SIDE::LEFT)
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

				//retreat_counter = 0;
			}
			if (IDLE_timer.getElapsedTime().asSeconds() >= 5.7f)
			{
				boss_state = BOSS_STATE::ATTACKING;
				IDLE_timer.restart();
			}

			break;
		}

	case BOSS_STATE::MOVING:
		{
			reset_Timer();
			std::cout << "Moving\n";
			displacement_max = 0.8f;
			if (on_ground)
			{
				if (update_collision_x())
				{
					moving *= -1.f;
					look(moving);
				}
			}
			PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
			if (playerSide == PL_SIDE::LEFT)
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
			//if (step_right == max_step)
			//{
			//	looks_to_the_left = true;
			//	looks_to_the_right = false;
			//	moving *= -1.f;
			//	//boss_state = BOSS_STATE::RETREATING;
			//	reset_step();
			//}
			//if (step_left == max_step)
			//{
			//	looks_to_the_left = false;
			//	looks_to_the_right = true;
			//	moving *= -1.f;
			//	//boss_state = BOSS_STATE::RETREATING;
			//	reset_step();
			//}
			if (sting())
			{
				pl_contact = true;
				boss_state = BOSS_STATE::PUNCH;
			}
			else reset_attention();
			/*if (distanceToPlayer > 10 * 60)
			{
				boss_state = BOSS_STATE::RETREATING;
				break;
			}*/
			//расширить повороты в сторону игрока, а так же поработать над ограничениями и атакой при приближении
			walk(moving);
			break;
		}
	case BOSS_STATE::PUNCH:
		{

		std::cout << "PUNCH\n";

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_PUNCH;
			reset_Timer();
			displacement.x = 0.f;
			if (Shot_timer.getElapsedTime().asSeconds() >= 1.2f)
			{
				boss_state = BOSS_STATE::RETREATING;
				Shot_timer.restart();
				if (boss_state_TORMENT)boss_state = BOSS_STATE::DOUBLE_KICK;
			}
				if (Shot_timer.getElapsedTime().asSeconds() >= 1.1F)
				{
					shot();
				}
			

			break;
		}
	case BOSS_STATE::JUMPING:
		{
			std::cout << "jumping\n";
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
			if (on_ground)
			{
				if (update_collision_x())
				{
					moving *= -1.f;
					look(moving);
				}
			}
			/*	if (step_right == max_step)
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
				}*/
			/*if (distanceToPlayer > 10 * 60)
			{
				boss_state = BOSS_STATE::RETREATING;
				break;
			}*/

			if (!pl_cont_jump)walk(moving);

			if ((std::abs(player_info->getPosition().x - get_position().x) < 7 * 64) && (std::abs(
					player_info->getPosition().x - get_position().x) > 3 * 64)
				&& ((getPlayerSide(player_info->getPosition().x, get_position().x) == PL_SIDE::LEFT &&
						looks_to_the_left) ||
					(getPlayerSide(player_info->getPosition().x, get_position().x) == PL_SIDE::RIGHT &&
						looks_to_the_right)) || pl_cont_jump)
			{
				reset_Timer();

				//jump_towardsS_player();
				//count_anger++;
				if (Jumping_att_timer.getElapsedTime().asSeconds() <= 0.1f)
				{
					if ((distance) > 0)jump(1.4F);
					else jump(1.5);
					//std::cout << "jump\n";
					//jump(1);
					//count_anger++;
					pl_cont_jump = true;
				}
				if (pl_cont_jump && on_ground && Jumping_att_timer.getElapsedTime().asSeconds() >= 1.0f)
				{
					shot();
					while (true)
					{
						
						sf::Vector2f tmp = calculateRandomPosition(get_global_bounds(), 10);
						//std::cout << tmp.x / 64 << " " << tmp.y / 64 << "\n";
						if (tmp.x / 64 == 0)tmp.x = 64;
						if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
						if (!sandbox->isBlock(tmp.y / 64, tmp.x / 64))
						{
							set_position(tmp.x, tmp.y);
							break;
						}
						else set_position(get_position().x, get_position().y);
					}
					//Enemy_S.setPosition(get_position().x - (distance),get_position().y);
					pl_cont_jump = false;
					boss_state = BOSS_STATE::IDLE;
					Jumping_att_timer.restart();
				}
			}
			else pl_contact = true;
			break;
		}
	case BOSS_STATE::TAKING_DAMAGE:
	{
		reset_Timer();
		boss_state_TORMENT = false;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
		if (HP <= 0)
		{
			hp_damage_i = HP;
			boss_state = BOSS_STATE::DEATH;
			break;
		}
		if (hp_damage_i > HP)
		{
			BOSS_TAKING_DAMAGE_TIMER.restart();
			hp_damage_i = HP;

		}
		if (BOSS_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 0.3f)
		{
			boss_state = BOSS_STATE::IDLE;
		}

		break;
	}
	case BOSS_STATE::RUN:
		{
		reset_Timer();
		std::cout << "RUN\n";

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
		PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);

		if (playerSide == PL_SIDE::LEFT)
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

		displacement_max = 10.f;
		displacement.x*=( displacement_max / 4);
		walk(moving);
		look(displacement.x);
			if(sting())
			{
				boss_state = BOSS_STATE::DOUBLE_KICK;
				displacement_max = 0.F;

			}


			break;
		}
	case BOSS_STATE::DOUBLE_KICK:
		{
		std::cout << "DOUBLE_KICK\n";

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_DOUBLE_KICK;
		reset_Timer();
		displacement.x = 0.f;
		if (Shot_timer.getElapsedTime().asSeconds() >= 1.2f)
		{
			boss_state = BOSS_STATE::RETREATING;
			Shot_timer.restart();
			if (boss_state_TORMENT)boss_state = BOSS_STATE::PUNCH;
		}
			if (Shot_timer.getElapsedTime().asSeconds() >= 1.1F)
			{
				shot();
				shot();
			}
		


		break;
		}
	case BOSS_STATE::ATTACKING:
		{
			std::cout << "attacking\n";
			reset_Timer();
			if (rand_ == 0)
			{
				rand_++;
				boss_state = BOSS_STATE::JUMPING;
			}
			else if (rand_ == 1)
			{
				rand_++;
				boss_state = BOSS_STATE::MOVING;
			}else if(rand_ == 2)
			{
				rand_++;
				boss_state = BOSS_STATE::RUN;
			}
			else if (rand_ == 3)
			{
				rand_++;
				boss_state = BOSS_STATE::HOWL;
			}
			else
			{
				rand_ = 0;
				boss_state = BOSS_STATE::HIT_EARTH;
			}

			//добавить еше укус 
			break;
		}


	case BOSS_STATE::RETREATING:
		{
			std::cout << "retreating\n";
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
			displacement_max = 5.f;
			if (RETREATING_timer.getElapsedTime().asSeconds() <= 2.6f)
			{
				if (playerSide == PL_SIDE::RIGHT)
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
			}
			if (IDLE_timer.getElapsedTime().asSeconds() >= 2.6f)
			{
				displacement_max = 1.f;
				boss_state = BOSS_STATE::IDLE;
				IDLE_timer.restart();
			}
			walk(moving);
			break;
		}
	case BOSS_STATE::HOWL:
		{
			std::cout << "HOWL\n";
			reset_Timer();

			PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
			if (playerSide == PL_SIDE::LEFT)
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
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_HOWL;
			retreat_counter++;
			displacement.x = 0;
			//std::cout << "HOWL\n";
			if (retreat_counter > 100)
			{
				shot_HOWL();
				retreat_counter = 0;
				boss_state = BOSS_STATE::IDLE;
			}
			break;
		}
	case BOSS_STATE::TORMENT:
		
		{
		reset_Timer();
		std::cout << "TORMENT\n";
			displacement_max = 10.f;

			PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
			if (!sting() && retreat_counter == 0)
			{
				if (playerSide == PL_SIDE::LEFT)
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
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
		if(sting())
		{
			displacement_max = 1.F;
			boss_state_TORMENT = true;
			boss_state = BOSS_STATE::PUNCH;
		}
		/*	if (sting() && retreat_counter < 50)
			{
				retreat_counter++;
				displacement.x = 0;
				bite();
			}
			if (retreat_counter == 50)
			{
				retreat_counter++;
				moving *= -1.f;
				walk(moving);
			}
			if (retreat_counter > 50 && retreat_counter < 300)
			{
				retreat_counter++;
				walk(moving);
			}
			if (retreat_counter > 299)
			{
				retreat_counter = 0;
				boss_state = BOSS_STATE::RETREATING;
				reset_attention();
			}*/


			break;
		}
		
	case BOSS_STATE::DEATH:
		{
		std::cout << "DEATH\n";

		reset_Timer();
		displacement.x = 0;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
		break;
		}
	case BOSS_STATE::HIT_EARTH:
		{
		std::cout << "HIT_EARTH\n";

		reset_Timer();
		animation_state = ENEMY_ANIMATION_STATES::HIT_EARTH;
		displacement.x = 0.f;
		if (Shot_timer.getElapsedTime().asSeconds() >= 1.2f)
		{
			boss_state = BOSS_STATE::IDLE;
			Shot_timer.restart();
			
		}
		if (Shot_timer.getElapsedTime().asSeconds() >= 1.1F)
		{
			shot();
			//ADD: falling stones
			
		}
			break;
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


void WolfBoss::look(float direction)
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

sf::Vector2f WolfBoss::calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance)
{
	int x = static_cast<int>(get_position().x / sandbox->getSizeTexture());
	int y = static_cast<int>(get_position().y / sandbox->getSizeTexture());
	int count = 1000000;
	int startDirection = (rand() % 2 == 0) ? 1 : -1;


	int spriteSizeInBlocksX = static_cast<int>(Enemy_S.getGlobalBounds().width / sandbox->getSizeTexture());
	int spriteSizeInBlocksY = static_cast<int>(Enemy_S.getGlobalBounds().height / sandbox->getSizeTexture());

	while (count--)
	{
		int randomXOffset = rand() % (2 * jumpDistance + 1) - jumpDistance; // Random offset within [-jumpDistance, jumpDistance]
		int randomYOffset = rand() % (2 * jumpDistance + 1) - jumpDistance; // Random offset within [-jumpDistance, jumpDistance]

		int newX = x + randomXOffset;
		int newY = y + randomYOffset;


		if (!sandbox->outOfMap(newY, newX))
			continue;


		if (sandbox->isBlock(newY, newX))
			continue;


		if (sandbox->outOfMap(newY + 2, newX) && !sandbox->isBlock(newY + 2, newX))
			continue;
		if (sandbox->outOfMap(newY + 1, newX) && sandbox->isBlock(newY + 1, newX))
			continue;
		return sf::Vector2f(newX * sandbox->getSizeTexture(), newY * sandbox->getSizeTexture());
	}

	return get_position();
}

void WolfBoss::bite()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_BITE;
}

void WolfBoss::reset_step()
{
	step_left = 0;
	step_right = 0;
	pl_contact = false;
}


void WolfBoss::shot()
{
	if(sting())player_info->changeHP(-attack_ - (rand() % 10));
}

void WolfBoss::attack()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
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

void WolfBoss::clear_shot()
{
}

bool WolfBoss::search_for_enemies()
{
	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = player_info->getGlobalBounds();

	PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (playerSide == PL_SIDE::RIGHT && look.intersects(pl))
	{
		player_l_r[1] = true;
		player_l_r[0] = false;
		return true;
	}
	else if (playerSide == PL_SIDE::LEFT && look.intersects(pl))
	{
		player_l_r[0] = true;
		player_l_r[1] = false;
		return true;
	}

	player_l_r[0] = false;
	player_l_r[1] = false;
	return false;
}

void WolfBoss::reset_attention()
{
	displacement_max = 2.5f;
	displacement.x += moving * acceleration;
}

void WolfBoss::walk(const float dir_x)
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
	/*if (animation_counter_think > 2 && animation_state != ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		displacement.x = 0;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;*/


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


void WolfBoss::update_physics()
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
	if ((displacement.x < 0 && pl_contact) || !pl_cont_jump)
		step_left++;
	//if (player_contact())displacement.x *= 1.3f;
	Enemy_S.move(displacement);
}


void WolfBoss::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = dir_y * 5.5f;
	}
}

void WolfBoss::shot_HOWL()
{
}
