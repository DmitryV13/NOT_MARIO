#include "stdafx.h"
#include "ScaleParametrBar.h"


	ScaleParametrBar::ScaleParametrBar(){
		initTexture();
		initSprite();
	}
	
	ScaleParametrBar::~ScaleParametrBar(){

	}


	
	void ScaleParametrBar::initTexture(){
		if (!bar_T.loadFromFile("Textures/GUI/lifeScale.png")) {
			std::cout << "Error -> Menu -> couldn't load menu texture" << std::endl;
		}
		front_bar = IntRect(0, 0, 158, 20);
		middle_bar = IntRect(5, 26, 146, 8);
		back_bar = IntRect(5, 46, 146, 8);
	}
	
	void ScaleParametrBar::initSprite(){
		bar_S.setTexture(bar_T);
		bar_S.setScale(2., 2.);
	}

	void ScaleParametrBar::update(FloatRect view_cords, double screenWidth, double screenHeight){
		bar_S.setPosition(view_cords.left - screenWidth/2 + 15, view_cords.top - screenHeight/2 + 15);
	}

	void ScaleParametrBar::updateScaleWidth(short new_width){
		middle_bar.width = static_cast<float>(new_width) / 1000 * 146;
	}

	void ScaleParametrBar::render(RenderTarget* target){
		bar_S.setTextureRect(back_bar);
		bar_S.setPosition(bar_S.getPosition().x + 6* bar_S.getScale().x, bar_S.getPosition().y + 6 * bar_S.getScale().y);
		target->draw(bar_S);
		bar_S.setTextureRect(middle_bar);
		target->draw(bar_S);
		bar_S.setTextureRect(front_bar);
		bar_S.setPosition(bar_S.getPosition().x - 6 * bar_S.getScale().x, bar_S.getPosition().y - 6 * bar_S.getScale().y);
		target->draw(bar_S);
	}