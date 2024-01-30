#include "stdafx.h"
#include "ComposedIMG.h"

	ComposedIMG::ComposedIMG(int width_, int height_, int original_size, TextureManager* manager, int index)
		: width(width_), height(height_), origin_size(original_size), scale(1){
		filler.setTexture(manager->getTexture(index, "Filler"));
		cornerTopLeft.setTexture(manager->getTexture(index, "TopLeft"));
		cornerTopRight.setTexture(manager->getTexture(index, "TopRight"));
		cornerBottomLeft.setTexture(manager->getTexture(index, "BottomLeft"));
		cornerBottomRight.setTexture(manager->getTexture(index, "BottomRight"));
	
		cornerTopLeft.setTextureRect(IntRect(0, 0, origin_size + width, origin_size + height));
		cornerTopRight.setTextureRect(IntRect(0, 0, origin_size, origin_size + height));
		cornerBottomRight.setTextureRect(IntRect(0, 0, origin_size, origin_size));
		cornerBottomLeft.setTextureRect(IntRect(0, 0, origin_size + width, origin_size));
		filler.setTextureRect(IntRect(0, 0, width, height));
	}

	ComposedIMG::ComposedIMG(int width_, int height_, int original_size, TextureManager* manager
		, int index_0, string name_0, int index_1, string name_1, int index_2, string name_2
		, int index_3, string name_3, int index_4, string name_4)
		: width(width_), height(height_), origin_size(original_size), scale(1) {
		filler.setTexture(manager->getTexture(index_0, name_0));
		cornerTopLeft.setTexture(manager->getTexture(index_1, name_1));
		cornerTopRight.setTexture(manager->getTexture(index_2, name_2));
		cornerBottomLeft.setTexture(manager->getTexture(index_3, name_3));
		cornerBottomRight.setTexture(manager->getTexture(index_4, name_4));

		cornerTopLeft.setTextureRect(IntRect(0, 0, origin_size + width, origin_size + height));
		cornerTopRight.setTextureRect(IntRect(0, 0, origin_size, origin_size + height));
		cornerBottomRight.setTextureRect(IntRect(0, 0, origin_size, origin_size));
		cornerBottomLeft.setTextureRect(IntRect(0, 0, origin_size + width, origin_size));
		filler.setTextureRect(IntRect(0, 0, width, height));
	}
	
	void ComposedIMG::setPosition(int x, int y){
		offsetX = x - origin_size;
		offsetY = y - origin_size;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + origin_size, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + origin_size);
		cornerBottomRight.setPosition(offsetX + width + origin_size, offsetY + height + origin_size);
		filler.setPosition(offsetX + origin_size, offsetY + origin_size);
	}
	
	void ComposedIMG::setPosition(string positionX, string positionY, int screen_width, int screen_height){
		if (positionX == "center") {
			offsetX = (screen_width - width + origin_size*2) / 2;
		}
		if (positionY == "center") {
			offsetY = (screen_height - height + origin_size*2) / 2;
		}

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + origin_size, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + origin_size);
		cornerBottomRight.setPosition(offsetX + width + origin_size, offsetY + height + origin_size);
		filler.setPosition(offsetX + origin_size, offsetY + origin_size);
	}

	void ComposedIMG::setPosition(string positionX, int y, int screen_width, int screen_height){
		if (positionX == "center") {
			offsetX = (screen_width - width + origin_size*2) / 2;
		}
		offsetY = y - origin_size;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + origin_size, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + origin_size);
		cornerBottomRight.setPosition(offsetX + width + origin_size, offsetY + height + origin_size);
		filler.setPosition(offsetX + origin_size, offsetY + origin_size);
	}

	void ComposedIMG::setPosition(int x, string positionY, int screen_width, int screen_height){
		if (positionY == "center") {
			offsetY = (screen_height - height + origin_size*2) / 2;
		}
		offsetX = x - origin_size;

		cornerTopLeft.setPosition(offsetX, offsetY);
		cornerTopRight.setPosition(offsetX + width + origin_size, offsetY);
		cornerBottomLeft.setPosition(offsetX, offsetY + height + origin_size);
		cornerBottomRight.setPosition(offsetX + width + origin_size, offsetY + height + origin_size);
		filler.setPosition(offsetX + origin_size, offsetY + origin_size);
	}

	void ComposedIMG::setScale(float scale_){
		scale = scale_;
		filler.setScale(Vector2f(scale, scale));
		cornerTopLeft.setScale(Vector2f(scale, scale));
		cornerTopRight.setScale(Vector2f(scale, scale));
		cornerBottomLeft.setScale(Vector2f(scale, scale));
		cornerBottomRight.setScale(Vector2f(scale, scale));
	}

	FloatRect ComposedIMG::getLocalBounds(){
		return FloatRect(cornerTopLeft.getPosition().x + origin_size, cornerTopLeft.getPosition().y + origin_size, width, height);
	}

	FloatRect ComposedIMG::getGlobalBounds(){
		return FloatRect(cornerTopLeft.getPosition().x, cornerTopLeft.getPosition().y, width + origin_size*2, height + origin_size*2);
	}
	
	void ComposedIMG::update(FloatRect view_cords){
		cornerTopLeft.setPosition(view_cords.left - view_cords.width/2 + offsetX, view_cords.top - view_cords.height/2 + offsetY);
		cornerTopRight.setPosition(view_cords.left - view_cords.width/2 + offsetX + width + origin_size, view_cords.top - view_cords.height/2 + offsetY);
		cornerBottomLeft.setPosition(view_cords.left - view_cords.width/2 + offsetX, view_cords.top - view_cords.height/2 + offsetY + height + origin_size);
		cornerBottomRight.setPosition(view_cords.left - view_cords.width/2 + offsetX + width + origin_size, view_cords.top - view_cords.height/2 + offsetY + height + origin_size);
		filler.setPosition(view_cords.left - view_cords.width/2 + offsetX + origin_size, view_cords.top - view_cords.height/2 + offsetY + origin_size);
	}
	
	void ComposedIMG::render(RenderTarget* target){
		target->draw(cornerTopLeft);
		target->draw(cornerTopRight);
		target->draw(cornerBottomLeft);
		target->draw(cornerBottomRight);
		target->draw(filler);
	}


