#pragma once
#include "AnimatedImage.h"
#include "InterfaceItem.h"
#include "INTERFACE_ITEM_TYPE.h"

using namespace::sf;

class Reviewer : public InterfaceItem{
private:
	short current_image;
	vector<BasicImage*> images;
	float scale;
	float max_width;
	float max_height;
	Vector2f position;
public:
	Reviewer(float x, float y, float width_, float height_);

	FloatRect getLocalBounds() override;
	FloatRect getGlobalBounds() override;

	void addAnimatedImage(TextureManager* t_manager, int index, string name, IntRect first_frame, short frames_number_);
	void addAnimatedImage(TextureManager* t_manager, Warehouse* w_object, string name);
	void addStaticImage(TextureManager* t_manager, int index, string name, IntRect first_frame);
	void addStaticImage(TextureManager* t_manager, Warehouse* w_object, string name);
	void setPosition(Vector2f position_);
	void setPositionX(float x) override;
	void setPositionY(float y) override;

	void changePosition(float offset_x, float offset_y) override;

	void changeCurrentImage(float next);

	void update(Vector2f mouse_pos, FloatRect view_cords) override;
	void render(RenderTarget* target) override;
};

