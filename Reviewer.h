#pragma once
#include "AnimatedImage.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class Reviewer : public InterfaceItem{
private:
	short current_image;
	vector<AnimatedImage*> images;
	float scale;
	float max_width;
	float max_height;
	Vector2f position;
public:
	Reviewer(float width, float height, Vector2f position_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void addAnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_);
	void setPosition(Vector2f position_);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

	void changeCurrentImage(float next);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target) override;
};

