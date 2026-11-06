#include "stdafx.h"
#include "units/enemies/HealthBarEnemy.h"

void HealthBarEnemy::init_texture()
{
	if (!HealthBarEnemy_t_.loadFromFile("Textures/Enemies/HP_STAND_ENEMY.png"))
	{
		std::cout << "Error -> HP_STAND_ENEMY -> couldn't load HP_STAND_ENEMY texture" << std::endl;
	}
}

void HealthBarEnemy::init_sprite()
{
	HealthBarEnemy_S_.setTexture(HealthBarEnemy_t_);
	standard_frame = IntRect(sf::Vector2i(0, 0), sf::Vector2i(90, 13));
	HealthBarEnemy_S_.setTextureRect(standard_frame);
}

void HealthBarEnemy::set_position(const float x, const float y)
{
	HealthBarEnemy_S_.setPosition(sf::Vector2f(x, y));
}

HealthBarEnemy::HealthBarEnemy()
{
	HealthBarEnemy::init_texture();
	HealthBarEnemy::init_sprite();
	procent = 0.0833333333f;
	manifestation_timer.restart();
}


void HealthBarEnemy::update_animation()
{
	if (HP_cur != HP_PREV)
	{
		reset_Timer();
		float hp_pot = HP_S - HP_cur;

		float healthPercentage = hp_pot / HP_S;;

		while (healthPercentage > procent)
		{
			procent += 0.0833333333f;
			standard_frame.position.y += 14;
			standard_frame.position.x = 0.f;
			standard_frame.size.y = 14.f;
			standard_frame.size.x = 90.f;

			HealthBarEnemy_S_.setTextureRect(standard_frame);
		}

		HP_PREV = HP_cur;

		
	}


}

void HealthBarEnemy::reset_Timer()
{
	manifestation_timer.restart();
}

void HealthBarEnemy::setHP_cur(short HP)
{
	HP_cur = HP;
}

void HealthBarEnemy::update(FloatRect sp_en)
{
	HealthBarEnemy_S_.setPosition(sf::Vector2f(sp_en.position.x - (HealthBarEnemy_S_.getGlobalBounds().size.x - (HealthBarEnemy_S_.getGlobalBounds().size.x
			/ 2) - (sp_en.size.x / 2)), (sp_en.position.y - (HealthBarEnemy_S_.getGlobalBounds().size.y))));

	update_animation();
}

void HealthBarEnemy::SET_ST_HP(short HP)
{
	HP_S = HP_PREV = HP_cur = HP;
}

void HealthBarEnemy::render(sf::RenderTarget& target)
{
	if(HP_cur!=HP_S && manifestation_timer.getElapsedTime().asSeconds()<=4.f)target.draw(HealthBarEnemy_S_);
}
