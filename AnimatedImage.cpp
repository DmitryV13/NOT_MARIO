#include "stdafx.h"
#include "AnimatedImage.h"

	AnimatedImage::AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_)
		:current_frame(first_frame), frames_number(frames_number_){
		image.setTexture(t_manager->getTexture(index, name));
		image.setTextureRect(first_frame);
		animation_timer.restart();
	}

	FloatRect AnimatedImage::getLocalBounds(){
		return image.getLocalBounds();
	}

	FloatRect AnimatedImage::getGlobalBounds(){
		return image.getGlobalBounds();
	}
	
	void AnimatedImage::setPosition(float x, float y){
		position.x = x;
		position.y = y;
		image.setPosition(position);
	}
	
	void AnimatedImage::setScale(float scale_){
		scale = scale_;
		image.setScale(scale, scale);
	}

	void AnimatedImage::update(){
		if (animation_timer.getElapsedTime().asSeconds() >= 0.2f) {
			current_frame.left += current_frame.width;
			if (current_frame.left >= frames_number * current_frame.width) {
				current_frame.left = 0;
			}
			animation_timer.restart();
			image.setTextureRect(current_frame);
		}
	}

	void AnimatedImage::render(RenderTarget* target){
		target->draw(image);
	}
