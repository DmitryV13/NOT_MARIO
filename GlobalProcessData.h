#pragma once

class GlobalProcessData {
private:
	static RenderWindow* window;
	static FloatRect view_cords;
	static Font* font;
	static int id_accumulator;
public:
	static void setFont(Font* font_);
	static void setViewCords(FloatRect new_cords);
	static void setWindow(RenderWindow* new_window);

	static int getUnicId();
	static Font* getFont();
	static FloatRect getViewCords();
	static Vector2f getMousePos();
	static RenderWindow* getWindow();
};


