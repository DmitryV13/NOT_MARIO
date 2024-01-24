#include "stdafx.h"
#include "HealthBarEnemy.h"

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
	standard_frame = IntRect(0, 0, 90, 13);
	HealthBarEnemy_S_.setTextureRect(standard_frame);
}

void HealthBarEnemy::set_position(const float x, const float y)
{
	HealthBarEnemy_S_.setPosition(x, y);
}

HealthBarEnemy::HealthBarEnemy()
{
	HealthBarEnemy::init_texture();
	HealthBarEnemy::init_sprite();
	procent = 0.083f;
	manifestation_timer.restart();
}


void HealthBarEnemy::update_animation()
{
	if (HP_cur != HP_PREV)
	{
		float healthPercentage = static_cast<float>(HP_cur) / HP_S * 100.0f;
		float healthChange = HP_PREV - HP_cur;

		if (healthPercentage>=8.3)
		{
			
			standard_frame.top += 13;
			standard_frame.left = 0.f;
			standard_frame.height = 13.f;
			standard_frame.width = 90.f;

			HealthBarEnemy_S_.setTextureRect(standard_frame);
			manifestation_timer.restart();


			HP_PREV = HP_cur;
		}
		
	}
	HealthBarEnemy_S_.setTextureRect(standard_frame);
	manifestation_timer.restart();
}

void HealthBarEnemy::reset_Timer()
{
	manifestation_timer.restart();
}

void HealthBarEnemy::setHP_cur(short HP)
{
	HP_cur = HP;
}

void HealthBarEnemy::update(Sprite sp_en)
{
	HealthBarEnemy_S_.setPosition(
		sp_en.getPosition().x - (HealthBarEnemy_S_.getGlobalBounds().width - (HealthBarEnemy_S_.getGlobalBounds().width
			/ 2) - (sp_en.
			        getGlobalBounds().width / 2)),
		(sp_en.getPosition().y - (HealthBarEnemy_S_.getGlobalBounds().height)));

	update_animation();
}

void HealthBarEnemy::SET_ST_HP(short HP)
{
	HP_S = HP_PREV = HP_cur = HP;
}

void HealthBarEnemy::render(sf::RenderTarget& target)
{
	target.draw(HealthBarEnemy_S_);
}
