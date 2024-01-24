#pragma once
#include "Enemy.h"

enum class EYE_EVIL_STATE
{
	IDLE = 0,
	MOVING,
	JUMPING,
	ATTACKING,
	DEATH,
	TAKING_DAMAGE
};

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;

class EyeEvil : public Enemy
{
public:
	EYE_EVIL_STATE eye_state;
	EYE_EVIL_STATE eye_state_past;
	Clock IDLE_timer;
	Clock DEATH_timer;
	Clock ATTACKING_timer;

	bool jump_flag{true};


	//vector<laser_weapon> laser;
	laser_weapon* laser{nullptr};
	laser_weapon* laserFL{nullptr};
	explicit EyeEvil(TileMap& map, GeneralInfo* player_info);
	~EyeEvil() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void draw_laser(int, sf::RenderTarget&);
	bool laser_existence();
	void walk(const float dir_x) override;
	//int laser_length();
	void reset_Timer();
	void changeHP(short) override;
	 void updateHP_bar() override;


private:
	Texture evil_ball_t_;
	void init_texture() override;
	void init_sprite() override;
};
