#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Player* player;

	double screenWidth;
	double screenHeight;

	void initWindow();
	void initPlayer();
public:
	Game(double screenWidth_, double screenHeight_);
	~Game();

	const sf::RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void updateCollision();
	void renderPLayer();
	void render();
};

