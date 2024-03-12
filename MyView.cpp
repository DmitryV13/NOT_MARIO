#include "stdafx.h"
#include "MyView.h"

MyView::MyView(TileMap& map, double screenWidth_, double screenHeight_)
	:absoluteRight(map.getMapWidth())
	, absoluteBottom(map.getMapHeight())
	, absoluteLeft(0.0f)
	, absoluteTop(0.0f)
	, windowRight(screenWidth_)
	, windowBottom(screenHeight_)
	, windowLeft(0.0f)
	, windowTop(0)
	, screenWidth(screenWidth_)
	, screenHeight(screenHeight_) {
	view.reset(FloatRect(0, 0, screenWidth_, screenHeight_));
	viewScreen.width = 400;
	viewScreen.height = 250;
	viewScreen.left = windowLeft + (screenWidth - viewScreen.width) / 2;
	viewScreen.top = windowTop + ((screenHeight - viewScreen.height) / 2);
}

void MyView::updateView(FloatRect coordinates) {
	updateLeft(coordinates.left);
	updateRight(coordinates.left + coordinates.width);
	updateTop(coordinates.top);
	updateBottom(coordinates.top + coordinates.height);
}

void MyView::updateLeft(double left) {
	double offset = (viewScreen.left - left);
	if (offset > 0) {
		if (windowLeft - offset > absoluteLeft) {
			viewScreen.left -= offset;
			windowRight -= offset;
			windowLeft -= offset;
		}
		else {
			offset = windowLeft - 1;
			viewScreen.left -= offset;
			windowRight -= offset;
			windowLeft -= offset;
		}
	}
	else {
		offset = 0;
	}
	view.move(-offset, 0);
}

void MyView::updateRight(double right) {
	double offset = (right - (viewScreen.left + viewScreen.width));
	if (offset > 0) {
		if (windowRight + offset < absoluteRight) {
			viewScreen.left += offset;
			windowRight += offset;
			windowLeft += offset;
		}
		else {
			offset = absoluteRight - windowRight - 1;
			viewScreen.left += offset;
			windowRight += offset;
			windowLeft += offset;
		}
	}
	else {
		offset = 0;
	}
	view.move(offset, 0);
}

void MyView::updateTop(double top) {
	double offset = viewScreen.top - top;
	if (offset > 0) {
		if (windowTop - offset > absoluteTop) {
			viewScreen.top -= offset;
			windowTop -= offset;
			windowBottom -= offset;
		}
		else {
			offset = windowTop-1;
			viewScreen.top -= offset;
			windowTop -= offset;
			windowBottom -= offset;
		}
	}
	else {
		offset = 0;
	}
	view.move(0, -offset);
}

void MyView::updateBottom(double bottom) {
	double offset = bottom - (viewScreen.top + viewScreen.height);
	if (offset > 0) {
		if (windowBottom + offset < absoluteBottom) {
			viewScreen.top += offset;
			windowTop += offset;
			windowBottom += offset;
		}
		else {
			offset = absoluteBottom-windowBottom-1;
			viewScreen.top += offset;
			windowTop += offset;
			windowBottom += offset;
		}
	}
	else {
		offset = 0;
	}
	view.move(0, offset);
}

FloatRect MyView::getCurrentViewCords() {
	return FloatRect(view.getCenter(), Vector2f(screenWidth, screenHeight));
}