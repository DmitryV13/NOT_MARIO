#pragma once
#include "BasicImage.h"

using namespace::sf;

class AnimatedImage : public BasicImage{
private:
	IntRect current_frame;
	short frames_number;
	Clock animation_timer;
public:
	AnimatedImage(TextureManager* t_manager, Warehouse* w_object, string name);
	AnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_);

	void update() override;
	void render();
};

