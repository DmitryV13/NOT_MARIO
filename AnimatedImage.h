#pragma once
#include "BasicImage.h"

using namespace::sf;

class AnimatedImage : public BasicImage{
private:
	IntRect current_frame;
	short frames_number;
	Clock animation_timer;
public:
	AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target);
};

