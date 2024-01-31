#include "stdafx.h"
#include "kusaka.h"

kusaka::kusaka(TileMap& map, GeneralInfo* player_info, const short regime)
	: Enemy(map, player_info,regime), player_info_(player_info)
{
	{
		kusaka::init_texture();
		kusaka::init_sprite();
		kusaka::set_at(20);
		kusaka::set_hp(1000);
		kusaka_state = KUSAKA_STATE::KUSAKA_SLEEP;
		hp_damage_i = HP;
		kusaka_state_past = kusaka_state;
		kusaka_taking_damage_timer.restart();
		idle_timer.restart();
		death_timer.restart();
		count_jm = 0;
		hp_bar->SET_ST_HP(HP);
	}
}

kusaka::kusaka(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	{
		kusaka::init_texture();
		kusaka::init_sprite();
		kusaka::set_at(20);
		kusaka::set_hp(1000);
		kusaka_state = KUSAKA_STATE::KUSAKA_SLEEP;
		hp_damage_i = HP;
		kusaka_state_past = kusaka_state;
		kusaka_taking_damage_timer.restart();
		idle_timer.restart();
		death_timer.restart();
		count_jm = 0;
		hp_bar->SET_ST_HP(HP);
	}
}


void kusaka::init_texture()
{
	if (!kusaka_t_.loadFromFile("Textures/Enemies/kusaka.png"))
	{
		std::cout << "Error -> Enemy_kusaka -> couldn't load enemy_kusaka texture" << '\n';
	}
}

void kusaka::init_sprite()
{
	current_area = IntRect(0, 0, 1280, 192);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(kusaka_t_);
	standard_frame = IntRect(0, 0, 90, 55);
	anim_area.setTextureRect(standard_frame);

	current_frame = IntRect(0, 0, 64, 55);
	Enemy_S.setTextureRect(current_frame);
}


void kusaka::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 281;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.05f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 90.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 70;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
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
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 70;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			animation_counter_think--;
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 140;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450)
				{
					standard_frame.left = 360.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 350;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_RUN)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 810)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 900)
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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.09f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 450)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 90;
				standard_frame.top = 208;
			}
			else
			{
				standard_frame.left += 90;
				if (standard_frame.left >= 540)
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
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
	player_info->changeHP(-attack_ - (rand() % 5));
}


void kusaka::attack()
{
	
	if (sting())
	{
		displacement.x = 0;
		displacement_max = 1.f;
		const FloatRect en = get_global_bounds();
		const FloatRect pl = player_info->getGlobalBounds();
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
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			shot();
			displacement.x = 0;
			displacement_max = 1.f;

			blow_timer.restart();
		}
	}
	else kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;
}

void kusaka::clear_shot()
{
	count_shot = 0;
}

bool kusaka::search_for_enemies()
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

void kusaka::reset_attention()
{
	displacement_max = 1.f;
	displacement.x += moving * acceleration;
	count_jump_ = 0;
}

void kusaka::reset_timer()
{
	if (kusaka_state_past != kusaka_state)
	{
		idle_timer.restart();
		death_timer.restart();
		kusaka_state_past = kusaka_state;
	}
}

void kusaka::update_movement()
{
	if (HP <= 0)kusaka_state = KUSAKA_STATE::KUSAKA_DEATH;
	if (hp_damage_i > HP && kusaka_state != KUSAKA_STATE::KUSAKA_DEATH)
	{
		kusaka_state = KUSAKA_STATE::KUSAKA_TAKING_DAMAGE;
	}
	switch (kusaka_state)
	{
	case KUSAKA_STATE::KUSAKA_IDLE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (search_for_enemies())
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_ATTACKING;
			}
			if(kusaka_state_past == KUSAKA_STATE::KUSAKA_JUMPING)
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_MOVING;
				break;
			}
			reset_timer();

			if (update_collision_x() && update_collision_x_jump())
			{
				jump_flag = true;
				kusaka_state = KUSAKA_STATE::KUSAKA_JUMPING;
				break;
			}
			if (idle_timer.getElapsedTime().asSeconds() >= 1.5f)
			{
				
				 if (hit_a_wall())
				{
					kusaka_state = KUSAKA_STATE::KUSAKA_MOVING;
					moving *= -1.f;
					animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
				}
				else
				{
					kusaka_state = KUSAKA_STATE::KUSAKA_MOVING;
				}
				if (rand() % 2 && !search_for_enemies())kusaka_state = KUSAKA_STATE::KUSAKA_SLEEP;


				idle_timer.restart();
			}
			else
			{
				displacement.x = 0;
				displacement_max = 1.f;
			}

			break;
		}
	case KUSAKA_STATE::KUSAKA_JUMPING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
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

			else if (!can_jump_forward() || count_jm > 4)
			{
				count_jm = 0;
				jump_flag = false;
				kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;
				displacement_max = 1.f;
			}
			if (search_for_enemies())kusaka_state = KUSAKA_STATE::KUSAKA_ATTACKING;

			walk(moving);


			break;
		}
	case KUSAKA_STATE::KUSAKA_MOVING:
		{
			kusaka_state_past = kusaka_state;
			if (search_for_enemies())
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_ATTACKING;
				reset_timer();
				break;
			}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			if (update_collision_x())
			{
				if (can_jump_forward())
				{
					jump_flag = true;
					kusaka_state = KUSAKA_STATE::KUSAKA_JUMPING;
				}
				else moving *= -1.f;
			}
			if (rand() % 10 > 5)kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;
			walk(moving);
			break;
		}
	case KUSAKA_STATE::KUSAKA_ATTACKING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
			kusaka_state_past = kusaka_state;
			if (search_for_enemies())
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_RUN;
			}
			if (is_player_in_radius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 192))
			{
				if (count_jump_ == 0)
				{
					jump_towards_player();
					count_jump_++;
					kusaka_state = KUSAKA_STATE::KUSAKA_JUMPING;
				}
			}
			else reset_attention();
			if (sting())
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_SHOT;
			}
			if (update_collision_x())
			{
				if (can_jump_forward())
				{
					jump_flag = true;
					kusaka_state = KUSAKA_STATE::KUSAKA_JUMPING;
				}
				else moving *= -1.f;
			}

			walk(moving);
			break;
		}
	case KUSAKA_STATE::KUSAKA_SHOT:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			if (search_for_enemies() && (on_ground))
			{
				attack();
			}
			else
			{
				reset_attention();
				clear_shot();

				kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;
			}
			walk(moving);
			break;
		}

	case KUSAKA_STATE::KUSAKA_DEATH:
		{

			kusaka_state_past = kusaka_state;
			displacement.x = 0;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			break;
		}
	case KUSAKA_STATE::KUSAKA_TAKING_DAMAGE:
		{
			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			if (HP <= 0)
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				kusaka_taking_damage_timer.restart();
				hp_damage_i = HP;
			}
			if (kusaka_taking_damage_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;
			}

			break;
		}
	case KUSAKA_STATE::KUSAKA_RUN:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
			if (search_for_enemies())
			{
				if (jump_tile || !on_ground)displacement_max = 1.f;
				else displacement_max = 5.f;
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
			else kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;

			walk(moving);
			kusaka_state = KUSAKA_STATE::KUSAKA_ATTACKING;
			break;
		}

	case KUSAKA_STATE::KUSAKA_SLEEP:
		{

			kusaka_state_past = kusaka_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
			displacement.x = 0.f;
			if (search_for_enemies()) kusaka_state = KUSAKA_STATE::KUSAKA_IDLE;

			break;
		}

	default:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
			kusaka_state = KUSAKA_STATE::KUSAKA_SLEEP;
			break;
		}
	}
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

	if (on_ground && kusaka_state != KUSAKA_STATE::KUSAKA_IDLE && kusaka_state != KUSAKA_STATE::KUSAKA_TAKING_DAMAGE &&
		kusaka_state != KUSAKA_STATE::KUSAKA_DEATH
		&& kusaka_state != KUSAKA_STATE::KUSAKA_SLEEP && kusaka_state != KUSAKA_STATE::KUSAKA_SHOT)
	{
		displacement.x += dir_x * acceleration;
	}

	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
}

bool kusaka::update_collision_move_x()
{
	const int block_size = 64;
	int total_pixels = 0;
	int collided_pixels = 0;

	const sf::Vector2f start_position = get_position();
	const sf::Vector2f new_position = start_position;

	for (float y = Enemy_S.getPosition().y; y < Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height; y++)
	{
		for (float x = Enemy_S.getPosition().x; x < Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width; x++)
		{
			const int i = static_cast<int>(y / block_size);
			const int j = static_cast<int>(x / block_size);
			++total_pixels;
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				++collided_pixels;
			}
		}
	}

	set_position(new_position.x, new_position.y);

	return (collided_pixels > total_pixels * 0.2);
}
