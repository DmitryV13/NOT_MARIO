#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>
#ifndef MYVIEW_H
#define MYVIEW_H

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

	MyView(Map map, double windowRight_, double windowBottom_, double screenWidth_, double screenHeight_);
	void updateView(FloatRect coordinates);
	void updateLeft(double left);
	void updateRight(double right);
	void updateTop(double top);
	void updateBottom(double bottom);
};

#endif