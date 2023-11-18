#pragma once
class MainMenu{
public:
	MainMenu(float width, float heught);
	~MainMenu();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int mainMenuPressed();
private:
	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[4];
	bool interaction_available;
};

