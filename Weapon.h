#pragma once

using namespace::sf;

class Weapon{
public:
	virtual void update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords);
	virtual void updateProjectiles();

	virtual void render(RenderTarget& target);
	virtual void renderProjectiles(RenderTarget& target);

	virtual void attack(short side_attack, Vector2f mouse_pos, FloatRect view_cord);
};

