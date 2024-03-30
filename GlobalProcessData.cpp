#include "stdafx.h"
#include "GlobalProcessData.h"
	RenderWindow* GlobalProcessData::window = nullptr;
	FloatRect GlobalProcessData::view_cords = FloatRect(0,0,0,0);

	void GlobalProcessData::setViewCords(FloatRect new_cords){
		view_cords = new_cords;
	}

	void GlobalProcessData::setWindow(RenderWindow* new_window){
		window = new_window;
	}
	
	FloatRect GlobalProcessData::getViewCords(){
		return view_cords;
	}
	
	Vector2i GlobalProcessData::getMousePos(){
		return Mouse::getPosition(*window);
	}

	RenderWindow* GlobalProcessData::getWindow(){
		return window;
	}
