#include "stdafx.h"
#include "WolfBoss.h"


WolfBoss::WolfBoss(TileMap& map, GeneralInfo* player_info, const short regime)
	: Enemy(map, player_info,regime), player_info_(player_info)
{
	WolfBoss::init_texture();
	WolfBoss::init_sprite();
	WolfBoss::init_physics();
	WolfBoss::set_at(50);
	WolfBoss::set_hp(5000);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
}

WolfBoss::WolfBoss(TileMap& map, GeneralInfo* player_info_, const float pos_x, const float pos_y) :
	Enemy(map, player_info_, pos_x, pos_y)
{
	WolfBoss::init_texture();
	WolfBoss::init_sprite();
	WolfBoss::init_physics();
	WolfBoss::set_at(50);
	WolfBoss::set_hp(5000);
	hp_damage_i = HP;
	hp_bar->SET_ST_HP(HP);
}

void WolfBoss::init_physics()
{
	
	boss_state_torment_ = false;
	boss_state_past_ = BOSS_STATE::IDLE;
	boss_taking_damage_timer_.restart();
	
	idle_timer_.restart();
	death_timer_.restart();
	shot_timer_.restart();
	count_jm = 0;
	rand_ = 0;
	awakening_ = false;
	retreat_counter_ = 0;
	max_retreat_duration_ = 100;
	boss_state_ = BOSS_STATE::SLEEP;
	animation_state_past = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
	displacement_max = 2.5f;
	attention_counter = 3;
	displacement_min = 0.3f;
	acceleration = 0.4f;
	deceleration = 0.77f;
	gravity = 2.5f;
	velocity_max_y = 15.f;
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
	max_step = 1000;
	pl_contact_ = false;
	pl_cont_jump_ = false;
}

void WolfBoss::init_texture()
{
	if (!wolf_boss_t_.loadFromFile("Textures/Enemies/boss_wolf.png"))
	{
		std::cout << "Error -> Enemy_Wolf_Boss -> couldn't load enemy_Wolf_Boss texture" << '\n';
	}
}

void WolfBoss::init_sprite()
{
	current_area = IntRect(0, 0, 2000, 200);
	observation_area.setTextureRect(current_area);

	anim_area.setTexture(wolf_boss_t_);
	standard_frame = IntRect(0, 0, 250, 250);
	anim_area.setTextureRect(standard_frame);


	//Enemy_S.setTexture(Wolf_Boss_t_);
	current_frame = IntRect(0, 0, 128, 128);
	Enemy_S.setTextureRect(current_frame);
}


void WolfBoss::update_animation()
{
	if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_MOVING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.15f || get_animation_switch())
		{
			if (looks_to_the_right)
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1250)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
				standard_frame.top = 0;
			}
			else
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1500)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
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
			standard_frame.top = 500;

			if (looks_to_the_right)
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1000)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1250)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_ATTENTION)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.05f || get_animation_switch())
		{
			standard_frame.top = 500;

			if (looks_to_the_right)
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1000)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{
				standard_frame.height = 250.f;

				standard_frame.left += 250;
				if (standard_frame.left >= 1250)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}

			anim_area.setTextureRect(standard_frame);

			animation_timer.restart();
		}
	}

	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_SLEEP)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.5f || get_animation_switch())
		{
			standard_frame.top = 2250.f;
			if (looks_to_the_right)
			{
				standard_frame.left += 250;
				if (!search_for_enemies()|| !is_player_in_radius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 300))
				{
					if (standard_frame.left >= 750)
					{
						standard_frame.left = 0.f;
					}
				}
					
				else if(search_for_enemies())
					{
						if (standard_frame.left >= 1500)
						{
							standard_frame.left = 1250.f;
						}
					}
				standard_frame.width = 250.f;
			}
			else
			{
				standard_frame.left += 250;
				if (!search_for_enemies() || !is_player_in_radius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 300))
				{
					if (standard_frame.left >= 1000)
					{
						standard_frame.left = 250.f;
					}
				}
					
				else if (search_for_enemies())
					{
						if (standard_frame.left >= 1750)
						{
							standard_frame.left = 1500.f;
						}
					}
				standard_frame.width = -250.f;
			}

			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_JUMPING)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.15f || get_animation_switch())
		{
			{
				standard_frame.top = 1750.f;

				if (looks_to_the_right)
				{
					standard_frame.height = 250.f;

					standard_frame.left += 250;
					if (standard_frame.left >= 1750)
					{
						standard_frame.left = 0.f;
					}
					standard_frame.width = 250;
				}
				else
				{
					standard_frame.height = 250.f;

					standard_frame.left += 250;
					if (standard_frame.left >= 2000)
					{
						standard_frame.left = 250.f;
					}
					standard_frame.width = -250;
				}
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_HOWL)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.25f || get_animation_switch())
		{
			standard_frame.top = 250.f;

			if (looks_to_the_right)
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 4000)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250;
			}
			else
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 4250)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_PUNCH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{

			standard_frame.top = 1000;
			if (looks_to_the_right)
			{
				

				standard_frame.left += 250;
				if (current_frame.left >= 2250)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 2500)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DOUBLE_KICK)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{

			standard_frame.top = 1250;
			if (looks_to_the_right)
			{


				standard_frame.left += 250;
				if (standard_frame.left >= 1500)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 1750)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_DEATH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.9f || get_animation_switch())
		{

			standard_frame.top = 2000;
			if (looks_to_the_right)
			{


				standard_frame.left += 250;
				if (standard_frame.left >= 1000)
				{
					standard_frame.left = 750.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 1250)
				{
					standard_frame.left = 1000.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
		}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{

			standard_frame.top = 2500;
			if (looks_to_the_right)
			{


				standard_frame.left += 250;
				if (standard_frame.left >= 750)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{

				standard_frame.left += 250;
				if (standard_frame.left >= 1000)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
		}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_HIT_EARTH)
	{
		if (animation_timer.getElapsedTime().asSeconds() >= 0.1f || get_animation_switch())
		{
			standard_frame.top = 1500;
			if (looks_to_the_right)
			{
				standard_frame.left += 250;
				if (standard_frame.left >= 2000)
				{
					standard_frame.left = 0.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{
				standard_frame.left += 250;
				if (standard_frame.left >= 2250)
				{
					standard_frame.left = 250.f;
				}
				standard_frame.width = -250.f;
			}
			anim_area.setTextureRect(standard_frame);
			animation_timer.restart();
		}
	}
	else if (animation_state == ENEMY_ANIMATION_STATES::ENEMY_RUN)
	{
		if (0.1f >= animation_timer.getElapsedTime().asSeconds() || get_animation_switch())
		{
			standard_frame.top = 750;
			if (looks_to_the_right)
			{
				standard_frame.left += 250;
				if (standard_frame.left >= 1750)
				{
					standard_frame.left = 750.f;
				}
				standard_frame.width = 250.f;
			}
			else
			{
				standard_frame.left += 250;
				if (standard_frame.left >= 2000)
				{
					standard_frame.left = 1000.f;
				}
				standard_frame.width = -250.f;
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

PL_SIDE WolfBoss::getPlayerSide(const float player_x, const float enemy_x)
{
	if (player_x < enemy_x)
	{
		return PL_SIDE::LEFT;
	}
	else
	{
		return PL_SIDE::RIGHT;
	}
}

void WolfBoss::reset_Timer()
{
	if (boss_state_past_ != boss_state_)
	{
		count_anim = 0;
		idle_timer_.restart();
		death_timer_.restart();
		blow_timer.restart();
		shot_timer_.restart();
		retreating_timer_.restart();
		jumping_att_timer_.restart();
		boss_state_past_ = boss_state_;
		distance_ = (player_info->getPosition().x - get_position().x);
	}
	if (animation_state_past != animation_state)
	{
		looks();
		if (looks_to_the_right)
		{
			standard_frame.left = 0.f;
			animation_timer.restart();
		}
		else
		{
			standard_frame.left = 250.f;
			animation_timer.restart();
		}
		animation_state_past = animation_state;
	}
}

bool WolfBoss::outside_sting()
{
	const FloatRect en = get_global_bounds_anim();
	const FloatRect pl = player_info->getGlobalBounds();
	return en.intersects(pl);
}

void WolfBoss::looks()
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

void WolfBoss::changeHP(const short i)
{
	if( boss_state_ == BOSS_STATE::ATTACKING|| boss_state_ == BOSS_STATE::HOWL || 
		boss_state_ == BOSS_STATE::MOVING|| boss_state_ == BOSS_STATE::SLEEP|| boss_state_ == BOSS_STATE::RETREATING )Enemy::changeHP(i);
}

void WolfBoss::updateHP_bar()
{
	hp_bar->update(Enemy_S);

}


void WolfBoss::update_movement()
{

	if (HP <= 0)
	{
		boss_state_ = BOSS_STATE::DEATH;
		hp_damage_i = HP;
	}
	if (hp_damage_i > HP && boss_state_ != BOSS_STATE::DEATH)
	{
		boss_state_ = BOSS_STATE::TAKING_DAMAGE;
	}
	if (!sting())boss_state_torment_ = false;
	float distance_to_player = std::abs(player_info->getPosition().x - get_position().x);
	switch (boss_state_)
	{
	case BOSS_STATE::SLEEP:
		{
		looks();

			displacement.x = 0.f;
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_SLEEP;
			if (is_player_in_radius(observation_area.getGlobalBounds(), player_info->getGlobalBounds(), 300) ||
				boss_state_past_ == boss_state_)
			{
				reset_Timer();
				if (idle_timer_.getElapsedTime().asSeconds() >= 1.5f)
				{
					boss_state_ = BOSS_STATE::IDLE;
				}
			}
			break;
		}
	case BOSS_STATE::IDLE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_IDLE;
			reset_Timer();
			displacement.x = 0.f;
				boss_state_ = BOSS_STATE::ATTACKING;
				
			

			break;
		}

	case BOSS_STATE::MOVING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			reset_Timer();
			looks();
			displacement_max = 0.8f;
			if (on_ground)
			{
				if (update_collision_x())
				{
					moving *= -1.f;
					look(moving);
				}
			}
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
			
			if (sting())
			{
				pl_contact_ = true;
				boss_state_ = BOSS_STATE::PUNCH;
			}
			else reset_attention();
			walk(moving);
			break;
		}
	case BOSS_STATE::PUNCH:
		{
			looks();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_PUNCH;
			reset_Timer();
			displacement.x = 0.f;
			if (shot_timer_.getElapsedTime().asSeconds() >= 1.0f)
			{
				boss_state_ = BOSS_STATE::RETREATING;
				shot_timer_.restart();
				if (boss_state_torment_)boss_state_ = BOSS_STATE::DOUBLE_KICK;
			}
			if (shot_timer_.getElapsedTime().asSeconds() >= 0.8F)
			{
				shot();
			}


			break;
		}
	case BOSS_STATE::JUMPING:
		{
			if (animation_state != ENEMY_ANIMATION_STATES::ENEMY_JUMPING)animation_state =
				ENEMY_ANIMATION_STATES::ENEMY_MOVING;

			if (on_ground)
			{
				if (update_collision_x())
				{
					moving *= -1.f;
					look(moving);
				}
			}
			

			if (!pl_cont_jump_)walk(moving);

			if ((std::abs(player_info->getPosition().x - get_position().x) < 8 * 64) && (std::abs(
					player_info->getPosition().x - get_position().x) > 5 * 64)
				&& ((getPlayerSide(player_info->getPosition().x, get_position().x) == PL_SIDE::LEFT &&
						looks_to_the_left) ||
					(getPlayerSide(player_info->getPosition().x, get_position().x) == PL_SIDE::RIGHT &&
						looks_to_the_right)) || pl_cont_jump_)
			{
				animation_state = ENEMY_ANIMATION_STATES::ENEMY_JUMPING;
				reset_Timer();
				if (!pl_cont_jump_ && jumping_att_timer_.getElapsedTime().asSeconds() >= 0.4)boss_state_ = BOSS_STATE::IDLE;
				if (jumping_att_timer_.getElapsedTime().asSeconds() >= 0.2f && !pl_cont_jump_)
				{
					jump(1.7F);

					pl_cont_jump_ = true;
				}
				if (pl_cont_jump_ && on_ground && jumping_att_timer_.getElapsedTime().asSeconds() >= 1.2f)
				{
					shot();
					while (true)
					{
						sf::Vector2f tmp = calculate_random_position(10);
						if (tmp.x / 64 == 0)tmp.x = 64;
						if (tmp.x / 64 == sandbox->getMapWidth() / 64)tmp.x = sandbox->getMapWidth() - 64;
						if (!sandbox->isBlock(tmp.y / 64, tmp.x / 64))
						{
							set_position(tmp.x, tmp.y);
							break;
						}
						else set_position(get_position().x, get_position().y);
					}
					pl_cont_jump_ = false;
					boss_state_ = BOSS_STATE::IDLE;
					jumping_att_timer_.restart();
				}
			}
			else pl_contact_ = true;
			break;
		}
	case BOSS_STATE::TAKING_DAMAGE:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_TAKING_DAMAGE;
			reset_Timer();
			looks();
			boss_state_torment_ = false;

			if (HP <= 0)
			{
				hp_damage_i = HP;
				boss_state_ = BOSS_STATE::DEATH;
				break;
			}
			if (hp_damage_i > HP)
			{
				boss_taking_damage_timer_.restart();
				hp_damage_i = HP;
			}
			if (boss_taking_damage_timer_.getElapsedTime().asSeconds() >= 0.01f)
			{
				boss_state_ = BOSS_STATE::IDLE;
			}

			break;
		}
	case BOSS_STATE::RUN:
		{
			looks();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
			reset_Timer();
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

			displacement_max = 5.f;
			displacement.x *= (displacement_max / 4);
			walk(moving);
			look(displacement.x);
			if (sting())
			{
				boss_state_ = BOSS_STATE::DOUBLE_KICK;
				displacement_max = 0.F;
			}


			break;
		}
	case BOSS_STATE::DOUBLE_KICK:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DOUBLE_KICK;
			reset_Timer();
			displacement.x = 0.f;
			if (shot_timer_.getElapsedTime().asSeconds() >= 1.f)
			{
				boss_state_ = BOSS_STATE::RETREATING;
				shot_timer_.restart();
				if (boss_state_torment_)boss_state_ = BOSS_STATE::PUNCH;
			}
			
				shot();
				shot();
			


			break;
		}
	case BOSS_STATE::ATTACKING:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_ATTENTION;
			reset_Timer();
			if (rand_ == 0)
			{
				rand_++;
				boss_state_ = BOSS_STATE::JUMPING;
			}
			else if (rand_ == 1)
			{
				rand_++;
				boss_state_ = BOSS_STATE::MOVING;
			}
			else if (rand_ == 2)
			{
				rand_++;
				boss_state_ = BOSS_STATE::RUN;
			}
			else if (rand_ == 3)
			{
				rand_++;
				boss_state_ = BOSS_STATE::HOWL;
			}
			else if(rand_ == 4)
			{
				rand_++;
				boss_state_ = BOSS_STATE::TORMENT;
			}else
			{
				rand_ = 0;
				boss_state_ = BOSS_STATE::HIT_EARTH;
			}

			break;
		}


	case BOSS_STATE::RETREATING:
		{

			animation_state = ENEMY_ANIMATION_STATES::ENEMY_MOVING;
			if (update_collision_x())boss_state_ = BOSS_STATE::IDLE;
			reset_Timer();
			const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
			displacement_max = 3.f;
			if (retreating_timer_.getElapsedTime().asSeconds() <= 4.6f)
			{
				if (player_side == PL_SIDE::RIGHT)
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
			if (idle_timer_.getElapsedTime().asSeconds() >= 4.6f)
			{
				displacement_max = 1.f;
				boss_state_ = BOSS_STATE::IDLE;
				idle_timer_.restart();
			}
			walk(moving);
			break;
		}
	case BOSS_STATE::HOWL:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_HOWL;
			reset_Timer();
			looks();
			retreat_counter_++;
			displacement.x = 0; shot_howl();
			if (shot_timer_.getElapsedTime().asSeconds() >= 4.2f)
			{
				
				boss_state_ = BOSS_STATE::IDLE;
				shot_timer_.restart();
			}
			break;
		}
	case BOSS_STATE::TORMENT:

		{
			displacement_max = 7.f;
			displacement.x *= (displacement_max / 4);
			if (update_collision_x())boss_state_ = BOSS_STATE::IDLE;
			const PL_SIDE player_side = getPlayerSide(player_info->getPosition().x, get_position().x);
			if (!sting() && retreat_counter_ == 0)
			{
				if (player_side == PL_SIDE::LEFT)
				{
					looks_to_the_left = true;
					looks_to_the_right = false;
					if (moving > 0)moving *= -1.f;

					walk(moving);
				}
				else
				{
					looks_to_the_left = false;
					looks_to_the_right = true;
					if (moving < 0)moving *= -1.f;
					walk(moving);
				}
			}
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_RUN;
			reset_Timer();
			if (sting())
			{
				displacement_max = 1.F;
				boss_state_torment_ = true;
				boss_state_ = BOSS_STATE::PUNCH;
			}
			walk(moving);
			break;
		}

	case BOSS_STATE::DEATH:
		{
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_DEATH;
			reset_Timer();
			displacement.x = 0;

			break;
		}
	case BOSS_STATE::HIT_EARTH:
		{
			looks();
			animation_state = ENEMY_ANIMATION_STATES::ENEMY_HIT_EARTH;
			reset_Timer();

			displacement.x = 0.f;
			if (shot_timer_.getElapsedTime().asSeconds() >= 1.7f)
			{
				boss_state_ = BOSS_STATE::IDLE;
				shot_timer_.restart();
			}
			if (shot_timer_.getElapsedTime().asSeconds() >= 1.5F)
			{
				shot();
				//ADD: falling stones
			}
			break;
		}
	}

	if (!search_for_enemies() && awakening_)

	{

		if (on_ground)
		{
			if (update_collision_x())
			{
				moving *= -1.f;
				look(moving);
			}
		}
		if (step_right == max_step)
		{
			moving *= -1.f;
			reset_step();
		}
		if (step_left == max_step)
		{
			moving *= -1.f;
			reset_step();
		}

		if (moving > 0)
		{
			looks_to_the_left = true;
			looks_to_the_right = false;
		}
		else
		{
			looks_to_the_left = false;
			looks_to_the_right = true;
		}

		walk(moving);
	}
}


void WolfBoss::look(const float direction)
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

sf::Vector2f WolfBoss::calculate_random_position(const int jump_distance) const
{
	const int x = static_cast<int>(get_position().x / sandbox->getSizeTexture());
	const int y = static_cast<int>(get_position().y / sandbox->getSizeTexture());
	int count = 1000000;

	while (count--)
	{
		const int random_x_offset = rand() % (2 * jump_distance + 1) - jump_distance;
		const int random_y_offset = rand() % (2 * jump_distance + 1) - jump_distance;

		const int new_x = x + random_x_offset;
		const int new_y = y + random_y_offset;


		if (!sandbox->outOfMap(new_y, new_x))
			continue;


		if (sandbox->isBlock(new_y, new_x))
			continue;


		if (sandbox->outOfMap(new_y + 2, new_x) && !sandbox->isBlock(new_y + 2, new_x))
			continue;
		if (sandbox->outOfMap(new_y + 1, new_x) && sandbox->isBlock(new_y + 1, new_x))
			continue;
		return {new_x * sandbox->getSizeTexture(), new_y * sandbox->getSizeTexture()};
	}

	return get_position();
}

void WolfBoss::bite()
{
	animation_state = ENEMY_ANIMATION_STATES::ENEMY_BITE;
}

void WolfBoss::reset_step()
{
	step_left = 0;
	step_right = 0;
	pl_contact_ = false;
}


void WolfBoss::shot()
{
	if(att_timer_.getElapsedTime().asSeconds()>=0.9f)
	{
		if ((outside_sting() || sting()) && boss_state_ == BOSS_STATE::DOUBLE_KICK)player_info->changeHP(-attack_ - (rand() % 10) -attack_);
		else if (outside_sting() || sting())player_info->changeHP(-attack_ - (rand() % 10));
		att_timer_.restart();
	}
	
}

void WolfBoss::attack()
{

	displacement_max = 10.f;
	displacement.x += moving * displacement_max;
}

void WolfBoss::clear_shot()
{
}

bool WolfBoss::search_for_enemies()
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

void WolfBoss::reset_attention()
{
	displacement_max = 2.5f;
	displacement.x += moving * acceleration;
}

void WolfBoss::walk(const float dir_x)
{
	
	
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

	if (displacement.x != 0.0f) { look(displacement.x); }
	
}


void WolfBoss::update_physics()
{
	// gravity
	displacement.y += 1.f * gravity;
	if (std::abs(displacement.y) > velocity_max_y)
	{
		displacement.y = velocity_max_y * ((displacement.y > 0.f) ? 1.f : -1.f);
	}
	//jumping


	if (jump_tile)
	{
		displacement.y -= jump_velocity;
		//jumping onto a block

		displacement.x = 2 * moving * displacement_max;
		//jump deceleratin
		jump_velocity *= 0.96f;
	}
	// deceleration
	displacement *= deceleration;

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
	if ((displacement.x > 0 && pl_contact_) || !pl_cont_jump_)
		step_right++;
	if ((displacement.x < 0 && pl_contact_) || !pl_cont_jump_)
		step_left++;
	Enemy_S.move(displacement);
	set_position(get_position().x, get_position().y);
}


void WolfBoss::jump(const float dir_y)
{
	if (on_ground)
	{
		on_ground = false;
		jump_tile = true;
		jump_velocity = dir_y * 5.5f;
	}
}

void WolfBoss::shot_howl() const
{
	player_info->setStanTime(5.6f);
}
