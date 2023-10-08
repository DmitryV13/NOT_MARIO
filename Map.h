#pragma once
#include <string>
#ifndef MAP_H
#define MAP_H

using std::string;
using std::swap;

class Map{
public:
	const int Height;
	const int Width;
	int sizeTexture;
	string* TileMap;

	Map(int Height, int Width, int sizeTexture, string* TileMap);
};

#endif