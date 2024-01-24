#include "stdafx.h"
#include "Enemy.h"

#include "laser_weapon.h"
#include "TileMap.h"


sf::Vector2f Enemy::generate_random_start_position(int mapWidth, int mapHeight)
{
	//  randomized distribution
	int maxAttempts = 1000000;

	for (int i = 0; i < maxAttempts; i++)
	{
		int x = 64 + rand() % (mapWidth - 64 * 2 + 1);
		int y = 64 + rand() % (mapHeight - 64 * 2 + 1);

		int centerX = (x + 64) / 64;
		int centerY = (y + 64) / 64;

		bool collisionDetected = false;
		if (sandbox->outOfMap(centerY, centerX) && sandbox->isBlock(centerY, centerX))
		{
			collisionDetected = true;
		}
		else
		{
			for (int dx = -2; dx <= 2; dx++)
			{
				for (int dy = -3; dy <= 3; dy++)
				{
					int blockX = (x + dx) / 64;
					int blockY = (y + dy) / 64;
					if (sandbox->outOfMap(blockY, blockX) && sandbox->isBlock(blockY, blockX))
					{
						collisionDetected = true;
						break;
					}
				}
				if (collisionDetected)
				{
					break;
				}
			}
		}
		if (!collisionDetected)
		{
			return sf::Vector2f(x, y);
		}
	}
	return sf::Vector2f(0, 0);
}

void Enemy::init_variables()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
}

Enemy::Enemy(TileMap& map, GeneralInfo* player_info_)
	: player_info(player_info_)
{
	blow_timer.restart();
	//player_ = &pl;
	sandbox = &map;
	init_variables();
	init_animation();
	Enemy::init_physics();
	//start_position = generate_random_start_position(sandbox->getMapWidth(), sandbox->getMapHeight());
	start_position = sandbox->cord_enemy();

	set_position(start_position.x, start_position.y);

	//set_position(1300,600);
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

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(anim_area);
	target.draw(Enemy_S);
}

void Enemy::update()
{
	update_movement();
	update_animation();
	update_physics();
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
	bool tmpSwitch = animation_switch;
	if (animation_switch)
	{
		animation_switch = false;
	}
	return tmpSwitch;
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
	animation_counter_think = 0;
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

bool Enemy::isPlayerInRadius(const sf::FloatRect& observationArea, const sf::FloatRect& playerBounds, float radius)
{		
	if (observation_area.getGlobalBounds().intersects(playerBounds))
	{
		sf::Vector2f observationCenter = {
			observationArea.left + observationArea.width / 2,
			observationArea.top + observationArea.height / 2
		};

		sf::Vector2f playerCenter = {
			playerBounds.left + playerBounds.width / 2,
			playerBounds.top + playerBounds.height / 2
		};

		float distance = std::sqrt(
			std::pow(observationCenter.x - playerCenter.x, 2) +
			std::pow(observationCenter.y - playerCenter.y, 2)
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

bool Enemy::player_contact()
{
	int centerX = get_position().x / 64;
	int centerY = get_position().y / 64;
	int l = 2;
	if (looks_to_the_right)
		for (int i = centerY - 5; i <= centerY + 5; i++)
		{
			for (int j = centerX; j <= centerX + l; j++)
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
		for (int i = centerY - 5; i <= centerY + 5; i++)
		{
			for (int j = centerX - l + 1; j <= centerX; j++)
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
	anim_area.move(displacement);
}

// collision x
bool Enemy::update_collision_x()
{
	bool wasCollision = false;
	sf::Vector2f newPosition(get_position().x, get_position().y);
	for (int i = Enemy_S.getPosition().y / 64; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 64; i
	     ++)
	{
		for (int j = (Enemy_S.getPosition().x + displacement.x) / 64; j < (Enemy_S.getPosition().x + displacement.x +
			     Enemy_S.getGlobalBounds().width) / 64; j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j) || j <= 0 || j > sandbox->getMapWidth() / 64)
			{
				wasCollision = true;
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
	return wasCollision;
}

//resolving jump collision
bool Enemy::update_collision_x_jump()
{
	bool wasCollision = false;
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
				wasCollision = true;
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
	return wasCollision;
}

//collision y
bool Enemy::update_collision_y()
{
	bool wasCollision = false;

	sf::Vector2f newPosition(Enemy_S.getPosition().x, Enemy_S.getPosition().y);

	for (int i = (Enemy_S.getPosition().y + displacement.y) / 64; i < (Enemy_S.getPosition().y + displacement.y +
		     Enemy_S.getGlobalBounds().height) / 64; i++)
	{
		for (int j = Enemy_S.getPosition().x / 64; j < (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width) / 64;
		     j++)
		{
			if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j))
			{
				wasCollision = true;
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
	return wasCollision;
}

bool Enemy::sting()
{
	FloatRect en = get_global_bounds();
	FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

void Enemy::jump_towards_player()
{
	float distance = std::abs(player_info->getPosition().x - get_position().x);
	float jump_Height = std::min(1.0f, distance / 300.0f) * 2.0f;
	float max_jump_height = 2.0f;
	jump_Height = std::min(jump_Height, max_jump_height);

	jump(jump_Height);
}

void Enemy::changeHP(short attackPl)
{
	HP -= attackPl;
}

void Enemy::setHP(short hp)
{
	HP = hp;
}

void Enemy::setAt(short at)
{
	attack_ = at;
}

bool Enemy::canMoveForward() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int centerX;
	int centerY;
	if (direction == 1)
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width / 2)) / 64);
		centerY = static_cast<int>(get_position().y / 64);
	}
	else
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width) / 2) / 64) - direction;
		centerY = static_cast<int>(get_position().y / 64);
	}


	const int nextX = centerX + direction;
	const int nextY = centerY;


	if (sandbox->outOfMap(nextY + 2, nextX) && !sandbox->isBlock(nextY + 1, nextX) && !sandbox->isBlock(
		nextY + 2, nextX))
	{
		return true;
	}


	return false; // Враг не может двигаться вперед
}
bool Enemy::outside_sting()
{
	FloatRect en = get_global_bounds_anim();
	FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

bool Enemy::hit_a_wall() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int centerX;
	int centerY;
	if (direction == 1)
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width)) / 64) - direction;
		centerY = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height / 2)) / 64);
	}
	else
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width)) / 64);
		centerY = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height / 2)) / 64);
	}


	const int nextX = centerX + direction;
	const int nextY = centerY;

	if (sandbox->outOfMap(nextY, nextX) && sandbox->isBlock(nextY, nextX))
	{
		return true;
	}


	return false;
}

bool Enemy::canJumpForward() const
{
	const int direction = looks_to_the_right ? 1 : -1;
	int centerX;
	int centerY;
	if (direction == 1)
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width / 2)) / 64);
		centerY = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height-64/2 )) / 64);
	}
	else
	{
		centerX = static_cast<int>((get_position().x + (Enemy_S.getGlobalBounds().width) / 2) / 64);
		centerY = static_cast<int>((get_position().y + (Enemy_S.getGlobalBounds().height-64/2 )) / 64);
	}


	const int nextX = centerX + direction;
	const int nextY = centerY;


	if (sandbox->outOfMap(nextY - 2, nextX) && !sandbox->isBlock(nextY - 1, nextX) && !sandbox->isBlock(
		nextY - 2, nextX))
	{
		return true;
	}


	return false;
}
