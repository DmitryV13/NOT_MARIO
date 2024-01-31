#include "stdafx.h"
#include "RedMutant.h"

RedMutant::RedMutant(TileMap& map, GeneralInfo* player_info, const short regime)
	: Enemy(map, player_info,regime), player_info_(player_info)
{
	{
		RedMutant::init_texture();
		RedMutant::init_sprite();
		RedMutant::set_at(25);
		RedMutant::set_hp(2000);
		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
		hp_damage_i = HP;
		red_mutant_state_past = red_mutant_state;
		red_mutant_taking_damage_timer_.restart();
		idle_timer_.restart();
		DEATH_timer.restart();
		shot_timer_.restart();
		count_jm_ = 0;
		hp_bar->SET_ST_HP(HP);
	}
}
void RedMutant::updateHP_bar()
{
	hp_bar->update(Enemy_S);

}
RedMutant::RedMutant(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	{
		RedMutant::init_texture();
		RedMutant::init_sprite();
		RedMutant::set_at(25);
		RedMutant::set_hp(2000);
		red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
		hp_damage_i = HP;
		red_mutant_state_past = red_mutant_state;
		red_mutant_taking_damage_timer_.restart();
		idle_timer_.restart();
		DEATH_timer.restart();
		shot_timer_.restart();
		count_jm_ = 0;
		hp_bar->SET_ST_HP(HP);
	}
}

void RedMutant::init_texture()
{
	if (!chubacabra_t_.loadFromFile("Textures/Enemies/RedMutant.png"))
	{
		std::cout << "Error -> Enemy_chupacabra -> couldn't load enemy_chupacabra texture" << '\n';
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

void RedMutant::reset_timer()
{
	if (red_mutant_state_past != red_mutant_state)
	{
		count_anim_ = 0;
		idle_timer_.restart();
		DEATH_timer.restart();
		blow_timer.restart();
		shot_timer_.restart();
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
	if (sting() && !pl_stan() && displacement.x != 0.f)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
	switch (red_mutant_state)
	{
	case RED_MUTANT_STATE::RED_MUTANT_IDLE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (search_for_enemies())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;
			}
			reset_timer();
			if (update_collision_x())
			{
				if (can_jump_forward())
				{
					jump_flag_ = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}
			if (idle_timer_.getElapsedTime().asSeconds() >= 0.5f)
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


				idle_timer_.restart();
			}
			else
			{
				displacement.x = 0;
				displacement_max = 1.f;
			}
			walk(moving);
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_JUMPING:
		{
			reset_timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
			
			if (on_ground && jump_flag_)
			{
				jump(1.2f);
				on_ground = false;
				jump_tile = true;
				count_jm_++;
			}

			else if (!can_jump_forward() || count_jm_ > 2)
			{
				count_jm_ = 0;
				jump_flag_ = false;
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			}
			if (search_for_enemies())red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_ATTACKING;

			walk(moving);


			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_MOVING:
		{
			reset_timer();
			
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
				if (can_jump_forward())
				{
					jump_flag_ = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}
			if (rand() % 10 > 5)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			if (!sting())walk(moving);
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_ATTACKING:
		{	reset_timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
			
			if (sting() && displacement.x != 0.f)red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
			if (search_for_enemies())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_RUN;
			}
			else red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			
			if (sting())
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_SHOT;
			}
			if (update_collision_x())
			{
				if (can_jump_forward())
				{
					jump_flag_ = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_JUMPING;
				}
				else moving *= -1.f;
			}

			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_SHOT:
		{
			FloatRect en = get_global_bounds();
			FloatRect pl = player_info->getGlobalBounds();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			reset_timer();

			if (blow_timer.getElapsedTime().asSeconds() >= 0.2f)
			{
				shot();
				blow_timer.restart();
			}
			if (shot_timer_.getElapsedTime().asSeconds() >= 0.5f)
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_TELEPORT;
				if (looks_to_the_left)current_frame.width = 60;
				else current_frame.width = 0;
				Enemy_S.setTextureRect(current_frame);
				shot_timer_.restart();
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

			reset_timer();
			displacement.x = 0;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_TAKING_DAMAGE:
		{
		reset_timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			if (HP <= 0 )
			{
				hp_damage_i = HP;
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				red_mutant_taking_damage_timer_.restart();
				hp_damage_i = HP;
				
			}
			if (red_mutant_taking_damage_timer_.getElapsedTime().asSeconds() >= 0.3f)
			{
				red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			}

			break;
		}
	case RED_MUTANT_STATE::RED_MUTANT_RUN:
		{
			
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
			if (search_for_enemies())
			{
				if (jump_tile || !on_ground)displacement_max = 1.f;
				else displacement_max = 1.f;
				if (player_l_r_[0] && displacement.x > 0)
				{
					displacement.x = 0;
					moving = -1.f;
					looks_to_the_right = false;
					looks_to_the_left = true;
				}
				else if (player_l_r_[0] && displacement.x < 0)
				{
					displacement.x = 0;
					looks_to_the_right = false;
					looks_to_the_left = true;
				}
				else if (player_l_r_[1] && displacement.x > 0)
				{
					displacement.x = 0;
					looks_to_the_right = true;
					looks_to_the_left = false;
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
			reset_timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TELEPORT;
			if (shot_timer_.getElapsedTime().asSeconds() >= 0.3f)
			{
				if (teleport_)
					while (true)
					{
						teleport_ = false;
						sf::Vector2f tmp = calculate_random_position(get_global_bounds(), 10);
						if (tmp.x / 64 == 0)tmp.x = 64;
						if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
						if (!sandbox->isBlock(tmp.y / 64, tmp.x / 64))
						{
							set_position(tmp.x, tmp.y);
							break;
						}
						else set_position(get_position().x, get_position().y);
					}
				if (shot_timer_.getElapsedTime().asSeconds() >= 0.7f)
				{
					teleport_ = true;
					red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;

					shot_timer_.restart();
				}
			}

			displacement.x = 0.f;
			break;
		}

	default:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			red_mutant_state = RED_MUTANT_STATE::RED_MUTANT_IDLE;
			break;
		}
	}

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
	if (on_ground)
	{
		displacement.x += dir_x * acceleration;
	}

	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	if (sting())displacement.x = 0.f;
	
}

void RedMutant::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
					current_frame.left += 60;
					if (current_frame.left >= 180)
					{
						current_frame.left = 0.f;
					}
					current_frame.width = 60;
					current_frame.top = 0;
				
			}
			else
			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 240)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TELEPORT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (shot_timer_.getElapsedTime().asSeconds() <= 0.5f)
				{

					if (count_anim_ == 1) { current_frame.left = 0; count_anim_++; }

					current_frame.left += 60;
					current_frame.width = 60;
					current_frame.top = 350;
				}
				else
				{
					current_frame.left += 60;
					if (current_frame.left >= 420)
					{
						current_frame.left = 0.f;
					}
					current_frame.width = 60;
					current_frame.top = 350;
				}
			}
			else
			{
				if (shot_timer_.getElapsedTime().asSeconds() <= 0.5f)
				{
					if (count_anim_ == 1) { current_frame.left = 60; count_anim_++; }

					current_frame.left += 60;
					
					current_frame.width = -60;
					current_frame.top = 350;
				}
				else
				{
					current_frame.left += 60;
					if (current_frame.left >= 480)
					{
						current_frame.left = 60.f;
					}
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
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 180)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;

			}
			else
			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 240)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 180)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;

			}
			else
			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 240)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_RUN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 180)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;

			}
			else
			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 240)
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

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				if (count_anim_ == 0) { current_frame.left = 0; count_anim_++; }

				else current_frame.left += 70;
				if (current_frame.left >= 280)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 70;
				current_frame.top = 122;
			}
			else
			{
				if (count_anim_ == 0) { current_frame.left =70; count_anim_++; }
				else current_frame.left += 70;
				if (current_frame.left >= 350)
				{
					current_frame.left = 70.f;
				}
				current_frame.width = -70;
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
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 300)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 242;
			}
			else

			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;
				if (current_frame.left >= 360)
				{
					current_frame.left = 60.f;
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
				
				current_frame.left += 60;

				if (current_frame.left >= 180)
				{
					current_frame.left = 0.f;
				}
				current_frame.top = 580;
				current_frame.width = 60;
			}
			else
			{
				current_frame.left += 60;

				if (current_frame.left >= 240)
				{
					current_frame.left = 60.f;
				}
				current_frame.top = 580;
				current_frame.width = -60;
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
				if (count_anim_ == 0) {
					current_frame.left = 0;
					count_anim_++;
				}
				current_frame.left += 60;

				if (current_frame.left >= 240)
				{
					current_frame.left = 180.f;
				}
				current_frame.top = 457;
				current_frame.width = 60;
			}
			else
			{
				if (count_anim_ == 0) {
					current_frame.left = 60;
					count_anim_++;
				}
				current_frame.left += 60;

				if (current_frame.left >= 300)
				{
					current_frame.left = 240.f;
				}
				current_frame.top = 457;
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

void RedMutant::shot()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
	player_info->changeHP(-attack_ - (rand() % 10));
}


void RedMutant::attack()
{
	
	if (!sting())
	{
		if (player_l_r_[0] && displacement.x > 0)
		{
			displacement.x = 0;
			moving = -1.f;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r_[0] && displacement.x < 0)
		{
			displacement.x = 0;
			looks_to_the_right = false;
			looks_to_the_left = true;
		}
		else if (player_l_r_[1] && displacement.x > 0)
		{
			displacement.x = 0;
			looks_to_the_right = true;
			looks_to_the_left = false;
		}
		else
		{
			displacement.x = 0;
			moving = 1.f;
			looks_to_the_right = true;
			looks_to_the_left = false;
		}
		displacement.x += 5 * moving * acceleration;
	}


	if (!is_player_in_radius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 128))
	{
		reset_attention();
	}

}

sf::Vector2f RedMutant::calculate_random_position(const sf::FloatRect& playerBounds, int jumpDistance) const
{
	const int x = static_cast<int>(get_position().x / sandbox->getSizeTexture());
	const int y = static_cast<int>(get_position().y / sandbox->getSizeTexture());
	int count = 1000000;
	int start_direction = (rand() % 2 == 0) ? 1 : -1;

	
	int sprite_size_in_blocks_x = static_cast<int>(Enemy_S.getGlobalBounds().width / sandbox->getSizeTexture());
	int sprite_size_in_blocks_y = static_cast<int>(Enemy_S.getGlobalBounds().height / sandbox->getSizeTexture());

	while (count--)
	{
		const int random_x_offset = rand() % (2 * jumpDistance + 1) - jumpDistance;
		const int random_y_offset = rand() % (2 * jumpDistance + 1) - jumpDistance;

		const int new_x = x + random_x_offset;
		const int new_y = y + random_y_offset;

		
		if (!sandbox->outOfMap(new_y, new_x))
			continue;

		
		if (sandbox->isBlock(new_y, new_x))
			continue;

		
		if (sandbox->outOfMap(new_y + 2, new_x) && !sandbox->isBlock(new_y + 2, new_x))
			continue;
		if (sandbox->outOfMap(new_y+1, new_x) && sandbox->isBlock(new_y + 1, new_x) )
			continue;
		return {new_x * sandbox->getSizeTexture(), new_y * sandbox->getSizeTexture()};
	}

	return get_position(); 
}





void RedMutant::clear_shot()
{
}

bool RedMutant::search_for_enemies()
{
	const FloatRect look = observation_area.getGlobalBounds();
	const FloatRect pl = player_info->getGlobalBounds();

	const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (player_side == PL_SIDE::RIGHT && look.intersects(pl))
	{
		player_l_r_[1] = true;
		player_l_r_[0] = false;
		return true;
	}
	else if (player_side == PL_SIDE::LEFT && look.intersects(pl))
	{
		
		player_l_r_[0] = true;
		player_l_r_[1] = false;
		return true;
	}

	player_l_r_[0] = false;
	player_l_r_[1] = false;
	return false;

}

void RedMutant::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump_ = 0;
}

void RedMutant::changeHP(const short i)
{
	if (red_mutant_state != RED_MUTANT_STATE::RED_MUTANT_TELEPORT)Enemy::changeHP(i);
}

bool RedMutant::pl_stan() const
{
	if (player_info->getVelocity().x != 0.f)return false;
	else return true;
}
