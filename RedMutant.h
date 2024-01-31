#pragma once
#include "Enemy.h"
#include "RED_MUTANT_STATE.h"



class RedMutant : public Enemy
{
private:
	Texture chubacabra_t_;

	Clock idle_timer_;
	Clock red_mutant_taking_damage_timer_;
	Clock shot_timer_;

	bool teleport_{true};
	bool jump_flag_{true};
	bool player_l_r_[2]{ false };

	short count_jm_;
	short count_anim_{0};

	int count_jump_ = 0;
	int count_attack_ = 0;
	GeneralInfo* player_info_;

	void init_texture() override;
	void init_sprite() override;

public:
	RED_MUTANT_STATE red_mutant_state;
	RED_MUTANT_STATE red_mutant_state_past;

	Clock DEATH_timer;


	sf::Vector2f calculate_random_position(const sf::FloatRect& playerBounds, int radius) const;
	explicit RedMutant(TileMap& map, GeneralInfo* player_info,short);
	RedMutant(TileMap& map, GeneralInfo* player_info_, float pos_x, float pos_y);
	void reset_timer();
	bool pl_stan() const;


	~RedMutant() override = default;
	void walk(const float dir_x) override;
	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;
	void changeHP(short) override;
	void updateHP_bar() override;

};
