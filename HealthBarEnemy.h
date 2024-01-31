#pragma once

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;


class HealthBarEnemy
{
private:
	Texture HealthBarEnemy_t_;
	Sprite HealthBarEnemy_S_;

	IntRect standard_frame;

	Clock manifestation_timer;

	short HP_S;
	short HP_cur;
	short HP_PREV;
	float procent;


	void init_texture() ;
	void init_sprite() ;


public:
	
	explicit HealthBarEnemy();
	~HealthBarEnemy()= default;

	void set_position(const float x, const float y);
	void update_animation();
	void reset_Timer();
	void setHP_cur(short);
	void update(Sprite);
	void SET_ST_HP(short HP);
	void render(sf::RenderTarget& target);

};

