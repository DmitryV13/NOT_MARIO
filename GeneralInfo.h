#pragma once

using namespace::sf;

class GeneralInfo{
private:
	FloatRect globalBounds;
	Vector2f position;
	Vector2f velocity;
	short HP;
public:
	GeneralInfo(short HP_);

	const Vector2f getVelocity() const;
	const short getHP() const;
	const FloatRect getGlobalBounds() const;
	const Vector2f getPosition() const;

	void changeVelocityX(float x);
	void changeVelocityY(float y);
	void setVelocityX(float x);
	void setVelocityY(float y);
	void changeHP(short z);
	void setGlobalBounds(FloatRect new_gb);
	void setPosition(Vector2f new_position);
};