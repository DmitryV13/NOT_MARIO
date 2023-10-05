//#pragma once
//
//#ifndef PLAYER_H
//#define PLAYER_H
//
//#include "Map.h"
//#include <SFML/Graphics.hpp>
//using sf::Sprite;
//using sf::RenderWindow;
//using sf::Vector2f;
//using sf::View;
//using sf::Texture;
//
//class Player
//{
//public:
//    // characteristics of map
//    float absoluteLeft;
//    float absoluteTop;
//    float absoluteRight;
//    float absoluteBottom;
//
//    // characteristics of window
//    float windowLeft;
//    float windowTop;
//    float windowRight;
//    float windowBottom;
//
//    // window characteristics
//    const int screenHeight;
//    const int screenWidth;
//
//    // Map
//    //Map map;
//
//    // player
//    Sprite player_S;
//    float playerSpeed;
//
//    Player(Texture hero_T, const float mapW, const float mapH, const float size_texture, const float sH, const float sW);
//	void moveRight(RenderWindow& window, View& view);
//	void moveLeft(RenderWindow& window, View& view);
//	void moveUp(RenderWindow& window, View& view);
//	void moveDown(RenderWindow& window, View& view);
//};
//
//#endif