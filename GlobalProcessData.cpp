#include "stdafx.h"
#include "GlobalProcessData.h"
	RenderWindow* GlobalProcessData::window = nullptr;
	FloatRect GlobalProcessData::view_cords = FloatRect(0,0,0,0);
	Font* GlobalProcessData::font = new Font();

	void GlobalProcessData::setFont(Font* font_){
		font = font_;
	}

	void GlobalProcessData::setViewCords(FloatRect new_cords){
		view_cords = new_cords;
	}

	void GlobalProcessData::setWindow(RenderWindow* new_window){
		window = new_window;
	}
	
	Font* GlobalProcessData::getFont(){
		return font;
	}

	FloatRect GlobalProcessData::getViewCords(){
		return view_cords;
	}
	
	Vector2f GlobalProcessData::getMousePos(){
		return Vector2f(Mouse::getPosition(*window));
	}

	RenderWindow* GlobalProcessData::getWindow(){
		return window;
	}
