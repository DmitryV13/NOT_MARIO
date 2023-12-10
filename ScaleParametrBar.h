#pragma once

using namespace sf;

class ScaleParametrBar{
private:
	Texture bar_T;
	Sprite bar_S;

	IntRect front_bar;
	IntRect middle_bar;
	IntRect back_bar;

	void initTexture();
	void initSprite();
public:
	ScaleParametrBar();
	~ScaleParametrBar();

	void update(FloatRect view_cords, double screenWidth, double screenHeight);
	void updateScaleWidth(short new_width);
	void render(RenderTarget* target);
};

