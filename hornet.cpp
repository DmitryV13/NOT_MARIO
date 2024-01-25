#include "stdafx.h"
#include "hornet.h"

void hornet::init_texture()
{
	if (!hornet_t_.loadFromFile("Textures/Enemies/hornet.png"))
	{
		std::cout << "Error -> hornet -> couldn't load hornet texture" << std::endl;
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

hornet::hornet(TileMap& map, GeneralInfo* player_info,short regime): Enemy(map, player_info,regime), player_info_(player_info)
{
	hornet::init_texture();
	hornet::init_sprite();
	hornet::setAt(20);
	hornet::setHP(50);
	hp_damage_i = HP;
	hornet_state = HORNET_STATE::IDLE;
	hornet_state_past = HORNET_STATE::FLYING;
	IDLE_timer.restart();
	ATTACKING_timer.restart();
	DEATH_timer.restart();
}

hornet::hornet(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y):
Enemy(map, player_info_,pos_x,pos_y ), player_info_(player_info)
{
	hornet::init_texture();
	hornet::init_sprite();
	hornet::setAt(20);
	hornet::setHP(50);
	hp_damage_i = HP;
	hornet_state = HORNET_STATE::IDLE;
	hornet_state_past = HORNET_STATE::FLYING;
	IDLE_timer.restart();
	ATTACKING_timer.restart();
	DEATH_timer.restart();
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
			hornet_state_past = hornet_state;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			looks();
			if (DEATH_timer.getElapsedTime().asSeconds() >= 0.5f)
			{
				direction_calculation();
				hornet_state = HORNET_STATE::FLYING;
				DEATH_timer.restart();
			}

			break;
		}


	case HORNET_STATE::FLYING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			looks();
			hornet_state_past = hornet_state;

			if (sting())
			{
				hornet_state = HORNET_STATE::ATTACKING;
			}
			if (IDLE_timer.getElapsedTime().asSeconds() >= 2.F)
			{
				hornet_state = HORNET_STATE::IDLE;
				IDLE_timer.restart();
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

			if (IDLE_timer.getElapsedTime().asSeconds() >= 0.8f)
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
				HORNET_TAKING_DAMAGE_TIMER.restart();
				hp_damage_i = HP;
			}
			if (HORNET_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 1.0f)
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
	if (ATTACKING_timer.getElapsedTime().asSeconds() >= 0.5f)
	{
		player_info->changeHP(-attack_ - (rand() % 5));
		ATTACKING_timer.restart();
	}
}

bool hornet::search_for_enemies()
{
	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = player_info->getGlobalBounds();

	PL_SIDE playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	//looks();
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
		displacement.x = acceleration * moveX * dir_x;
		displacement.y = acceleration * moveY * dir_x;
	}
	else
	{
		displacement.x = acceleration * moveX * (-dir_x);
		displacement.y = acceleration * moveY * (-dir_x);
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
	if (hornet_state_past != hornet_state)
	{
		DEATH_timer.restart();
		blow_timer.restart();
		hornet_state_past = hornet_state;
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

void hornet::changeHP(short i)
{
	if (hornet_state != HORNET_STATE::TAKING_DAMAGE)Enemy::changeHP(i);
}

void hornet::update_physics()


{
	if (hornet_state == HORNET_STATE::DEATH)
	{
		displacement.y += 1.f * gravity;
	}

	//displacement *= deceleration;


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
}

void hornet::direction_calculation()
{
	float targetX = get_position().x;
	float targetY = get_position().y;

	float startX = player_info_->getPosition().x;
	float startY = player_info_->getPosition().y;

	float directionX = targetX - startX;
	float directionY = targetY - startY;

	float length = std::sqrt(directionX * directionX + directionY * directionY);

	if (length != 0.0f)
	{
		float normalizedDirectionX = directionX / length;
		float normalizedDirectionY = directionY / length;


		moveX = normalizedDirectionX;
		moveY = normalizedDirectionY;
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
