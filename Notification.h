#pragma once

using namespace::sf;

class Notification{
private:
	Text text;
	bool active;
	Vector2f position;
	Vector2f norm_s;
	Clock display_time;
public:
	Notification(float x, float y, float dest_x, float dest_y, short text_size, string text_, Color text_color);
	Notification(FloatRect object_cords, short text_size, string text_, Color text_color);

	void activation(float q);

	void update();
	void updateDT();
	void render();
};

