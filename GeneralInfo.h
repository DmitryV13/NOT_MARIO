#pragma once

using namespace::sf;

class GeneralInfo{
private:
	float HP;
	const float max_HP;
	float mana;
	float max_mana;
	float stan_time;
	bool mana_is_used;
	FloatRect globalBounds;
	Vector2f position;
	Vector2f velocity;
public:
	GeneralInfo(int HP_, int mana_);

	const Vector2f getVelocity() const;
	const float getHP() const;
	float* getHp();
	float* getMana();
	float getMaxMana();
	const float getMaxHP();
	const FloatRect getGlobalBounds() const;
	const Vector2f getPosition() const;
	float getStanTime();

	void changeVelocityX(float x);
	void changeVelocityY(float y);
	bool changeMana(float x);

	void setVelocityX(float x);
	void setVelocityY(float y);
	void setStanTime(float new_st);
	void setGlobalBounds(FloatRect new_gb);
	void setPosition(Vector2f new_position);
	void setManaUtilisation(bool used);

	void changeHP(short z);
	bool isManaUsed();
};