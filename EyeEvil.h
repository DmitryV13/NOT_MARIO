#pragma once
#include "Enemy.h"
#include "EYE_EVIL_STATE.h"


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

	Clock idle_timer;
	Clock death_timer;
	Clock attacking_timer;

	bool jump_flag{true};

	laser_weapon* laser{nullptr};
	laser_weapon* laser_fl{nullptr};
	GeneralInfo* player_info;


	explicit EyeEvil(TileMap& map, GeneralInfo* player_info,short);
	EyeEvil(TileMap& map, GeneralInfo* player_info_, float, float);
	void reset_timer();
	void draw_laser(int, sf::RenderTarget&) const;
	bool laser_existence() const;



	~EyeEvil() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;
	void changeHP(short) override;
	void updateHP_bar() override;


private:
	Texture evil_ball_t_;
	void init_texture() override;
	void init_sprite() override;
};
