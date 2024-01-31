#include "stdafx.h"
#include "EyeEvil.h"


EyeEvil::EyeEvil(TileMap& map, GeneralInfo* player_info, const short regime)
	: Enemy(map, player_info,regime), player_info(player_info)
{
	{
		EyeEvil::init_texture();
		EyeEvil::init_sprite();
		EyeEvil::set_at(20);
		EyeEvil::set_hp(1000);
		hp_damage_i = HP;
		eye_state = eye_state_past = EYE_EVIL_STATE::IDLE;
		idle_timer.restart();
		attacking_timer.restart();
		death_timer.restart();
		hp_bar->SET_ST_HP(HP);
	}
}
EyeEvil::EyeEvil(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	{
		EyeEvil::init_texture();
		EyeEvil::init_sprite();
		EyeEvil::set_at(20);
		EyeEvil::set_hp(1000);
		hp_damage_i = HP;
		eye_state = eye_state_past = EYE_EVIL_STATE::IDLE;
		idle_timer.restart();
		attacking_timer.restart();
		death_timer.restart();
		hp_bar->SET_ST_HP(HP);
	}
}


void EyeEvil::init_texture()
{
	if (!Enemy_T.loadFromFile("Textures/Enemies/eye.png"))
	{
		std::cout << "Error -> Enemy -> couldn't load enemy texture" << '\n';
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

void EyeEvil::reset_timer()
{
	if (eye_state_past != eye_state)
	{
		idle_timer.restart();
		death_timer.restart();
		attacking_timer.restart();
		eye_state_past = eye_state;
	}
}

void EyeEvil::changeHP(const short i)
{
	if(eye_state != EYE_EVIL_STATE::TAKING_DAMAGE && eye_state != EYE_EVIL_STATE::DEATH)Enemy::changeHP(i);
}

void EyeEvil::updateHP_bar()
{
	hp_bar->update(Enemy_S);

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
			if (search_for_enemies() && attacking_timer.getElapsedTime().asSeconds() >= 6.1f)
				eye_state =
					EYE_EVIL_STATE::ATTACKING;
			reset_timer();
			if (hit_a_wall() && update_collision_x_jump())
				{
					jump_flag = true;
					eye_state = EYE_EVIL_STATE::JUMPING;
				break;
				}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			if (idle_timer.getElapsedTime().asSeconds() >= 1.5f)
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
			break;
		}
	case EYE_EVIL_STATE::JUMPING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
			eye_state_past = eye_state;
			if (on_ground && jump_flag)
			{
				jump(1.2f);
				on_ground = false;
				jump_tile = true;
			}
			else if (!can_jump_forward() || can_move_forward())
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
				reset_timer();
			}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			if (hit_a_wall())
			{
				if (can_jump_forward())
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


			if (search_for_enemies() && attacking_timer.getElapsedTime().asSeconds() <= 5.1f)
			{
				attack();
			}
			else
			{
				reset_attention();
				clear_shot();
				reset_timer();
				eye_state = EYE_EVIL_STATE::IDLE;
			}
			break;
		}
	case EYE_EVIL_STATE::DEATH:
		{
			displacement.x = 0;
			reset_timer();
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

	default:    // NOLINT(clang-diagnostic-covered-switch-default)
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			eye_state = EYE_EVIL_STATE::IDLE;
		}
	}

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


}

void EyeEvil::walk(const float dir_x)
{
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
				if (current_frame.left >= 360)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 0;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420)
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
				if (current_frame.left >= 360)
				{
					current_frame.left = 0.f;
				}
				current_frame.width = 60;
				current_frame.top = 180;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420)
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
				if (current_frame.left >= 360)
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
				if (current_frame.left >= 420)
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
				if (current_frame.left >= 420)
				{
					current_frame.left = 60.f;
				}
				current_frame.width = -60;
				current_frame.top = 60;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 360)
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
				if (current_frame.left >= 360)
				{
					current_frame.left = 180.f;
				}
				current_frame.width = 60;
				current_frame.top = 60;
			}
			else
			{
				current_frame.left += 60;
				if (current_frame.left >= 420)
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

				if (current_frame.left >= 360)
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

				if (current_frame.left >= 420)
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

				if (current_frame.left >= 300)
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

				if (current_frame.left >= 360)
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
		laser_fl = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y,
		                           looks_to_the_right, player_info);
		laser = new laser_weapon(*sandbox, 2, Enemy_S.getPosition().x + 64, Enemy_S.getPosition().y,
		                         looks_to_the_right, player_info);

	}
	else
	{
		laser_fl = new laser_weapon(*sandbox, 1, Enemy_S.getPosition().x, Enemy_S.getPosition().y,
		                           looks_to_the_right, player_info);
		laser = new laser_weapon(*sandbox, 2, Enemy_S.getPosition().x - 64, Enemy_S.getPosition().y,
		                         looks_to_the_right, player_info);
		
	}
}


void EyeEvil::attack()
{
	const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
	if ((player_side == PL_SIDE::LEFT && looks_to_the_left) || (player_side == PL_SIDE::RIGHT && looks_to_the_right))
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
			laser_fl->update();
		}
		displacement.x = 0;
	}
	else clear_shot();
}

void EyeEvil::clear_shot()
{
	delete laser;
	delete laser_fl;
	laser_fl = nullptr;
	laser = nullptr;
}

bool EyeEvil::laser_existence() const
{
	if (laser_fl == nullptr)return false;
	else return true;
}

void EyeEvil::draw_laser(int i, sf::RenderTarget& target) const
{
	if (HP >= 0)laser_fl->render_fl(target);
	if (HP >= 0)laser->render(target);
}

void EyeEvil::reset_attention()
{
	attention_counter = 3;
}


bool EyeEvil::search_for_enemies()
{
	const FloatRect en = observation_area.getGlobalBounds();
	const FloatRect pl = player_info->getGlobalBounds();
	const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (player_side == PL_SIDE::RIGHT && looks_to_the_right)
	{
		return en.intersects(pl);
	}
	else if (player_side == PL_SIDE::LEFT && looks_to_the_left)
	{
		return en.intersects(pl);
	}
	return false;
}
