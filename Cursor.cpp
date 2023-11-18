#include "stdafx.h"
#include "Cursor.h"

Cursor::Cursor(){
	initTexture();
	initSprite();
}

void Cursor::initTexture(){
	if (!cursor_T.loadFromFile("Textures/cursor1.png")) {
		std::cout << "Error -> Cursor -> couldn't load cursor texture" << std::endl;
	}
}

void Cursor::initSprite(){
    cursor_S.setTexture(cursor_T);
    currentFrame = IntRect(0, 0, 14, 14);
    cursor_S.setTextureRect(currentFrame);
}

void Cursor::update(sf::Vector2f position){
	cursor_S.setPosition(position.x, position.y);
}

void Cursor::render(sf::RenderTarget& target){
	target.draw(cursor_S);
}
