#pragma once
#include "Enemy.h"

class Eye_evil : public Enemy
{
public:
	
	//vector<laser_weapon> laser;
	laser_weapon* laser{nullptr};
	laser_weapon* laserFL{nullptr};
	explicit Eye_evil(TileMap& map, GeneralInfo* player_info);
	~Eye_evil() override = default;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void draw_laser(int, sf::RenderTarget&);
	bool laser_existence();
	//int laser_length();

private:

	Texture evil_ball_t_;
	void init_texture() override;
	void init_sprite() override;

};
