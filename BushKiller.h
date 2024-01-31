#pragma once
#include "Enemy.h"
#include "BUSH_KILLER_STATE.h"




class BushKiller: public Enemy
{
	BUSH_KILLER_STATE bush_state_;
	BUSH_KILLER_STATE bush_state_past_;

	Texture bush_killer_t_;

	Clock bush_taking_damage_timer_;
	Clock shot_timer_;
	Clock death_timer_;
	Clock leaf_spawn_;
	vector<killer_leaf*>killer_leaf_sh_;
	GeneralInfo* player_info_;

	void init_texture() override;
	void init_sprite() override;
	void init_physics() override;

public:
	explicit BushKiller(TileMap& map, GeneralInfo* player_info,short);
	BushKiller(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);

	void draw_leaf(sf::RenderTarget& target) const;
	void look(float direction);
	void reset_Timer();
	void looks();
	void clear_leaf();
	bool leaf_empty() const;
	void update_life() const;

	~BushKiller() override = default;
	void update_movement() override;
	void attack() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void walk(const float dir_x) override;
	void update_physics() override;
	void jump(const float dir_y) override;
	bool outside_sting() override;
	void changeHP(short) override;
	




};
