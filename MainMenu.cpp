#include "stdafx.h"
#include "MainMenu.h"

	MainMenu::MainMenu(float width, float heught){
		if (!font.loadFromFile("Fonts/Cruiser.ttf")) {
			std::cout<< "Error -> MainMenu -> couldn't load font" << std::endl;
		}

		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(sf::Color::White);
		mainMenu[0].setString("Play");
		mainMenu[0].setCharacterSize(70);
		mainMenu[0].setPosition(400, 200);

		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(sf::Color::White);
		mainMenu[1].setString("Options");
		mainMenu[1].setCharacterSize(70);
		mainMenu[1].setPosition(400, 300);

		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(sf::Color::White);
		mainMenu[2].setString("About");
		mainMenu[2].setCharacterSize(70);
		mainMenu[2].setPosition(400, 400);

		mainMenu[3].setFont(font);
		mainMenu[3].setFillColor(sf::Color::White);
		mainMenu[3].setString("Exit");
		mainMenu[3].setCharacterSize(70);
		mainMenu[3].setPosition(400, 500);

		mainMenuSelected = -1;
	}
	
	MainMenu::~MainMenu(){
	}
	
	void MainMenu::draw(sf::RenderWindow& window){
		for (int i = 0; i < 4; i++){
			window.draw(mainMenu[i]);
		}
	}
	
	void MainMenu::moveUp(){
		if (mainMenuSelected - 1 >= -1) {
			mainMenu[mainMenuSelected].setFillColor(sf::Color::White);

			mainMenuSelected--;
			if (mainMenuSelected == -1) {
				mainMenuSelected = 3;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
		}
	}
	
	void MainMenu::moveDown(){
		if (mainMenuSelected + 1 <= 4) {
			mainMenu[mainMenuSelected].setFillColor(sf::Color::White);

			mainMenuSelected++;
			if (mainMenuSelected == 4) {
				mainMenuSelected = 0;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
		}
	}
	
	int MainMenu::mainMenuPressed(){
		return mainMenuSelected;
	}
	