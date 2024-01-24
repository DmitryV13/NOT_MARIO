#pragma once
#include "Enemy.h"

enum class BUSH_KILLER_STATE
{
	SLEEP,
	MOVING,
	SHOT,
	PUNCH,
	DEATH,
	TAKING_DAMAGE,
	IDLE,
	AWAKENING
};



class BushKiller: public Enemy
{
	BUSH_KILLER_STATE bush_state;
	BUSH_KILLER_STATE bush_state_past;
	Texture bush_killer_t_;
	Clock BUSH_TAKING_DAMAGE_TIMER;
	Clock Shot_timer;
	Clock DEATH_timer;
	Clock leaf_spawn;
	vector<killer_leaf*>killer_leaf_SH;
	//killer_leaf* killer_leaf_SH{ nullptr };



	void init_texture() override;
	void init_sprite() override;
	void init_physics() override;

public:
	explicit BushKiller(TileMap& map, GeneralInfo* player_info);
	~BushKiller() override = default;
	void update_movement() override;
	void look(float direction);
	void attack() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;
	void update_physics() override;
	void jump(const float dir_y) override;
	void reset_Timer();
	bool outside_sting() override;
	void looks();
	void changeHP(short) override;
	void draw_leaf( sf::RenderTarget& target);
	void clear_leaf();
	bool leaf_empty();
	void update_life();




};
