#include "stdafx.h"
#include "PopUpWindow.h"


PopUpWindow::PopUpWindow(double screen_width, double screen_height, int width_, int height_, int text_size, Font* font_, string label_text, RenderWindow* window_)
		:width(width_), height(height_), font(font_), window(window_){
		label.setFont(*font);
		label.setString(label_text);
		label.setFillColor(sf::Color::White);
		label.setCharacterSize(text_size);
		label.setOutlineThickness(3.f);
		label.setOutlineColor(sf::Color(0, 0, 0, 0));

		initBTexture();
		initBSprite();
		background_S.setPosition((screen_width - width) / 2, (screen_height - height) / 2);

		initLTexture();
		initLSprite();
		label_S.setPosition((screen_width - label_S.getLocalBounds().width) / 2, (screen_height - height) / 2 - label_S.getLocalBounds().height);
	}
	
	PopUpWindow::~PopUpWindow(){
	}

	void PopUpWindow::initLSprite(){
		label_S.setTexture(label_T);
		label_S.setTextureRect(IntRect(0, 0, 100, 50));
	}

	void PopUpWindow::initLTexture(){
		if (!label_T.loadFromFile("Textures/GUI/windowPopUpB.png")) {
			std::cout << "Error -> PopUpWindow -> couldn't load texture" << std::endl;
		}
	}

	void PopUpWindow::initBSprite(){
		background_S.setTexture(background_T);
		background_S.setTextureRect(IntRect(0, 0, width, height));
	}

	void PopUpWindow::initBTexture(){
		if (!background_T.loadFromFile("Textures/GUI/popUpLabel.png")) {
			std::cout << "Error -> PopUpWindow -> Label -> couldn't load texture" << std::endl;
		}
	}
	
	void PopUpWindow::setBackground(){
	}
	
	void PopUpWindow::setSize(){
	}
	
	void PopUpWindow::addWButton(){
	}
	
	void PopUpWindow::addNWButton(){
	}
	
	void PopUpWindow::addDelimiter(){
	}
	
	void PopUpWindow::verifyBtnsPressed(){
	}
	
	void PopUpWindow::update(FloatRect view_cords){
		background_S.setPosition(view_cords.left + (view_cords.width - width) / 2, view_cords.top + (view_cords.height - height) / 2);
		label_S.setPosition(view_cords.left + (view_cords.width - label_S.getLocalBounds().width) / 2, view_cords.top + (view_cords.height - height) / 2 - label_S.getLocalBounds().height);
	}
	
	void PopUpWindow::render(){
		window->draw(background_S);
		//window->draw(label_S);
	}
