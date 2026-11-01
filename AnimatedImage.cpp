#include "stdafx.h"
#include "AnimatedImage.h"

	AnimatedImage::AnimatedImage(TextureManager* t_manager, Warehouse* w_object, string name)
	: BasicImage(t_manager, w_object, name){
		current_frame = w_object->getWarehouseItem(name)->getSpriteInfo().first;
		frames_number = w_object->getWarehouseItem(name)->getSpriteInfo().second;
	}
	
	AnimatedImage::AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_)
		: BasicImage(t_manager, index, name, first_frame)
		, frames_number(frames_number_), current_frame(first_frame){
		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(first_frame);
		animation_timer.restart();
	}

	void AnimatedImage::update(Vector2f mouse_pos, FloatRect view_cords){
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f) {
			current_frame.position.x += current_frame.size.x;
			if (current_frame.position.x >= frames_number * current_frame.size.x) {
				current_frame.position.x = 0;
			}
			animation_timer.restart();
			image.setTextureRect(current_frame);
			image.setPosition(sf::Vector2f(position.x + view_cords.position.x - view_cords.size.x / 2, position.y + view_cords.position.y - view_cords.size.y / 2));
		}
	}

	void AnimatedImage::render(RenderTarget* target){
		target->draw(image);
	}
