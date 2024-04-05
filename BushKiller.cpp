#include "stdafx.h"
#include "BushKiller.h"


BushKiller::BushKiller(TileMap& map, GeneralInfo* player_info, const short regime)
	: Enemy(map, player_info,regime), player_info_(player_info)

{
	BushKiller::init_texture();
	BushKiller::init_sprite();
	BushKiller::init_physics();
	BushKiller::set_at(20);
	BushKiller::set_hp(100);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
	
}

BushKiller::BushKiller(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	BushKiller::init_texture();
	BushKiller::init_sprite();
	BushKiller::init_physics();
	BushKiller::set_at(20);
	BushKiller::set_hp(100);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
}

void BushKiller::init_physics()
{
	bush_taking_damage_timer_.restart();
	death_timer_.restart();
	shot_timer_.restart();
	bush_state_ = BUSH_KILLER_STATE::SLEEP;
	bush_state_past_ = BUSH_KILLER_STATE::IDLE;
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
	animation_state_past = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
	displacement_max = 2.5f;
	displacement_min = 0.3f;
	acceleration = 0.4f;
	deceleration = 0.77f;
	gravity = 2.5f;
	velocity_max_y = 15.f;
	on_ground = false;
	jump_velocity = 7.f;
	moving = 1.f;
	jump_tile = false;
	displacement.x = 0.f;
	displacement.y = 0.f;
	looks_to_the_left = false;
	looks_to_the_right = true;
}

void BushKiller::init_texture()
{
	if (!bush_killer_t_.loadFromFile("Textures/Enemies/bush_killer.png"))
	{
		std::cout << "Error -> bush_killer -> couldn't load bush_killer texture" << '\n';
	}
}

void BushKiller::init_sprite()
{
	current_area = IntRect(0, 0, 2000, 1500);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(bush_killer_t_);
	standard_frame = IntRect(0, 0, 64, 64);
	anim_area.setTextureRect(standard_frame);


	current_frame = IntRect(0, 0, 60, 60);
	Enemy_S.setTextureRect(current_frame);
}

/// <summary>
/// Update Animation
/// </summary>
void BushKiller::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING	)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.15f || get_animation_switch())
		{
			standard_frame.top = 256.f;
			if (looks_to_the_right)
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
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 320	)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_IDLE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch())
		{
			standard_frame.top = 320.f;

			if (looks_to_the_right)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 384)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 448)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.5f || get_animation_switch())
		{
			standard_frame.top = 0.f;

			if (looks_to_the_right)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 384)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 448)
				{
					standard_frame.left = 64.f;
				}
				standard_frame.width = -64.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_PUNCH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 192.f;

			if (looks_to_the_right)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 256)
				{
					standard_frame.left = 192.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 320)
				{
					standard_frame.left = 256.f;
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
			standard_frame.top = 384.F;

			if (looks_to_the_right)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 320)
				{
					standard_frame.left = 256.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 384)
				{
					standard_frame.left = 320.f;
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
			standard_frame.top = 448.F;

			if (looks_to_the_right)
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
				standard_frame.height = 64.f;

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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SHOT)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 128.f;

			if (looks_to_the_right)
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
				standard_frame.height = 64.f;

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
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_AWAKENING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 64.F;

			if (looks_to_the_right)
			{
				standard_frame.left += 64;
				if (standard_frame.left >= 384)
				{
					standard_frame.left = 320.f;
				}
				standard_frame.width = 64;
			}
			else
			{
				standard_frame.height = 64.f;

				standard_frame.left += 64;
				if (standard_frame.left >= 448)
				{
					standard_frame.left = 384.f;
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


void BushKiller::reset_Timer()
{
	if (bush_state_past_ != bush_state_)
	{
		death_timer_.restart();
		blow_timer.restart();
		shot_timer_.restart();
		bush_state_past_ = bush_state_;
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

bool BushKiller::outside_sting()
{
	const FloatRect en = get_global_bounds_anim();
	const FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

void BushKiller::looks()
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

void BushKiller::changeHP(short i)
{
	if (bush_state_ != BUSH_KILLER_STATE::TAKING_DAMAGE)Enemy::changeHP(i);
}

void BushKiller::draw_leaf( sf::RenderTarget& target) const
{
	for(const auto dr:killer_leaf_sh_)
	{
		dr->render(target);
	}
}

void BushKiller::clear_leaf()
{
	killer_leaf_sh_.clear();
}

bool BushKiller::leaf_empty() const
{
	return killer_leaf_sh_.empty();
}

void BushKiller::update_life() const
{
	for (auto cl : killer_leaf_sh_)
	{
		cl->update();
	}
}


void BushKiller::look(const float direction)
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

void BushKiller::attack()
{
	if (leaf_spawn_.getElapsedTime().asSeconds() >= .4f) {
		vector<float> cord;
		cord.push_back(get_position().x+get_global_bounds().width/2);
		cord.push_back(get_position().y+get_global_bounds().height/2 + 10);
		cord.push_back(player_info->getPosition().x+player_info->getGlobalBounds().width/2);
		cord.push_back(player_info->getPosition().y+player_info->getGlobalBounds().height/2);
		killer_leaf_sh_.push_back(new killer_leaf(*sandbox, cord, player_info));
		leaf_spawn_.restart();
	}
	

}

void BushKiller::update_movement()
{
	update_life();
	if (HP <= 0)
	{
		bush_state_ = BUSH_KILLER_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP && bush_state_ != BUSH_KILLER_STATE::DEATH)
	{
		bush_state_ = BUSH_KILLER_STATE::TAKING_DAMAGE;
	}
	clear_shot();


	switch (bush_state_)
	{
	case BUSH_KILLER_STATE::SLEEP:
		{
			displacement.x = 0.f;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
			if (is_player_in_radius(Enemy_S.getGlobalBounds(), player_info->getGlobalBounds(), 500)||bush_state_==bush_state_past_)
			{
				bush_state_ = BUSH_KILLER_STATE::AWAKENING;
			}
			break;
		}
	case BUSH_KILLER_STATE::IDLE:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			reset_Timer();
			looks();
			if (death_timer_.getElapsedTime().asSeconds() >= 2.0f)
			{
				bush_state_ = BUSH_KILLER_STATE::MOVING;
				death_timer_.restart();
			}

			break;
		}
	case BUSH_KILLER_STATE::AWAKENING:
		{
		animation_state = ENEMY_ANIMATION_STATES::ENEMY_AWAKENING;
		reset_Timer();
			if(death_timer_.getElapsedTime().asSeconds()>=2.F)
			{

				bush_state_ = BUSH_KILLER_STATE::IDLE;
				death_timer_.restart();
			}
			break;

		}


	case BUSH_KILLER_STATE::MOVING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			reset_Timer();
			//looks();
			displacement_max = 1.f;
			if (update_collision_x()||hit_a_wall())
			{
				if (can_jump_forward())
				{
					jump(1.f);
					on_ground = false;
					jump_tile = true;
				}
				else moving *= -1.f;
			}
		
		
			if (sting())
			{
				bush_state_ = BUSH_KILLER_STATE::PUNCH;
			}
			if (shot_timer_.getElapsedTime().asSeconds() >= 3.0f)
			{
				bush_state_ = BUSH_KILLER_STATE::SHOT;
			}
			walk(moving);
			break;
		}
	case BUSH_KILLER_STATE::SHOT:
		{
			looks();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SHOT;
			reset_Timer();
			displacement.x = 0.f;
			if (sting())
			{
				bush_state_ = BUSH_KILLER_STATE::PUNCH;
			}
			if (shot_timer_.getElapsedTime().asSeconds() <= 2.F)
			{
				attack();
			}
			else
			{
				clear_shot();
				bush_state_ = BUSH_KILLER_STATE::MOVING;
			}

			break;
		}
	case BUSH_KILLER_STATE::PUNCH:
		{
		looks();

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_PUNCH;
			reset_Timer();
			if (!sting())bush_state_ = BUSH_KILLER_STATE::IDLE;
			if (shot_timer_.getElapsedTime().asSeconds() >= 1.0f)
			{
				bush_state_ = BUSH_KILLER_STATE::MOVING;
			}
			if (shot_timer_.getElapsedTime().asSeconds() >= 0.9F)
			{
				shot();
				player_info->setStanTime(1.f);
			}
		

			walk(moving);
			break;
		}


	case BUSH_KILLER_STATE::TAKING_DAMAGE:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			reset_Timer();
			looks();

			if (HP <= 0)
			{
				hp_damage_i = HP;
				bush_state_ = BUSH_KILLER_STATE::DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				bush_taking_damage_timer_.restart();
				hp_damage_i = HP;
			}
			if (bush_taking_damage_timer_.getElapsedTime().asSeconds() >= 0.6f)
			{
				bush_state_ = BUSH_KILLER_STATE::IDLE;
			}

			break;
		}


	case BUSH_KILLER_STATE::DEATH:
		{

			displacement.x = 0;
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			break;
		}
	}
}


void BushKiller::shot()
{
	if (outside_sting() || sting())player_info->changeHP(-attack_ - (rand() % 10));
}


void BushKiller::clear_shot()
{
	if (!killer_leaf_sh_.empty())
	{
		for(auto cl = 0; cl < killer_leaf_sh_.size(); cl++)
		{
			if(killer_leaf_sh_[cl]->leaf_existence())
			{
				 
					delete* (killer_leaf_sh_.begin() + cl);
					killer_leaf_sh_.erase(killer_leaf_sh_.begin() + cl);
				
			}
		}
		
	}
}

bool BushKiller::search_for_enemies()
{
	const FloatRect look = observation_area.getGlobalBounds();
	const FloatRect pl = player_info->getGlobalBounds();

	PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (look.intersects(pl))
	{
		return true;
	}

	return false;
}

void BushKiller::reset_attention()
{
	bush_state_ = BUSH_KILLER_STATE::SLEEP;
}

void BushKiller::walk(const float dir_x)
{
	if (on_ground)
	{
		displacement.x += dir_x * acceleration;
	}

	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}

}


void BushKiller::update_physics()
{
	displacement.y += 1.f * gravity;
	if (std::abs(displacement.y) > velocity_max_y)
	{
		displacement.y = velocity_max_y * ((displacement.y > 0.f) ? 1.f : -1.f);
	}


	if (jump_tile)
	{
		displacement.y -= jump_velocity;

		displacement.x = 2 * moving * displacement_max;
		jump_velocity *= 0.96f;
	}
	displacement *= deceleration;


	if (update_collision_x())
	{
		displacement.x = 0.f;
	}
	if (update_collision_y())
	{
		displacement.y = 0.f;
	}
	Enemy_S.move(displacement);
	set_position(get_position().x, get_position().y);
}


void BushKiller::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = dir_y * 5.5f;
	}
}
