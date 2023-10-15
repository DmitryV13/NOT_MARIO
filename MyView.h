#pragma once

#include "Map.h"

using sf::View;
using sf::FloatRect;

class MyView{
private:
	// characteristics of map
	double absoluteLeft;
	double absoluteTop;
	double absoluteRight;
	double absoluteBottom;

	// characteristics of window
	double windowLeft;
	double windowTop;
	double windowRight;
	double windowBottom;

	double screenWidth;
	double screenHeight;

	FloatRect viewScreen;
public:
	View view;

	MyView(double windowRight_, double windowBottom_, double screenWidth_, double screenHeight_);
	void updateView(FloatRect coordinates);
	void updateLeft(double left);
	void updateRight(double right);
	void updateTop(double top);
	void updateBottom(double bottom);
};