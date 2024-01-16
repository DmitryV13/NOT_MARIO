#include "stdafx.h"
#include "ComposedIMG.h"

	ComposedIMG::ComposedIMG(int width_, int height_, TextureManager* manager, int index): width(width_), height(height_){
		filler.setTexture(manager->getTexture(index, "Filler"));
		cornerTopLeft.setTexture(manager->getTexture(index, "TopLeft"));
		cornerTopRight.setTexture(manager->getTexture(index, "TopRight"));
		cornerBottomLeft.setTexture(manager->getTexture(index, "BottomLeft"));
		cornerBottomRight.setTexture(manager->getTexture(index, "BottomRight"));
	
		cornerTopLeft.setTextureRect(IntRect(0, 0, 6 + width, 6 + height));
		cornerTopRight.setTextureRect(IntRect(0, 0, 6, 6 + height));
		cornerBottomRight.setTextureRect(IntRect(0, 0, 6, 6));
		cornerBottomLeft.setTextureRect(IntRect(0, 0, 6 + width, 6));
		filler.setTextureRect(IntRect(0, 0, width, height));
	}
	
	void ComposedIMG::setPosition(int x, int y){
		offsetX = x - 6;
		offsetY = y - 6;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + 6, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + 6);
		cornerBottomRight.setPosition(offsetX + width + 6, offsetY + height + 6);
		filler.setPosition(offsetX + 6, offsetY + 6);
	}
	
	void ComposedIMG::setPosition(string positionX, string positionY, int screen_width, int screen_height){
		if (positionX == "center") {
			offsetX = (screen_width - width + 12) / 2;
		}
		if (positionY == "center") {
			offsetY = (screen_height - height + 12) / 2;
		}

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + 6, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + 6);
		cornerBottomRight.setPosition(offsetX + width + 6, offsetY + height + 6);
		filler.setPosition(offsetX + 6, offsetY + 6);
	}

	void ComposedIMG::setPosition(string positionX, int y, int screen_width, int screen_height){
		if (positionX == "center") {
			offsetX = (screen_width - width + 12) / 2;
		}
		offsetY = y - 6;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + 6, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + 6);
		cornerBottomRight.setPosition(offsetX + width + 6, offsetY + height + 6);
		filler.setPosition(offsetX + 6, offsetY + 6);
	}

	void ComposedIMG::setPosition(int x, string positionY, int screen_width, int screen_height){
		if (positionY == "center") {
			offsetY = (screen_height - height + 12) / 2;
		}
		offsetX = x - 6;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + 6, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + 6);
		cornerBottomRight.setPosition(offsetX + width + 6, offsetY + height + 6);
		filler.setPosition(offsetX + 6, offsetY + 6);
	}

	FloatRect ComposedIMG::getLocalBounds(){
		return FloatRect(cornerTopLeft.getPosition().x + 6, cornerTopLeft.getPosition().y + 6, width, height);
	}

	FloatRect ComposedIMG::getGlobalBounds(){
		return FloatRect(cornerTopLeft.getPosition().x, cornerTopLeft.getPosition().y, width + 12, height + 12);
	}
	
	void ComposedIMG::update(FloatRect view_cords){
		cornerTopLeft.setPosition(view_cords.left - view_cords.width/2 + offsetX, view_cords.top - view_cords.height/2 + offsetY);
		cornerTopRight.setPosition(view_cords.left - view_cords.width/2 + offsetX + width + 6, view_cords.top - view_cords.height/2 + offsetY);
		cornerBottomLeft.setPosition(view_cords.left - view_cords.width/2 + offsetX, view_cords.top - view_cords.height/2 + offsetY + height + 6);
		cornerBottomRight.setPosition(view_cords.left - view_cords.width/2 + offsetX + width + 6, view_cords.top - view_cords.height/2 + offsetY + height + 6);
		filler.setPosition(view_cords.left - view_cords.width/2 + offsetX + 6, view_cords.top - view_cords.height/2 + offsetY + 6);
	}
	
	void ComposedIMG::render(RenderTarget* target){
		target->draw(cornerTopLeft);
		target->draw(cornerTopRight);
		target->draw(cornerBottomLeft);
		target->draw(cornerBottomRight);
		target->draw(filler);
	}


