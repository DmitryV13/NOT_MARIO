
#include "stdafx.h"
#include "Enemy.h"

#include "laser_weapon.h"
#include "TileMap.h"


void Enemy::init_variables()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
}

Enemy::Enemy(TileMap& map, GeneralInfo* player_info_,short regime)
	: player_info(player_info_)
{
	blow_timer.restart();
	sandbox = &map;
	hp_bar = new HealthBarEnemy();
	init_variables();
	init_animation();
	Enemy::init_physics();

	if(regime == 1)start_position = generate_random_start_position(static_cast<float>(sandbox->getMapWidth()), static_cast<float>(sandbox->getMapHeight()));
	if(regime == 2)start_position = sandbox->cord_enemy();

	set_position(start_position.x, start_position.y);
	hp_bar->SET_ST_HP(HP);
}

/// \brief 
/// \param map 
/// \param player_info_ 
/// \param pos_x 
/// \param pos_y 
Enemy::Enemy(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y)
	: player_info(player_info_)
{
	blow_timer.restart();
	sandbox = &map;
	hp_bar = new HealthBarEnemy();
	init_variables();
	init_animation();
	Enemy::init_physics();


	set_position(pos_x, pos_y);
	hp_bar->SET_ST_HP(HP);
}

sf::Vector2f Enemy::get_position() const
{
	return Enemy_S.getPosition();
}

const FloatRect Enemy::get_global_bounds() const
{
	return Enemy_S.getGlobalBounds();
}
const FloatRect Enemy::get_global_bounds_anim() const
{
	return anim_area.getGlobalBounds();
}

short Enemy::getHP() const
{
	return HP;
}

void Enemy::updateHP_bar()
{
	hp_bar->update(anim_area);
}

//POSITION OF THE PLAYER RELATIVE TO THE ENEMY
PL_SIDE Enemy::getPlayerSide(float playerX, float enemyX)
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

//centering all areas relative to the basic
void Enemy::set_position(const float x, const float y)
{
	observation_area.setPosition(
		x - (observation_area.getGlobalBounds().width - (observation_area.getGlobalBounds().width / 2) - (Enemy_S.
			getGlobalBounds().width / 2)),
		(y - (observation_area.getGlobalBounds().height - Enemy_S.getGlobalBounds().height)));

	anim_area.setPosition(
		x - (anim_area.getGlobalBounds().width - (anim_area.getGlobalBounds().width / 2) - (Enemy_S.
			getGlobalBounds().width / 2)),
		(y - (anim_area.getGlobalBounds().height - Enemy_S.getGlobalBounds().height)));

	Enemy_S.setPosition(x, y);
}

sf::Vector2f Enemy::generate_random_start_position(int map_width, int map_height) const
{
	constexpr int max_attempts = 1000000;

	for (int i = 0; i < max_attempts; i++)
	{
		float x = 64 + rand() % (map_width - 64 * 2 + 1);
		float y = 64 + rand() % (map_height - 64 * 2 + 1);

		const int center_x = (x + 64) / 64;
		const int center_y = (y + 64) / 64;

		bool collision_detected = false;
		if (sandbox->outOfMap(center_y, center_x) && sandbox->isBlock(center_y, center_x))
		{
			collision_detected = true;
		}
		else
		{
			for (int dx = -2; dx <= 2; dx++)
			{
				for (int dy = -3; dy <= 3; dy++)
				{
					const int block_x = (x + dx) / 64;
					const int block_y = (y + dy) / 64;
					if (sandbox->outOfMap(block_y, block_x) && sandbox->isBlock(block_y, block_x))
					{
						collision_detected = true;
						break;
					}
				}
				if (collision_detected)
				{
					break;
				}
			}
		}
		if (!collision_detected)
		{
			return {x, y};
		}
	}
	return {0.f, 0.f};
}

void Enemy::render(sf::RenderTarget& target) const
{
	target.draw(anim_area);
	target.draw(Enemy_S);
	hp_bar->render(target);
}

void Enemy::update()
{

	update_movement();
	update_animation();
	update_physics();
	updateHP_bar();
}

void Enemy::reset_animation_timer()
{
	animation_timer.restart();
	animation_switch = true;
}


void Enemy::init_animation()
{
	animation_switch = true;
	animation_timer.restart();
}

const bool& Enemy::get_animation_switch()
{
	bool tmp_switch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmp_switch;
}

void Enemy::init_physics()
{
	displacement_max = 1.f;
	attention_counter = 3;
	displacement_min = 0.3f;
	acceleration = 0.4f;
	deceleration = 0.77f;
	gravity = 2.5f;
	velocity_max_y = 6.f;
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
	count_shot = 0;
}

void Enemy::walk(const float dir_x)
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

	if (animation_counter_think > 2 && animation_state != ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		displacement.x = 0;
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
	}
	else if (displacement.y >= gravity)animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING_DOWN;
	else if (jump_tile)animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
	else animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;


	//logic when exposing a player
	if (search_for_enemies() && ((on_ground) || (jump_tile)))
	{
		attack();
	}
	else
	{
		reset_attention();
		clear_shot();
	}
}

bool Enemy::is_player_in_radius(const sf::FloatRect& observationArea, const sf::FloatRect& playerBounds, float radius) const
{		
	if (observation_area.getGlobalBounds().intersects(playerBounds))
	{
		const sf::Vector2f observation_center = {
			observationArea.left + observationArea.width / 2,
			observationArea.top + observationArea.height / 2
		};

		const sf::Vector2f player_center = {
			playerBounds.left + playerBounds.width / 2,
			playerBounds.top + playerBounds.height / 2
		};

		const float distance = std::sqrt(
			std::pow(observation_center.x - player_center.x, 2) +
			std::pow(observation_center.y - player_center.y, 2)
		);


		return distance <= radius;
	}

	return false;
}

//ground contact
void Enemy::reset_jump_access()
{
	displacement.y = 0.f;
	on_ground = true;
	jump_tile = false;
}


//jump handling
void Enemy::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = dir_y * 5.5f;
	}
}

bool Enemy::player_contact() const
{
	const int center_x = get_position().x / 64;
	const int center_y = get_position().y / 64;
	int l = 2;
	if (looks_to_the_right)
		for (int i = center_y - 5; i <= center_y + 5; i++)
		{
			for (int j = center_x; j <= center_x + l; j++)
			{
				if (i >= 0 && i < (sandbox->getMapHeight() / 64) && j >= 0 && j < (sandbox->getMapWidth() / 64))
				{
					if (sandbox->isOccupied(i, j))
					{
						return true;
					}
				}
			}
		}

	else
		for (int i = center_y - 5; i <= center_y + 5; i++)
		{
			for (int j = center_x - l + 1; j <= center_x; j++)
			{
				if (i >= 0 && i < (sandbox->getMapHeight() / 64) && j >= 0 && j < (sandbox->getMapWidth() / 64))
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


void Enemy::update_physics()
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

	if (jump_tile && search_for_enemies())
	{
		displacement.x = 2 * moving * displacement_max;
	}
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
	if (displacement.x > 0 && displacement_max == 1.f)
		step_right++;
	if (displacement.x < 0 && displacement_max == 1.f)
		step_left++;

	//move all areas
	Enemy_S.move(displacement);
	observation_area.move(displacement);
	anim_area.move(displacement);
}

// collision x
bool Enemy::update_collision_x()
{
	bool was_collision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = Enemy_S.getPosition().y / 64; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 64; i
	     ++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 64; j < (Enemy_S.getPosition().x + displacement.x +
			     Enemy_S.getGlobalBounds().width) / 64; j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j) || j <= 0 || j > sandbox->getMapWidth() / 64)
			{
				was_collision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	set_position(newPosition.x, newPosition.y);
	return was_collision;
}

//resolving jump collision
bool Enemy::update_collision_x_jump()
{
	bool was_collision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = Enemy_S.getPosition().y / 64; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 64; i
	     ++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 64; j < (Enemy_S.getPosition().x + displacement.x +
			     Enemy_S.getGlobalBounds().width) / 64; j++)
		{
			if (sandbox->outOfMap(i, j) && (i > 0 && sandbox->isBlock(i - 1, j)) || j <= 0 || j > sandbox->getMapWidth()
				/ 64)
			{
				was_collision = true;
				if (displacement.x >= 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().width;
				}
				if (displacement.x < 0)
				{
					newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}
	set_position(newPosition.x, newPosition.y);
	return was_collision;
}

//collision y
bool Enemy::update_collision_y()
{
	bool was_collision = false;

	sf::Vector2f newPosition(Enemy_S.getPosition().x, Enemy_S.getPosition().y);

	for (int i = (Enemy_S.getPosition().y + displacement.y) / 64; i < (Enemy_S.getPosition().y + displacement.y +
		     Enemy_S.getGlobalBounds().height) / 64; i++)
	{
		for (int j = Enemy_S.getPosition().x / 64; j < (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width) / 64;
		     j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				was_collision = true;
				reset_jump_access();
				if (displacement.y > 0)
				{
					reset_jump_access();
					newPosition.y = (i * sandbox->getSizeTexture() - Enemy_S.getGlobalBounds().height);
				}
				if (displacement.y < 0)
				{
					reset_jump_access();
					newPosition.y = i * sandbox->getSizeTexture() + sandbox->getSizeTexture();
				}
			}
		}
	}

	set_position(newPosition.x, newPosition.y);
	return was_collision;
}

//Cross enemy and player sprites
bool Enemy::sting() const
{
	FloatRect en = get_global_bounds();
	FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}


void Enemy::jump_towards_player()
{
	const float distance = std::abs(player_info->getPosition().x - get_position().x);
	float jump_height = std::min(1.0f, distance / 300.0f) * 2.0f;
	constexpr float max_jump_height = 2.0f;
	jump_height = std::min(jump_height, max_jump_height);

	jump(jump_height);
}

void Enemy::changeHP(short attackPl)
{
	HP -= attackPl;
	hp_bar->setHP_cur(HP);
}

void Enemy::set_hp(const short hp)
{
	HP = hp;
}

void Enemy::set_at(const short at)
{
	attack_ = at;
}

bool Enemy::can_move_forward() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int center_x;
	int center_y;
	if (direction == 1)
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width / 2)) / 64);
		center_y = static_cast<int>(get_position().y / 64);
	}
	else
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width) / 2) / 64) - direction;
		center_y = static_cast<int>(get_position().y / 64);
	}


	const int next_x = center_x + direction;
	const int next_y = center_y;


	if (sandbox->outOfMap(next_y + 2, next_x) && !sandbox->isBlock(next_y + 1, next_x) && !sandbox->isBlock(
		next_y + 2, next_x))
	{
		return true;
	}


	return false; 
}

//intersection with player on external search area
bool Enemy::outside_sting()
{
	const FloatRect en = get_global_bounds_anim();
	const FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

//another collision prototype by x
bool Enemy::hit_a_wall() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int center_x;
	int center_y;
	if (direction == 1)
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width)) / 64) - direction;
		center_y = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height / 2)) / 64);
	}
	else
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width)) / 64);
		center_y = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height / 2)) / 64);
	}


	const int next_x = center_x + direction;
	const int next_y = center_y;

	if (sandbox->outOfMap(next_y, next_x) && sandbox->isBlock(next_y, next_x))
	{
		return true;
	}


	return false;
}
//jump availability analysis
bool Enemy::can_jump_forward() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int center_x;
	int center_y;
	if (direction == 1)
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width / 2)) / 64);
		center_y = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height-64/2 )) / 64);
	}
	else
	{
		center_x = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width) / 2) / 64);
		center_y = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height-64/2 )) / 64);
	}


	const int next_x = center_x + direction;
	const int next_y = center_y;


	if (sandbox->outOfMap(next_y - 2, next_x) && !sandbox->isBlock(next_y - 1, next_x) && !sandbox->isBlock(
		next_y - 2, next_x))
	{
		return true;
	}


	return false;
}

