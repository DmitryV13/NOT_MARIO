#include "stdafx.h"
#include "RoadMap.h"

	RoadMap::RoadMap(double screen_w, double screen_h): screen_height(screen_h), screen_width(screen_w){
	}

	void RoadMap::enter(RenderWindow* window){
		Level* level = new Level(window, screen_width, screen_height);
		// level selection

		level->start();
	}