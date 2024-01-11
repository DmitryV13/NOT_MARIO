#pragma once
#include "Enemy.h"

class RedMutant: public Enemy{
private:
	Texture chubacabra_t_;
	bool player_l_r[2]{ false };
	int count_jump = 0;
	int count_atack = 0;
	void init_texture() override;
	void init_sprite() override;

public:
	
	sf::Vector2f calculateRandomPosition(const sf::FloatRect& playerBounds, int radius);
	explicit RedMutant(TileMap& map, GeneralInfo* player_info);

	~RedMutant() override = default;

	void update_movement() override;
	void update_animation() override;
	void clear_shot() override;
	void shot() override;
	void attack() override;
	bool search_for_enemies() override;
	void reset_attention() override;

	bool plStan();
};

