#pragma once

using namespace::sf;

class GeneralInfo{
private:
	int HP;
	const int max_HP;
	int mana;
	int max_mana;
	float stan_time;
	bool mana_is_used;
	FloatRect globalBounds;
	Vector2f position;
	Vector2f velocity;
public:
	GeneralInfo(int HP_, int mana_);

	const Vector2f getVelocity() const;
	const short getHP() const;
	int* getHp();
	int* getMana();
	int getMaxMana();
	const int getMaxHP();
	const FloatRect getGlobalBounds() const;
	const Vector2f getPosition() const;
	float getStanTime();

	void changeVelocityX(float x);
	void changeVelocityY(float y);
	bool changeMana(int x);

	void setVelocityX(float x);
	void setVelocityY(float y);
	void setStanTime(float new_st);
	void setGlobalBounds(FloatRect new_gb);
	void setPosition(Vector2f new_position);
	void setManaUtilisation(bool used);

	void changeHP(short z);
	bool isManaUsed();
};