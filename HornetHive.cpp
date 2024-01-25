#include "stdafx.h"
#include "HornetHive.h"


void HornetHive::init_texture()
{
	if (!HornetHive_t_.loadFromFile("Textures/Enemies/beehive.png"))
	{
		std::cout << "Error -> beehive -> couldn't load beehive texture" << std::endl;
	}
}

void HornetHive::init_sprite()
{
	current_area = IntRect(0, 0, 2000, 400);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(HornetHive_t_);
	standard_frame = IntRect(0, 0, 64,64);
	anim_area.setTextureRect(standard_frame);


	//Enemy_S.setTexture(Wolf_Boss_t_);
	current_frame = IntRect(0,0, 64, 50);
	Enemy_S.setTextureRect(current_frame);
}


HornetHive::HornetHive(TileMap& map, GeneralInfo* player_info,short regime):Enemy(map, player_info,regime), player_info_(player_info)
{
	HornetHive::init_texture();
	HornetHive::init_sprite();
	HornetHive::setAt(0);
	HornetHive::setHP(30);
	hp_damage_i = HP;
	hornet_state = HORNET_HIVE_STATE::IDLE;
	hornet_hive_state_past = HORNET_HIVE_STATE::TAKING_DAMAGE;
	DEATH_timer.restart();
	hp_bar->SET_ST_HP(HP);
}

HornetHive::HornetHive(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	HornetHive::init_texture();
	HornetHive::init_sprite();
	HornetHive::setAt(0);
	HornetHive::setHP(30);
	hp_damage_i = HP;
	hornet_state = HORNET_HIVE_STATE::IDLE;
	hornet_hive_state_past = HORNET_HIVE_STATE::TAKING_DAMAGE;
	DEATH_timer.restart();
	hp_bar->SET_ST_HP(HP);
}
void HornetHive::update_movement()
{


	set_position_AR(get_position().x, get_position().y);
	if (HP <= 0)
	{
		hornet_state = HORNET_HIVE_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP && hornet_state != HORNET_HIVE_STATE::DEATH)
	{
		hornet_state = HORNET_HIVE_STATE::TAKING_DAMAGE;
	}
	clear_shot();


	switch (hornet_state)
	{

	case HORNET_HIVE_STATE::IDLE:
	{
		std::cout << "IDLE\n";

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;

		break;
	}

	case HORNET_HIVE_STATE::TAKING_DAMAGE:
	{
		std::cout << "TAKING_DAMAGE\n";

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
		reset_Timer();
		displacement.x = 0.f;
		displacement.y = 0.f;
		if (HP <= 0)
		{
			hp_damage_i = HP;
			hornet_state = HORNET_HIVE_STATE::DEATH;
			break;
		}
		if (hp_damage_i > HP)
		{
			HORNET_TAKING_DAMAGE_TIMER.restart();
			hp_damage_i = HP;
		}
		if (HORNET_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 1.0f)
		{
			hornet_state = HORNET_HIVE_STATE::IDLE;
		}

		break;
	}


	case HORNET_HIVE_STATE::DEATH:
	{
		std::cout << "DEATH\n";


		reset_Timer();

		animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;

		break;

	}
	}
}

void HornetHive::update_animation()
{

	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.03f || get_animation_switch())
		{
			standard_frame.top = 0.f;
			standard_frame.left = 0.f;
				standard_frame.width = 64.f;

			

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.3f || get_animation_switch())
		{
			standard_frame.top = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 256)
				{
					standard_frame.left = 192.f;
				}
				standard_frame.width = 64;
			
			

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 0.f;

			
			standard_frame.left += 64;
				if (standard_frame.left >= 256)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 64;
			

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}


	else
	{
		animation_timer.restart();
	}
}

void HornetHive::shot()
{
}

bool HornetHive::search_for_enemies()
{
	return false;
}


void HornetHive::reset_Timer()
{
	if (hornet_hive_state_past != hornet_state)
	{
		DEATH_timer.restart();
		hornet_hive_state_past = hornet_state;
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

void HornetHive::attack()
{
}

void HornetHive::clear_shot()
{
}

void HornetHive::reset_attention()
{
}

void HornetHive::changeHP(short i)
{
	if(hornet_state!=HORNET_HIVE_STATE::TAKING_DAMAGE && hornet_state!=HORNET_HIVE_STATE::DEATH)Enemy::changeHP(i);
}

void HornetHive::update_physics()
{
	// gravity
	displacement.y += 1.f * gravity;
	if (std::abs(displacement.y) > velocity_max_y)
	{
		displacement.y = velocity_max_y * ((displacement.y > 0.f) ? 1.f : -1.f);
	}
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}
	//jumping
	if (jump_tile)
	{
		displacement.y -= jump_velocity;
		//jumping onto a block
		displacement.x += moving * acceleration;
		//jump deceleratin
		jump_velocity *= 0.96;
	}
	// deceleration
	displacement *= deceleration;

	// limits
	if (jump_tile && search_for_enemies())
	{
		displacement.x = 2 * moving * displacement_max;
	}
	if (update_collision_x())
	{
		displacement.x = 0.f;
	}
	if (update_collision_y())
	{
		displacement.y = 0.f;
	}
	//step counter
	if (displacement.x > 0 && displacement_max == 1.f)
		step_right++;
	if (displacement.x < 0 && displacement_max == 1.f)
		step_left++;
	//if (player_contact())displacement.x *= 1.3f;

	Enemy_S.move(displacement);
	observation_area.move(displacement);
	set_position_AR(get_position().x, get_position().y);
}

bool HornetHive::HIVE_LIFE() const
{
	return HP >= 1;
}

void HornetHive::set_position_AR(const float x, const float y)
{
	observation_area.setPosition(
		x - (observation_area.getGlobalBounds().width - (observation_area.getGlobalBounds().width / 2) - (Enemy_S.
			getGlobalBounds().width / 2)),
		(y - (observation_area.getGlobalBounds().height - Enemy_S.getGlobalBounds().height)));

	anim_area.setPosition(
		x - (anim_area.getGlobalBounds().width - (anim_area.getGlobalBounds().width / 2) - (Enemy_S.
			getGlobalBounds().width / 2)),
		(y - (anim_area.getGlobalBounds().height - Enemy_S.getGlobalBounds().height-4)));

	Enemy_S.setPosition(x, y);
}



