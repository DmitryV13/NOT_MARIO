#pragma once
#include "TextureManager.h"

using namespace::sf;

class AnimatedImage{
private:
	Sprite image;
	IntRect current_frame;
	short frames_number;
	short scale;
	Clock animation_timer;
	Vector2f position;
public:
	AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_);

	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();

	void setPosition(float x, float y);
	void setScale(float scale_);

	void update();
	void render(RenderTarget* target);
};

