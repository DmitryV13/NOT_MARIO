#include "stdafx.h"
#include "TextureManager.h"

	TextureManager::TextureManager(){
		//single
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[0]["Transparent"].loadFromFile("Textures/GUI/popup/void.png")) {
			std::cout << "Error -> TextureManager -> couldn't load void texture" << std::endl;
		}
		if (!textures[0]["LobbyBackground"].loadFromFile("Textures/GUI/lobby0.png")) {
			std::cout << "Error -> TextureManager -> couldn't load LobbyBackground texture" << std::endl;
		}
		if (!textures[0]["ArrowL"].loadFromFile("Textures/GUI/buttons/arrowL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ArrowL texture" << std::endl;
		}
		if (!textures[0]["ArrowR"].loadFromFile("Textures/GUI/buttons/arrowR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ArrowR texture" << std::endl;
		}
		if (!textures[0]["ArrowBack"].loadFromFile("Textures/GUI/buttons/arrowBack.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ArrowBack texture" << std::endl;
		}
		if (!textures[0]["B"].loadFromFile("Textures/GUI/b.png")) {
			std::cout << "Error -> TextureManager -> couldn't load B texture" << std::endl;
		}
		if (!textures[0]["Coin"].loadFromFile("Textures/GUI/resources/coin.png")) {
			std::cout << "Error -> TextureManager -> couldn't load Coin texture" << std::endl;
		}
		if (!textures[0]["BSplinter"].loadFromFile("Textures/GUI/resources/blueSplinter.png")) {
			std::cout << "Error -> TextureManager -> couldn't load blueSplinter texture" << std::endl;
		}
		if (!textures[0]["RSplinter"].loadFromFile("Textures/GUI/resources/redSplinter.png")) {
			std::cout << "Error -> TextureManager -> couldn't load redSplinter texture" << std::endl;
		}
		if (!textures[0]["Arrow1"].loadFromFile("Textures/Weapons/arrow1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load Arrow1 texture" << std::endl;
		}

		//label 1 (6)
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[1]["Filler"].loadFromFile("Textures/GUI/popup/labelF.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelFiller texture" << std::endl;
		}
		if (!textures[1]["TopRight"].loadFromFile("Textures/GUI/popup/labelTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelTopRight texture" << std::endl;
		}
		if (!textures[1]["TopLeft"].loadFromFile("Textures/GUI/popup/labelTL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelTopLeft texture" << std::endl;
		}
		if (!textures[1]["BottomRight"].loadFromFile("Textures/GUI/popup/labelBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelBottomRight texture" << std::endl;
		}
		if (!textures[1]["BottomLeft"].loadFromFile("Textures/GUI/popup/labelBL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load labelBottomLeft texture" << std::endl;
		}

		//popup 1 (6)
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[2]["Filler"].loadFromFile("Textures/GUI/popup/popUpF.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpFiller texture" << std::endl;
		}
		if (!textures[2]["TopRight"].loadFromFile("Textures/GUI/popup/popUpTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpTopRight texture" << std::endl;
		}
		if (!textures[2]["TopLeft"].loadFromFile("Textures/GUI/popup/popUpTL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpTopLeft texture" << std::endl;
		}
		if (!textures[2]["BottomRight"].loadFromFile("Textures/GUI/popup/popUpBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpBottomRight texture" << std::endl;
		}
		if (!textures[2]["BottomLeft"].loadFromFile("Textures/GUI/popup/popUpBL.png")) {
			std::cout << "Error -> TextureManager -> couldn't load popUpBottomLeft texture" << std::endl;
		}

		//slider 1 (2)
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[3]["TopLeft"].loadFromFile("Textures/GUI/popup/sliderScaleTLBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sliderScaleTLBR texture" << std::endl;
		}
		if (!textures[3]["TopRight"].loadFromFile("Textures/GUI/popup/sliderScaleBLTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sliderScaleBLTR texture" << std::endl;
		}
		if (!textures[3]["BottomRight"].loadFromFile("Textures/GUI/popup/sliderScaleTLBR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sliderScaleTLBR texture" << std::endl;
		}
		if (!textures[3]["BottomLeft"].loadFromFile("Textures/GUI/popup/sliderScaleBLTR.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sliderScaleBLTR texture" << std::endl;
		}

		//player images
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[4]["Hero1"].loadFromFile("Textures/Heroes/hero1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load Hero1 texture" << std::endl;
		}
		if (!textures[4]["Hero2"].loadFromFile("Textures/Heroes/hero2.png")) {
			std::cout << "Error -> TextureManager -> couldn't load Hero2 texture" << std::endl;
		}

		//potions
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[5]["ManaPotion"].loadFromFile("Textures/Textures_map/mana_potion.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ManaPotion texture" << std::endl;
		}
		if (!textures[5]["HealthPotion"].loadFromFile("Textures/Textures_map/health_potion.png")) {
			std::cout << "Error -> TextureManager -> couldn't load HealthPotion texture" << std::endl;
		}
		if (!textures[5]["PoisonPotion"].loadFromFile("Textures/Textures_map/poison_potion.png")) {
			std::cout << "Error -> TextureManager -> couldn't load PoisonPotion texture" << std::endl;
		}
		if (!textures[5]["SpeedPotion"].loadFromFile("Textures/Textures_map/speed_potion.png")) {
			std::cout << "Error -> TextureManager -> couldn't load SpeedPotion texture" << std::endl;
		}
	}

	Texture& TextureManager::getTexture(int index, string name)
	{
		return textures[index][name];
	}
