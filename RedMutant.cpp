#include "stdafx.h"
#include "RedMutant.h"

RedMutant::RedMutant(TileMap& map, GeneralInfo* player_info)
	: Enemy(map, player_info)
{
	{
		RedMutant::init_texture();
		RedMutant::init_sprite();
		RedMutant::setAt(25);
		RedMutant::setHP(2000);
		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
		hp_damage_i = HP;
		red_mutant_state_past = red_mutant_state;
		RED_MUTANT_TAKING_DAMAGE_TIMER.restart();
		IDLE_timer.restart();
		DEATH_timer.restart();
		Shot_timer.restart();
		count_jm = 0;
	}
}

void RedMutant::init_texture()
{
	if (!chubacabra_t_.loadFromFile("Textures/Enemies/RedMutant.png"))
	{
		std::cout << "Error -> Enemy_chubacabra -> couldn't load enemy_chubacabra texture" << std::endl;
	}
}

void RedMutant::init_sprite()
{
	current_area = IntRect(0, 0, 1280, 256);
	observation_area.setTextureRect(current_area);

	Enemy_S.setTexture(chubacabra_t_);
	current_frame = IntRect(0, 0, 60, 88);
	Enemy_S.setTextureRect(current_frame);
}

void RedMutant::reset_Timer()
{
	if (red_mutant_state_past != red_mutant_state)
	{
		count_anim = 0;
		IDLE_timer.restart();
		DEATH_timer.restart();
		blow_timer.restart();
		Shot_timer.restart();
		red_mutant_state_past = red_mutant_state;
	}
}

void RedMutant::update_movement()
{
	if (HP <= 0) {
		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP)
	{
		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TAKING_DAMAGE;
	}
	if (sting() && !plStan() && displacement.x != 0.f)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
	//if (!search_for_enemies())clear_shot();
	switch (red_mutant_state)
	{
	case RED_MUTANT_STATE::RED_MUTANT_IDLE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (search_for_enemies())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;
			}
			reset_Timer();
			if (update_collision_x())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}
			if (IDLE_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				if (hit_a_wall())
				{
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_MOVING;
					moving *= -1.f;
					animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
				}
				else
				{
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_MOVING;
				}


				IDLE_timer.restart();
			}
			else
			{
				displacement.x = 0;
				displacement_max = 1.f;
			}
			//animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			std::cout << "idle\n";
			walk(moving);
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_JUMPING:
		{
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
			
			if (on_ground && jump_flag)
			{
				jump(1.2f);
				on_ground = false;
				jump_tile = true;
				count_jm++;
			}

			else if (!canJumpForward() || count_jm > 2)
			{
				count_jm = 0;
				jump_flag = false;
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			}
			if (search_for_enemies())red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;

			walk(moving);
			std::cout << "jumping\n";


			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_MOVING:
		{
			reset_Timer();
			
			if (sting() && displacement.x != 0.f)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;

			if (search_for_enemies())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;
				//reset_Timer();
				break;
			}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			if (update_collision_x())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}
			if (rand() % 10 > 5)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			if (!sting())walk(moving);
			std::cout << "moving\n";
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_ATTACKING:
		std::cout << "attaking\n";
		{	reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
			
			if (sting() && displacement.x != 0.f)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
			if (search_for_enemies())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_RUN;
			}
			else red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			//if (isPlayerInRadius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 192))
			//{
			//	if (count_jump == 0)
			//	{
			//		//jump(1.f);
			//		jump_towards_player();
			//		count_jump++;
			//		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
			//	}
			//}
			//else reset_attention();
			if (sting())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_SHOT;
			}
			if (update_collision_x())
			{
				if (canJumpForward())
				{
					jump_flag = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}

			//walk(moving);
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_SHOT:
		{
			std::cout << "shot\n";
			FloatRect en = get_global_bounds();
			FloatRect pl = player_info->getGlobalBounds();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			reset_Timer();

			if (blow_timer.getElapsedTime().asSeconds() >= 0.2f)
			{
				shot();
				blow_timer.restart();
			}
			if (Shot_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
				Shot_timer.restart();
			}

			displacement.x = 0;
			displacement_max = 1.f;

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


			if (search_for_enemies() && (on_ground))
			{
				attack();
			}
			else
			{
				reset_attention();
				clear_shot();

				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			}
			walk(moving);
			break;
		}

	case RED_MUTANT_STATE::RED_MUTANT_DEATH:
		{
			std::cout << "death\n";

			reset_Timer();
			displacement.x = 0;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_TAKING_DAMAGE:
		{
		reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			if (HP <= 0 )
			{
				hp_damage_i = HP;
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				RED_MUTANT_TAKING_DAMAGE_TIMER.restart();
				hp_damage_i = HP;
				std::cout <<HP<< "\n";
				
			}
			if (RED_MUTANT_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 0.4f)
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			}

			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_RUN:
		{
			std::cout << "run\n";
			red_mutant_state_past = red_mutant_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
			if (search_for_enemies())
			{
				if (jump_tile || !on_ground)displacement_max = 1.f;
				else displacement_max = 1.f;
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
			else red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;


			walk(moving);
			red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;
			break;
		}

	case RED_MUTANT_STATE::RED_MUTANT_TELEPORT:
		{
			std::cout << "TELEPORT\n";
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TELEPORT;
			if (Shot_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				if (teleport)
					while (true)
					{
						teleport = false;
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
				if (Shot_timer.getElapsedTime().asSeconds() >= 0.9f)
				{
					teleport = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;

					Shot_timer.restart();
				}
			}


			displacement.x = 0.f;


			break;
		}

	default:
		{
			std::cout << "default\n";

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			break;
		}
	}

	//decision explorer
	//if (on_ground)
	//{
	//	if (update_collision_x())
	//	{
	//		//переписать для подьема без прыжка
	//		if (!update_collision_x_jump())
	//		{

	//			
	//			jump(1);
	//			on_ground = false;
	//			jump_tile = true;
	//		}
	//		else moving *= -1.f;
	//	}
	//}
	////step limits
	//if (step_right == max_step)
	//{
	//	moving *= -1.f;
	//	step_right = 0;
	//	animation_counter_think = 12;
	//}
	//if (step_left == max_step)
	//{
	//	animation_counter_think = 12;
	//	moving *= -1.f;
	//	step_left = 0;
	//}if (on_ground && !canMoveForward())
	//{
	//	// Враг может двигаться вперед
	//	walk(moving);
	//}
	//else
	//{
	//	// Враг не может двигаться вперед, разворачиваемся
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


void RedMutant::walk(const float dir_x)
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
	if (on_ground)
	{
		displacement.x += dir_x * acceleration;
	}

	// limits
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	if (sting())displacement.x = 0.f;
	/*if (animation_counter_think > 2 && animation_state != ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		displacement.x = 0;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;*/


	//logic when exposing a player
	//if (search_for_enemies() && ((on_ground) || (jump_tile)))
	//{
	//	attack();
	//}
	//else
	//{
	//	reset_attention();
	//	clear_shot();
	//}
}

void RedMutant::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim == 0) {
					current_frame.left = 0;
					count_anim++;
				}
					current_frame.left += 70;
					if (current_frame.left >= 210.f)
					{
						current_frame.left = 0.f;
					}
					current_frame.width = 60;
					current_frame.top = 0;
				
			}
			else
			{
				if (count_anim == 0) {
					current_frame.left = 70;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 280.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TELEPORT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (Shot_timer.getElapsedTime().asSeconds() <= 0.5f)
				{

					if (count_anim == 1) { current_frame.left = 0; count_anim++; }

					current_frame.left += 60;
					current_frame.width = 60;
					current_frame.top = 350;
				}
				else
				{
					current_frame.left += 60;
					current_frame.width = 60;
					current_frame.top = 350;
				}
			}
			else
			{
				if (Shot_timer.getElapsedTime().asSeconds() <= 0.5f)
				{
					if (count_anim == 1) { current_frame.left = 60; count_anim++; }

					current_frame.left += 60;
					
					current_frame.width = -60;
					current_frame.top = 350;
				}
				else
				{
					current_frame.left += 60;
					
					current_frame.width = -60;
					current_frame.top = 350;
				}
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
				if (count_anim == 0) {
					current_frame.left = 0;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				if (count_anim == 0) {
					current_frame.left = 70;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 280.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
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
				if (count_anim == 0) {
					current_frame.left = 0;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				if (count_anim == 0) {
					current_frame.left = 70;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 280.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -60;
				current_frame.top = 0;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_RUN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				
				current_frame.left += 70;
				if (current_frame.left >= 210.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				
				current_frame.left += 70;
				if (current_frame.left >= 280.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -60;
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
				if (count_anim == 0) { current_frame.left = 0; count_anim++; }

				current_frame.left += 80;
				if (current_frame.left >= 320.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 80;
				current_frame.top = 122;
			}
			else
			{
				if (count_anim == 0) { current_frame.left = 80; count_anim++; }

				current_frame.left += 80;
				if (current_frame.left >= 400.f)
				{
					current_frame.left = 80.f;
				}
				current_frame.width = -80;
				current_frame.top = 122;
			}

			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_JUMPING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim == 0) {
					current_frame.left = 0;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 350.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 242;
			}
			else

			{
				if (count_anim == 0) {
					current_frame.left = 70;
					count_anim++;
				}
				current_frame.left += 70;
				if (current_frame.left >= 420.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -60;
				current_frame.top = 242;
			}
			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (attention_counter == 3)current_frame.left = 0.f;
				attention_counter--;
				current_frame.left += 70;

				if (current_frame.left >= 210.f)
				{
					current_frame.left = 0.f;
				}
				current_frame.top = 580;
				current_frame.width = 70;
			}
			else
			{
				if (attention_counter == 3)current_frame.left = 0.f;
				attention_counter--;
				current_frame.left += 70;

				if (current_frame.left >= 280.f)
				{
					current_frame.left = 70.f;
				}
				current_frame.top = 580;
				current_frame.width = -70;
			}


			Enemy_S.setTextureRect(current_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				count_anim++;
				if (count_anim<4) {
					if (count_anim == 0) {
						current_frame.left = 0;
						count_anim++;
					}
					else current_frame.left += 60;
					if (current_frame.left >= 180.f)
					{
						current_frame.left = 0.f;
					}
					current_frame.width = 60;
					current_frame.top = 458;
				}
			}
			else
			{
				count_anim++;
				if (count_anim < 4) {
					if (count_anim == 0) {
						current_frame.left = 60;
						count_anim++;
					}
					current_frame.left += 60;
					if (current_frame.left >= 240.f)
					{
						current_frame.left = 60.f;
					}
					current_frame.width = -60;
					current_frame.top = 458;
				}
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

void RedMutant::shot()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
	//player_->changeHP(-attack_-(rand()%10));
	player_info->changeHP(-attack_ - (rand() % 10));
}


void RedMutant::attack()
{
	//FloatRect en = get_global_bounds();
	//FloatRect pl = player_info->getGlobalBounds();
	//if (displacement.x != 0.f && en.intersects(pl) && !plStan())
	//{
	//	while(true)
	//	{
	//		sf::Vector2f tmp = calculateRandomPosition(get_global_bounds(), 10);
	//	//std::cout << tmp.x / 64 << " " << tmp.y / 64 << "\n";
	//	if (tmp.x / 64 == 0)tmp.x = 64;
	//	if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
	//	if (!sandbox->isBlock(tmp.y / 64, tmp.x / 64)) {
	//		set_position(tmp.x, tmp.y);
	//		break;
	//	}
	//	else set_position(get_position().x, get_position().y);
	//	}
	//	
	//}
	if (!sting())
	{
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
		displacement.x += 5 * moving * acceleration;
		//displacement.x += 10 * moving * acceleration;
	}


	if (!isPlayerInRadius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 128))
	{
		reset_attention();
		//float intersectionRadius = 50.0f;
		//teleportBehindPlayer(Enemy_S, sandbox->get_player_glob_bound(), intersectionRadius);
	}

	// displacement.x = 0;
}

//sf::Vector2f RedMutant::calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance)
//{
//	int maxAttempts = 1000000;
//
//	for (int i = 0; i < maxAttempts; ++i)
//	{
//		
//		int direction = (rand() % 2 == 0) ? -1 : 1;
//
//		float newX = playerBounds.left + direction * jumpDistance * sandbox->getSizeTexture();
//		float newY = playerBounds.top;
//
//		if (newX >= 0 && newX < sandbox->getMapWidth() && newY >= 0 && newY < sandbox->getMapHeight())
//		{
//			if (!sandbox->isBlock(newY / sandbox->getSizeTexture(), newX / sandbox->getSizeTexture()))
//			{
//				return sf::Vector2f(newX, newY);
//			}
//		}
//		newY -= sandbox->getSizeTexture();
//		if (newX >= 0 && newX < sandbox->getMapWidth() && newY >= 0 && newY < sandbox->getMapHeight())
//		{
//			if (!sandbox->isBlock(newY / sandbox->getSizeTexture(), newX / sandbox->getSizeTexture()))
//			{
//				return sf::Vector2f(newX, newY);
//			}
//		}
//	}
//
//	return get_position();
//}
sf::Vector2f RedMutant::calculateRandomPosition(const sf::FloatRect& playerBounds, int jumpDistance)
{
	int x = static_cast<int>(get_position().x / sandbox->getSizeTexture());
	int y = static_cast<int>(get_position().y / sandbox->getSizeTexture());
	int count = 10000;
	int startDirection = (rand() % 2 == 0) ? 1 : -1;
	while (true)
	{
		for (int i = startDirection * jumpDistance; i != 0; i -= startDirection)
		{
			int newX = x + i;
			int newY = y;

			if (sandbox->outOfMap(newY + 1, newX) && sandbox->isBlock(newY + 1, newX))
			{
				newY += 1;
			}

			if (sandbox->outOfMap(newY, newX))
			{
				if (!sandbox->isBlock(newY, newX))
				{
					return sf::Vector2f(newX * sandbox->getSizeTexture(), newY * sandbox->getSizeTexture());
				}
			}
		}
		if (!count--)return get_position();
	}
}


void RedMutant::clear_shot()
{
}

bool RedMutant::search_for_enemies()
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
		for (int j = centerX + 1; j <= centerX + 15; j++)
		{
			if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
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
		for (int j = centerX - 15; j <= centerX; j++)
		{
			if (i >= 0 && i < sandbox->getMapHeight() / 64 && j >= 0 && j < sandbox->getMapWidth() / 64)
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

void RedMutant::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump = 0;
}

void RedMutant::changeHP(short i)
{
	if (red_mutant_state != RED_MUTANT_STATE::RED_MUTANT_TELEPORT)Enemy::changeHP(i);
}

bool RedMutant::plStan()
{
	if (player_info->getVelocity().x != 0.f)return false;
	else return true;
}
