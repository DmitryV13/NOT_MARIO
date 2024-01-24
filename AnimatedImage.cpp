#include "stdafx.h"
#include "AnimatedImage.h"

	AnimatedImage::AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_)
		: BasicImage(t_manager, index, name, first_frame)
		, frames_number(frames_number_), current_frame(first_frame){
		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(first_frame);
		animation_timer.restart();
	}

	void AnimatedImage::update(Vector2f mouse_pos, FloatRect view_cords){
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f) {
			current_frame.left += current_frame.width;
			if (current_frame.left >= frames_number * current_frame.width) {
				current_frame.left = 0;
			}
			animation_timer.restart();
			image.setTextureRect(current_frame);
			image.setPosition(
				position.x + view_cords.left - view_cords.width / 2,
				position.y + view_cords.top - view_cords.height / 2
			);
		}
	}

	void AnimatedImage::render(RenderTarget* target){
		target->draw(image);
	}
