#pragma once

using namespace::sf;

class GeneralInfo{
private:
	short HP;
	float stan_time;
	FloatRect globalBounds;
	Vector2f position;
	Vector2f velocity;
public:
	GeneralInfo(short HP_);

	const Vector2f getVelocity() const;
	const short getHP() const;
	const FloatRect getGlobalBounds() const;
	const Vector2f getPosition() const;
	float getStanTime();

	void changeVelocityX(float x);
	void changeVelocityY(float y);

	void setVelocityX(float x);
	void setVelocityY(float y);
	void setStanTime(float new_st);
	void setGlobalBounds(FloatRect new_gb);
	void setPosition(Vector2f new_position);

	void changeHP(short z);
};