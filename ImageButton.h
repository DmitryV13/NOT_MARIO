#pragma once
#include "Button.h"

using namespace::sf;

class ImageButton : public Button{
private:
	Sprite* btn_image;
	const string name;
public:
	ImageButton(float x, float y, float width, float height, short text_size, sf::Font* font_
		, string text_, TextureManager* t_manager, int index, string name_, bool outline, int id_);

	void setPosition(Vector2f new_position) override;

	void updatePosition(FloatRect view_cords) override;
	void render(sf::RenderTarget* target) override;
};

