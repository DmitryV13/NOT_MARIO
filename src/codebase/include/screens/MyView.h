#pragma once

#include "map/TileMap.h"

using namespace::sf;

class MyView{
private:
	// characteristics of the map
	double absoluteLeft;
	double absoluteTop;
	double absoluteRight;
	double absoluteBottom;

	// characteristics of the displayed window
	double windowLeft;
	double windowTop;
	double windowRight;
	double windowBottom;

	double screenWidth;
	double screenHeight;

	// zero screen movement area for player
	FloatRect viewScreen;
public:
	View view;

	MyView(TileMap& map, double screenWidth_, double screenHeight_);

	void updateView(FloatRect coordinates);
	void updateLeft(double left);
	void updateRight(double right);
	void updateTop(double top);
	void updateBottom(double bottom);

	FloatRect getCurrentViewCords();
};
