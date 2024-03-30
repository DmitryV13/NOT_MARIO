#pragma once

class GlobalProcessData {
private:
	static RenderWindow* window;
	static FloatRect view_cords;
public:
	static void setViewCords(FloatRect new_cords);
	static void setWindow(RenderWindow* new_window);

	static FloatRect getViewCords();
	static Vector2i getMousePos();
	static RenderWindow* getWindow();
};


