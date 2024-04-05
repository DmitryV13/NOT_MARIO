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

	ComposedIMG::~ComposedIMG(){
	}
	
	void ComposedIMG::setPosition(float x, float y){
		position.x = x - origin_size;
		position.y = y - origin_size;

		cornerTopLeft.setPosition(position.x, position.y);
		cornerTopRight.setPosition(position.x + width + origin_size, position.y);
		cornerBottomLeft.setPosition(position.x, position.y + height + origin_size);
		cornerBottomRight.setPosition(position.x + width + origin_size, position.y + height + origin_size);
		filler.setPosition(position.x + origin_size, position.y + origin_size);
	}
	
	void ComposedIMG::setPosition(string positionX, string positionY, int screen_width, int screen_height){
		if (positionX == "center") {
			position.x = (screen_width - width + origin_size*2) / 2;
		}
		if (positionY == "center") {
			position.y = (screen_height - height + origin_size*2) / 2;
		}

		cornerTopLeft.setPosition(position.x, position.y);
		cornerTopRight.setPosition(position.x + width + origin_size, position.y);
		cornerBottomLeft.setPosition(position.x, position.y + height + origin_size);
		cornerBottomRight.setPosition(position.x + width + origin_size, position.y + height + origin_size);
		filler.setPosition(position.x + origin_size, position.y + origin_size);
	}

	void ComposedIMG::setPosition(string positionX, float y, int screen_width, int screen_height){
		if (positionX == "center") {
			position.x = (screen_width - width + origin_size*2) / 2;
		}
		position.y = y - origin_size;

		cornerTopLeft.setPosition(position.x, position.y);
		cornerTopRight.setPosition(position.x + width + origin_size, position.y);
		cornerBottomLeft.setPosition(position.x, position.y + height + origin_size);
		cornerBottomRight.setPosition(position.x + width + origin_size, position.y + height + origin_size);
		filler.setPosition(position.x + origin_size, position.y + origin_size);
	}

	void ComposedIMG::setPosition(float x, string positionY, int screen_width, int screen_height){
		if (positionY == "center") {
			position.y = (screen_height - height + origin_size*2) / 2;
		}
		position.x = x - origin_size;

		cornerTopLeft.setPosition(position.x, position.y);
		cornerTopRight.setPosition(position.x + width + origin_size, position.y);
		cornerBottomLeft.setPosition(position.x, position.y + height + origin_size);
		cornerBottomRight.setPosition(position.x + width + origin_size, position.y + height + origin_size);
		filler.setPosition(position.x + origin_size, position.y + origin_size);
	}

	void ComposedIMG::changePosition(float offset_x, float offset_y){
		position.x += offset_x;
		position.y += offset_y;
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
	
	void ComposedIMG::update(){
		FloatRect view_cords = GlobalProcessData::getViewCords();

		cornerTopLeft.setPosition(view_cords.left - view_cords.width/2 + position.x, view_cords.top - view_cords.height/2 + position.y);
		cornerTopRight.setPosition(view_cords.left - view_cords.width/2 + position.x + width + origin_size, view_cords.top - view_cords.height/2 + position.y);
		cornerBottomLeft.setPosition(view_cords.left - view_cords.width/2 + position.x, view_cords.top - view_cords.height/2 + position.y + height + origin_size);
		cornerBottomRight.setPosition(view_cords.left - view_cords.width/2 + position.x + width + origin_size, view_cords.top - view_cords.height/2 + position.y + height + origin_size);
		filler.setPosition(view_cords.left - view_cords.width/2 + position.x + origin_size, view_cords.top - view_cords.height/2 + position.y + origin_size);
	}
	
	void ComposedIMG::render(){
		RenderTarget* target = GlobalProcessData::getWindow();

		target->draw(cornerTopLeft);
		target->draw(cornerTopRight);
		target->draw(cornerBottomLeft);
		target->draw(cornerBottomRight);
		target->draw(filler);
	}


