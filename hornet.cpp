#include "stdafx.h"
#include "hornet.h"

void hornet::init_texture()
{
	if (!hornet_t_.loadFromFile("Textures/Enemies/hornet.png"))
	{
		std::cout << "Error -> hornet -> couldn't load hornet texture" << '\n';
	}
}

void hornet::init_sprite()
{
	current_area = IntRect(0, 0, 2000, 400);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(hornet_t_);
	standard_frame = IntRect(0, 0, 64, 76);
	anim_area.setTextureRect(standard_frame);


	//Enemy_S.setTexture(Wolf_Boss_t_);
	current_frame = IntRect(0, 0, 30, 30);
	Enemy_S.setTextureRect(current_frame);
}

hornet::hornet(TileMap& map, GeneralInfo* player_info, const short regime): Enemy(map, player_info, regime),
                                                                            player_info_(player_info)
{
	hornet::init_texture();
	hornet::init_sprite();
	hornet::set_at(20);
	hornet::set_hp(50);
	hp_damage_i = HP;
	hornet_state = HORNET_STATE::IDLE;
	hornet_state_past_ = HORNET_STATE::FLYING;
	idle_timer_.restart();
	attacking_timer_.restart();
	death_timer.restart();
	hp_bar->SET_ST_HP(HP);
}

hornet::hornet(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y):
Enemy(map, player_info_,pos_x,pos_y ), player_info_(player_info)
{
	hornet::init_texture();
	hornet::init_sprite();
	hornet::set_at(20);
	hornet::set_hp(50);
	hp_damage_i = HP;
	hornet_state = HORNET_STATE::IDLE;
	hornet_state_past_ = HORNET_STATE::FLYING;
	idle_timer_.restart();
	attacking_timer_.restart();
	death_timer.restart();
	hp_bar->SET_ST_HP(HP);
}

void hornet::update_movement()
{
	if (HP <= 0)
	{
		hornet_state = HORNET_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP && hornet_state != HORNET_STATE::DEATH)
	{
		hornet_state = HORNET_STATE::TAKING_DAMAGE;
	}


	switch (hornet_state)
	{
	case HORNET_STATE::IDLE:
		{
			hornet_state_past_ = hornet_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			looks();
			if (death_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				direction_calculation();
				hornet_state = HORNET_STATE::FLYING;
				death_timer.restart();
			}

			break;
		}


	case HORNET_STATE::FLYING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			looks();
			hornet_state_past_ = hornet_state;

			if (sting())
			{
				hornet_state = HORNET_STATE::ATTACKING;
			}
			if (idle_timer_.getElapsedTime().asSeconds() >= 2.F)
			{
				hornet_state = HORNET_STATE::IDLE;
				idle_timer_.restart();
			}
			walk(moving);
			break;
		}

	case HORNET_STATE::ATTACKING:
		{
			looks();
			displacement.x = 0.f;
			displacement.y = 0.f;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_PUNCH;
			reset_Timer();
			attack();

			if (idle_timer_.getElapsedTime().asSeconds() >= 0.8f)
			{
				hornet_state = HORNET_STATE::FLYING;
			}


			//walk(moving);
			break;
		}


	case HORNET_STATE::TAKING_DAMAGE:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			reset_Timer();
			looks();
			displacement.x = 0.f;
			displacement.y = 0.f;
			if (HP <= 0)
			{
				hp_damage_i = HP;
				hornet_state = HORNET_STATE::DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				hornet_taking_damage_timer_.restart();
				hp_damage_i = HP;
			}
			if (hornet_taking_damage_timer_.getElapsedTime().asSeconds() >= 1.0f)
			{
				hornet_state = HORNET_STATE::IDLE;
			}

			break;
		}


	case HORNET_STATE::DEATH:
		{


			reset_Timer();

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;

			walk(moving);
			break;
		}
	}
}

void hornet::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.03f || get_animation_switch())
		{
			standard_frame.top = 0.f;
			if (looks_to_the_left)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 512)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = 64.f;
			}
			else
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 576)
				{
					standard_frame.left = 128.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.03f || get_animation_switch())
		{
			standard_frame.top = 0.f;
			if (looks_to_the_left)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 512)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = 64.f;
			}
			else
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 576)
				{
					standard_frame.left = 128.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_PUNCH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.07f || get_animation_switch())
		{
			standard_frame.top = 76.f;

			if (looks_to_the_left)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 256)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 320)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 228.f;

			if (looks_to_the_left)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 704)
				{
					standard_frame.left = 576.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 768)
				{
					standard_frame.left = 640.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 228.f;

			if (looks_to_the_left)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 384)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 448)
				{
					standard_frame.left = 128.f;
				}
				standard_frame.width = -64.f;
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

void hornet::shot()
{
	if (attacking_timer_.getElapsedTime().asSeconds() >= 0.5f)
	{
		player_info->changeHP(-attack_ - (rand() % 5));
		attacking_timer_.restart();
	}
}

bool hornet::search_for_enemies()
{
	const FloatRect look = observation_area.getGlobalBounds();
	const FloatRect pl = player_info->getGlobalBounds();

	PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (look.intersects(pl))
	{
		return true;
	}

	return false;
}

void hornet::walk(const float dir_x)
{
	displacement_max = 10.f;
	velocity_max_y = 10.f;
	acceleration = 0.5;
	direction_calculation();
	looks();
	if (looks_to_the_left)
	{
		displacement.x = acceleration * move_x_ * dir_x;
		displacement.y = acceleration * move_y_ * dir_x;
	}
	else
	{
		displacement.x = acceleration * move_x_ * (-dir_x);
		displacement.y = acceleration * move_y_ * (-dir_x);
	}
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	if (std::abs(displacement.y) > velocity_max_y)
	{
		displacement.y = velocity_max_y * ((displacement.y > 0.f) ? 1.f : -1.f);
	}
}

void hornet::reset_Timer()
{
	if (hornet_state_past_ != hornet_state)
	{
		death_timer.restart();
		blow_timer.restart();
		hornet_state_past_ = hornet_state;
	}
	if (animation_state_past != animation_state)
	{
		if (looks_to_the_right)
		{
			standard_frame.left = 0.f;
			animation_timer.restart();
		}
		else
		{
			standard_frame.left = 64.f;
			animation_timer.restart();
		}
		animation_state_past = animation_state;
	}
}

void hornet::changeHP(const short i)
{
	if (hornet_state != HORNET_STATE::TAKING_DAMAGE)Enemy::changeHP(i);
}

void hornet::update_physics()


{
	if (hornet_state == HORNET_STATE::DEATH)
	{
		displacement.y += 1.f * gravity;
	}



	if (update_collision_x() || hornet_state == HORNET_STATE::DEATH || sting())
	{
		displacement.x = 0.f;
	}
	if (update_collision_y() || sting())
	{
		displacement.y = 0.f;
	}
	Enemy_S.move(displacement);
	set_position(get_position().x, get_position().y);
}

void hornet::looks()
{
	const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (player_side == PL_SIDE::LEFT)
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

void hornet::direction_calculation()
{
	const float target_x = get_position().x;
	const float target_y = get_position().y;

	const float start_x = player_info_->getPosition().x;
	const float start_y = player_info_->getPosition().y;

	const float direction_x = target_x - start_x;
	const float direction_y = target_y - start_y;

	const float length = std::sqrt(direction_x * direction_x + direction_y * direction_y);

	if (length != 0.0f)
	{
		const float normalized_direction_x = direction_x / length;
		const float normalized_direction_y = direction_y / length;


		move_x_ = normalized_direction_x;
		move_y_ = normalized_direction_y;
	}
}

void hornet::attack()
{
	shot();
}

void hornet::clear_shot()
{
}

void hornet::reset_attention()
{
}
