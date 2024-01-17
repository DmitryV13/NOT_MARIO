#pragma once
#include "Enemy.h"

enum class RED_MUTANT_STATE
{
	RED_MUTANT_IDLE = 0,
	RED_MUTANT_MOVING,
	RED_MUTANT_JUMPING,
	RED_MUTANT_SHOT,
	RED_MUTANT_DEATH,
	RED_MUTANT_TAKING_DAMAGE,
	RED_MUTANT_RUN,
	RED_MUTANT_ATTACKING,
	RED_MUTANT_TELEPORT
};

class RedMutant: public Enemy{
private:
	Texture chubacabra_t_;

	RED_MUTANT_STATE red_mutant_state;
	RED_MUTANT_STATE red_mutant_state_past;
	Clock IDLE_timer;
	Clock DEATH_timer;
	Clock RED_MUTANT_TAKING_DAMAGE_TIMER;

	bool jump_flag{ true };
	short count_jm;
	bool player_l_r[2]{ false };
	int count_jump = 0;
	int count_atack = 0;
	void init_texture() override;
	void init_sprite() override;

public:
	
	sf::Vector2f calculateRandomPosition(const sf::FloatRect& playerBounds, int radius);
	explicit RedMutant(TileMap& map, GeneralInfo* player_info);

	~RedMutant() override = default;
	void reset_Timer();

	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;

	bool plStan();
};

