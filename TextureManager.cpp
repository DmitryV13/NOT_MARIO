#include "stdafx.h"
#include "TextureManager.h"

	TextureManager::TextureManager(){
		//label
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[0]["Filler"].loadFromFile("Textures/GUI/popup/labelF.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelFiller texture" << std::endl;
		}
		if (!textures[0]["TopRight"].loadFromFile("Textures/GUI/popup/labelTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelTopRight texture" << std::endl;
		}
		if (!textures[0]["TopLeft"].loadFromFile("Textures/GUI/popup/labelTL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelTopLeft texture" << std::endl;
		}
		if (!textures[0]["BottomRight"].loadFromFile("Textures/GUI/popup/labelBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelBottomRight texture" << std::endl;
		}
		if (!textures[0]["BottomLeft"].loadFromFile("Textures/GUI/popup/labelBL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelBottomLeft texture" << std::endl;
		}

		//popup
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[1]["Filler"].loadFromFile("Textures/GUI/popup/popUpF.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpFiller texture" << std::endl;
		}
		if (!textures[1]["TopRight"].loadFromFile("Textures/GUI/popup/popUpTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpTopRight texture" << std::endl;
		}
		if (!textures[1]["TopLeft"].loadFromFile("Textures/GUI/popup/popUpTL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpTopLeft texture" << std::endl;
		}
		if (!textures[1]["BottomRight"].loadFromFile("Textures/GUI/popup/popUpBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpBottomRight texture" << std::endl;
		}
		if (!textures[1]["BottomLeft"].loadFromFile("Textures/GUI/popup/popUpBL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpBottomLeft texture" << std::endl;
		}

	}

	Texture& TextureManager::getTexture(int number, string name)
	{
		return textures[number][name];
	}
