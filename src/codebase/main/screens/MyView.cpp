#include "stdafx.h"
#include "screens/MyView.h"

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
	view = sf::View(sf::FloatRect(
		{ 0.f, 0.f },
		{ static_cast<float>(screenWidth_), static_cast<float>(screenHeight_) }
	));
	viewScreen.size.x = 400;
	viewScreen.size.y = 250;
	viewScreen.position.x = windowLeft + (screenWidth - viewScreen.size.x) / 2;
	viewScreen.position.y = windowTop + ((screenHeight - viewScreen.size.y) / 2);
}

// calculation is based on players' global bounds
void MyView::updateView(FloatRect coordinates) {
	updateLeft(coordinates.position.x);
	updateRight(coordinates.position.x + coordinates.size.x);
	updateTop(coordinates.position.y);
	updateBottom(coordinates.position.y + coordinates.size.y);
}

void MyView::updateLeft(double left) {
	double offset = viewScreen.position.x - left;
	if (offset > 0) {
		if (windowLeft - offset > absoluteLeft) {
			viewScreen.position.x -= offset;
			windowRight -= offset;
			windowLeft -= offset;
		}
		else {
			offset = 0;
			windowLeft = absoluteLeft;
			windowRight = absoluteLeft + screenWidth;
			viewScreen.position.x = windowLeft + (screenWidth - viewScreen.size.x) / 2;
			view = sf::View(sf::FloatRect(
				{ static_cast<float>(windowLeft), static_cast<float>(windowTop) },
				{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) }
			));
		}
	}
	else {
		offset = 0;
	}
	view.move(sf::Vector2f(-offset, 0));
}

void MyView::updateRight(double right) {
	double offset = right - (viewScreen.position.x + viewScreen.size.x);
	if (offset > 0) {
		if (windowRight + offset < absoluteRight) {
			viewScreen.position.x += offset;
			windowRight += offset;
			windowLeft += offset;
		}
		else {
			offset = 0;
			windowRight = absoluteRight;
			windowLeft = absoluteRight - screenWidth;
			viewScreen.position.x = windowLeft + (screenWidth - viewScreen.size.x) / 2;
			view = sf::View(sf::FloatRect(
				{ static_cast<float>(windowLeft), static_cast<float>(windowTop) },
				{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) }
			));
		}
	}
	else {
		offset = 0;
	}
	view.move(sf::Vector2f(offset, 0));
}

void MyView::updateTop(double top) {
	double offset = viewScreen.position.y - top;
	if (offset > 0) {
		if (windowTop - offset > absoluteTop) {
			viewScreen.position.y -= offset;
			windowTop -= offset;
			windowBottom -= offset;
		}
		else {
			offset = 0;
			windowTop = absoluteTop;
			windowBottom = absoluteTop + screenHeight;
			viewScreen.position.y = windowTop + (screenHeight - viewScreen.size.y) / 2;
			view = sf::View(sf::FloatRect(
				{ static_cast<float>(windowLeft), static_cast<float>(windowTop) },
				{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) }
			));
		}
	}
	else {
		offset = 0;
	}
	view.move(sf::Vector2f(0, -offset));
}

void MyView::updateBottom(double bottom) {
	double offset = bottom - (viewScreen.position.y + viewScreen.size.y);
	if (offset > 0) {
		if (windowBottom + offset < absoluteBottom) {
			viewScreen.position.y += offset;
			windowTop += offset;
			windowBottom += offset;
		}
		else {
			offset = 0;
			windowTop = absoluteBottom - screenHeight;
			windowBottom = absoluteBottom;
			viewScreen.position.y = windowTop + (screenHeight - viewScreen.size.y) / 2;
			view = sf::View(sf::FloatRect(
				{ static_cast<float>(windowLeft), static_cast<float>(windowTop) },
				{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) }
			));
		}
	}
	else {
		offset = 0;
	}
	view.move(sf::Vector2f(0, offset));
}

FloatRect MyView::getCurrentViewCords() {
	return FloatRect(view.getCenter(), Vector2f(screenWidth, screenHeight));
}