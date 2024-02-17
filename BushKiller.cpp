#include "stdafx.h"
#include "BushKiller.h"


BushKiller::BushKiller(TileMap& map, GeneralInfo* player_info, short regime, TextureManager* t_manager_, 
	int index, string name)
	: Enemy(map, player_info,regime), t_manager(t_manager_)

{
	BushKiller::init_sprite(nullptr, index, name);
	BushKiller::init_physics();
	BushKiller::setAt(20);
	BushKiller::setHP(100);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
	
}

BushKiller::BushKiller(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y, 
	TextureManager* t_manager_, int index, string name) :
	Enemy(map, player_info_, pos_x, pos_y), t_manager(t_manager_)
{
	BushKiller::init_sprite(nullptr, index, name);
	BushKiller::init_physics();
	BushKiller::setAt(20);
	BushKiller::setHP(100);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
}

void BushKiller::init_physics()
{
	BUSH_TAKING_DAMAGE_TIMER.restart();
	DEATH_timer.restart();
	Shot_timer.restart();
	bush_state = ENEMY_STATE::SLEEPING;
	bush_state_past = ENEMY_STATE::IDLE;
	animation_state = ENEMY_ANIMATION_STATE::ENEMY_SLEEP;
	animation_state_past = ENEMY_ANIMATION_STATE::ENEMY_SLEEP;
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

void BushKiller::init_sprite(TextureManager* t_manager_, int index, string name)
{
	current_area = IntRect(0, 0, 2000, 1500);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(t_manager->getTexture(index, name));
	standard_frame = IntRect(0, 0, 64, 64);
	anim_area.setTextureRect(standard_frame);


	//Enemy_S.setTexture(bush_killer_t_);
	current_frame = IntRect(0, 0, 60, 60);
	Enemy_S.setTextureRect(current_frame);
}


void BushKiller::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_MOVING)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_IDLE)
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
	

	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_SLEEP)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_PUNCH)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_DEATH)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_TAKING_DAMAGE)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_SHOT)
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
	else if (animation_state == ENEMY_ANIMATION_STATE::ENEMY_AWAKENING)
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
	if (bush_state_past != bush_state)
	{
		DEATH_timer.restart();
		blow_timer.restart();
		Shot_timer.restart();
		bush_state_past = bush_state;
	}
	if (animation_state_past != animation_state)
	{
		//looks();
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
	FloatRect en = get_global_bounds_anim();
	FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

void BushKiller::looks()
{
	ORIENTATION playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	if (playerSide == ORIENTATION::LEFT)
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
	if (bush_state != ENEMY_STATE::TAKING_DAMAGE)Enemy::changeHP(i);
}

void BushKiller::draw_leaf( sf::RenderTarget& target)
{
	for(auto dr:killer_leaf_SH)
	{
		dr->render(target);
	}
}

void BushKiller::clear_leaf()
{
	killer_leaf_SH.clear();
}

bool BushKiller::leaf_empty()
{
	return killer_leaf_SH.empty();
}

void BushKiller::update_life()
{
	for (auto cl : killer_leaf_SH)
	{
		cl->update();
	}
}


void BushKiller::look(float direction)
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
	if (leaf_spawn.getElapsedTime().asSeconds() >= .4f) {
		vector<float> cord;
		cord.push_back(get_position().x+get_global_bounds().width/2);
		cord.push_back(get_position().y+get_global_bounds().height/2 + 10);
		cord.push_back(player_info->getPosition().x+player_info->getGlobalBounds().width/2);
		cord.push_back(player_info->getPosition().y+player_info->getGlobalBounds().height/2);
		killer_leaf_SH.push_back(new killer_leaf(*sandbox, cord, player_info, t_manager, 9, "sheet"));
		leaf_spawn.restart();
	}
	

}



void BushKiller::update_movement()
{
	update_life();
	if (HP <= 0)
	{
		bush_state = ENEMY_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP && bush_state != ENEMY_STATE::DEATH)
	{
		bush_state = ENEMY_STATE::TAKING_DAMAGE;
	}
	//if (!search_for_enemies())bush_state = ENEMY_STATE::SLEEP;
	clear_shot();


	switch (bush_state)
	{
	case ENEMY_STATE::SLEEPING:
		{
			//looks();
			//reset_Timer();
			displacement.x = 0.f;
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SLEEP;
			if (isPlayerInRadius(Enemy_S.getGlobalBounds(), player_info->getGlobalBounds(), 500)||bush_state==bush_state_past)
			{
				bush_state = ENEMY_STATE::AWAKENING;
			}
			break;
		}
	case ENEMY_STATE::IDLE:
		{

			animation_state = ENEMY_ANIMATION_STATE::ENEMY_IDLE;
			reset_Timer();
			looks();
			if (DEATH_timer.getElapsedTime().asSeconds() >= 2.0f)
			{
				bush_state = ENEMY_STATE::MOVING;
				DEATH_timer.restart();
			}

			break;
		}
	case ENEMY_STATE::AWAKENING:
		{
		animation_state = ENEMY_ANIMATION_STATE::ENEMY_AWAKENING;
		reset_Timer();
			if(DEATH_timer.getElapsedTime().asSeconds()>=2.F)
			{

				bush_state = ENEMY_STATE::IDLE;
				DEATH_timer.restart();
			}
			break;

		}


	case ENEMY_STATE::MOVING:
		{
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_MOVING;
			reset_Timer();
			//looks();
			displacement_max = 1.f;
			if (update_collision_x()||hit_a_wall())
			{
				if (canJumpForward())
				{
					jump(1.f);
					on_ground = false;
					jump_tile = true;
				}
				else moving *= -1.f;
			}
		
		
			if (sting())
			{
				bush_state = ENEMY_STATE::PUNCHING;
			}
			if (Shot_timer.getElapsedTime().asSeconds() >= 3.0f)
			{
				bush_state = ENEMY_STATE::SHOT;
			}
			walk(moving);
			break;
		}
	case ENEMY_STATE::SHOT:
		{
			looks();
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_SHOT;
			reset_Timer();
			displacement.x = 0.f;
			if (sting())
			{
				bush_state = ENEMY_STATE::PUNCHING;
			}
			if (Shot_timer.getElapsedTime().asSeconds() <= 2.F)
			{
				attack();
			}
			else
			{
				clear_shot();
				bush_state = ENEMY_STATE::MOVING;
			}

			break;
		}
	case ENEMY_STATE::PUNCHING:
		{
		looks();

			animation_state = ENEMY_ANIMATION_STATE::ENEMY_PUNCH;
			reset_Timer();
			if (!sting())bush_state = ENEMY_STATE::IDLE;
			if (Shot_timer.getElapsedTime().asSeconds() >= 1.0f)
			{
				bush_state = ENEMY_STATE::MOVING;
			}
			if (Shot_timer.getElapsedTime().asSeconds() >= 0.9F)
			{
				shot();
			}
		

			walk(moving);
			break;
		}


	case ENEMY_STATE::TAKING_DAMAGE:
		{

			animation_state = ENEMY_ANIMATION_STATE::ENEMY_TAKING_DAMAGE;
			reset_Timer();
			looks();

			if (HP <= 0)
			{
				hp_damage_i = HP;
				bush_state = ENEMY_STATE::DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				BUSH_TAKING_DAMAGE_TIMER.restart();
				hp_damage_i = HP;
			}
			if (BUSH_TAKING_DAMAGE_TIMER.getElapsedTime().asSeconds() >= 0.6f)
			{
				bush_state = ENEMY_STATE::IDLE;
			}

			break;
		}


	case ENEMY_STATE::DEATH:
		{

			displacement.x = 0;
			reset_Timer();
			animation_state = ENEMY_ANIMATION_STATE::ENEMY_DEATH;
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
	if (!killer_leaf_SH.empty())
	{


		
		for(auto cl = 0; cl < killer_leaf_SH.size(); cl++)
		{
			if(killer_leaf_SH[cl]->leaf_existence())
			{
				 
					delete* (killer_leaf_SH.begin() + cl);
					killer_leaf_SH.erase(killer_leaf_SH.begin() + cl);
				
			}
		}
		/*for (auto cl = killer_leaf_SH.begin(); cl != killer_leaf_SH.end(); ++cl)
		{
			if ((*cl)->leaf_existence())
			{
				delete* cl;
				cl = killer_leaf_SH.erase(cl);
			}
		}*/
	}
}

bool BushKiller::search_for_enemies()
{
	FloatRect look = observation_area.getGlobalBounds();
	FloatRect pl = player_info->getGlobalBounds();

	ORIENTATION playerSide = getPlayerSide(player_info->getPosition().x, get_position().x);
	//looks();
	if (look.intersects(pl))
	{
		return true;
	}

	return false;
}

void BushKiller::reset_attention()
{
	bush_state = ENEMY_STATE::SLEEPING;
}

void BushKiller::walk(const float dir_x)
{
	//looks();
	if (on_ground)
	{
		displacement.x += dir_x * acceleration;
	}

	// limits
	if (std::abs(displacement.x) > displacement_max)
	{
		displacement.x = displacement_max * ((displacement.x > 0.f) ? 1.f : -1.f);
	}

	//if (displacement.x != 0.0f) { //looks(); }
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
		jump_velocity *= 0.96;
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
