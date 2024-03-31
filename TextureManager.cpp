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
		if (!textures[0]["CloseB"].loadFromFile("Textures/GUI/buttons/closeB.png")) {
			std::cout << "Error -> TextureManager -> couldn't load CloseB texture" << std::endl;
		}
		if (!textures[0]["EyeB"].loadFromFile("Textures/GUI/buttons/eyeB.png")) {
			std::cout << "Error -> TextureManager -> couldn't load eyeB texture" << std::endl;
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
		if (!textures[0]["projectile1"].loadFromFile("Textures/Weapons/projectile1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load projectile1 texture" << std::endl;
		}
		if (!textures[0]["RedScaleBar"].loadFromFile("Textures/GUI/scales/redScale.png")) {
			std::cout << "Error -> TextureManager -> couldn't load RedScaleBar texture" << std::endl;
		}
		if (!textures[0]["BlueScaleBar"].loadFromFile("Textures/GUI/scales/blueScale.png")) {
			std::cout << "Error -> TextureManager -> couldn't load BlueScaleBar texture" << std::endl;
		}
		if (!textures[0]["hp_enemy_bar"].loadFromFile("Textures/Enemies/HP_STAND_ENEMY.png")) {
			std::cout << "Error -> TextureManager -> couldn't load hp_enemy_bar texture" << std::endl;
		}

		//label 1 (6)  Textures/Enemies/HP_STAND_ENEMY.png"
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

		//tiles
		////basic
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[6]["grass_tile"].loadFromFile("Textures/Textures_map/grass_tile.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile texture" << std::endl;
		}
		if (!textures[6]["grass_tile_on_the_left"].loadFromFile("Textures/Textures_map/grass_tile_on_the_left.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_on_the_left texture" << std::endl;
		}
		if (!textures[6]["grass_tile_on_the_right"].loadFromFile("Textures/Textures_map/grass_tile_on_the_right.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_on_the_right texture" << std::endl;
		}
		if (!textures[6]["grass_tile_in_corner_left"].loadFromFile("Textures/Textures_map/grass_tile_in_corner_left.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_in_corner_left texture" << std::endl;
		}
		if (!textures[6]["grass_tile_in_corner_right"].loadFromFile("Textures/Textures_map/grass_tile_in_corner_right.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_in_corner_right texture" << std::endl;
		}
		if (!textures[6]["earth"].loadFromFile("Textures/Textures_map/earth.png")) {
			std::cout << "Error -> TextureManager -> couldn't load earth texture" << std::endl;
		}
		if (!textures[6]["sand"].loadFromFile("Textures/Textures_map/sand.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sand texture" << std::endl;
		}
		if (!textures[6]["gravel"].loadFromFile("Textures/Textures_map/gravel.png")) {
			std::cout << "Error -> TextureManager -> couldn't load gravel texture" << std::endl;
		}
		if (!textures[6]["ground8"].loadFromFile("Textures/Textures_map/ground8.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ground8 texture" << std::endl;
		}
		if (!textures[6]["ground7"].loadFromFile("Textures/Textures_map/ground7.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ground7 texture" << std::endl;
		}
		if (!textures[6]["water_top_layer"].loadFromFile("Textures/Textures_map/water_top_layer.png")) {
			std::cout << "Error -> TextureManager -> couldn't load water_top_layer texture" << std::endl;
		}
		if (!textures[6]["water_down_layer"].loadFromFile("Textures/Textures_map/water_down_layer.png")) {
			std::cout << "Error -> TextureManager -> couldn't load water_down_layer texture" << std::endl;
		}

		////functional and decorative
		if (!textures[6]["ladder1"].loadFromFile("Textures/Textures_map/ladder1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ladder1 texture" << std::endl;
		}
		if (!textures[6]["ladder2"].loadFromFile("Textures/Textures_map/ladder2.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ladder2 texture" << std::endl;
		}
		if (!textures[6]["ladder3"].loadFromFile("Textures/Textures_map/ladder3.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ladder3 texture" << std::endl;
		}
		if (!textures[6]["ladder4"].loadFromFile("Textures/Textures_map/ladder4.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ladder4 texture" << std::endl;
		}
		if (!textures[6]["ladder5"].loadFromFile("Textures/Textures_map/ladder5.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ladder5 texture" << std::endl;
		}
		if (!textures[6]["directionSign1"].loadFromFile("Textures/Textures_map/directionSign1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load directionSign1 texture" << std::endl;
		}
		if (!textures[6]["directionSign2"].loadFromFile("Textures/Textures_map/directionSign2.png")) {
			std::cout << "Error -> TextureManager -> couldn't load directionSign2 texture" << std::endl;
		}
		if (!textures[6]["box"].loadFromFile("Textures/Textures_map/box.png")) {
			std::cout << "Error -> TextureManager -> couldn't load box texture" << std::endl;
		}
		if (!textures[6]["tree1"].loadFromFile("Textures/Textures_map/tree1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load tree1 texture" << std::endl;
		}
		if (!textures[6]["tree2"].loadFromFile("Textures/Textures_map/tree2.png")) {
			std::cout << "Error -> TextureManager -> couldn't load tree2 texture" << std::endl;
		}
		if (!textures[6]["tree3"].loadFromFile("Textures/Textures_map/tree3.png")) {
			std::cout << "Error -> TextureManager -> couldn't load tree3 texture" << std::endl;
		}
		if (!textures[6]["tree4"].loadFromFile("Textures/Textures_map/tree4.png")) {
			std::cout << "Error -> TextureManager -> couldn't load tree4 texture" << std::endl;
		}
		if (!textures[6]["cactus1"].loadFromFile("Textures/Textures_map/cactus1.png")) {
			std::cout << "Error -> TextureManager -> couldn't load cactus1 texture" << std::endl;
		}
		if (!textures[6]["cactus2"].loadFromFile("Textures/Textures_map/cactus2.png")) {
			std::cout << "Error -> TextureManager -> couldn't load cactus2 texture" << std::endl;
		}

		////animated
		if (!textures[6]["spikes"].loadFromFile("Textures/Textures_map/spikes.png")) {
			std::cout << "Error -> TextureManager -> couldn't load spikes texture" << std::endl;
		}
		if (!textures[6]["magma"].loadFromFile("Textures/Textures_map/magma.png")) {
			std::cout << "Error -> TextureManager -> couldn't load magma texture" << std::endl;
		}
		if (!textures[6]["health_potion"].loadFromFile("Textures/Textures_map/health_potion.png")) {
			std::cout << "Error -> TextureManager -> couldn't load health_potion texture" << std::endl;
		}

		////background
		if (!textures[6]["grass_tile_back"].loadFromFile("Textures/Textures_map/grass_tile_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_back texture" << std::endl;
		}
		if (!textures[6]["grass_tile_on_the_left_back"].loadFromFile("Textures/Textures_map/grass_tile_on_the_left_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_on_the_left_back texture" << std::endl;
		}
		if (!textures[6]["grass_tile_on_the_right_back"].loadFromFile("Textures/Textures_map/grass_tile_on_the_right_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_on_the_right_back texture" << std::endl;
		}
		if (!textures[6]["grass_tile_in_corner_left_back"].loadFromFile("Textures/Textures_map/grass_tile_in_corner_left_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_in_corner_left_back texture" << std::endl;
		}
		if (!textures[6]["grass_tile_in_corner_right_back"].loadFromFile("Textures/Textures_map/grass_tile_in_corner_right_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load grass_tile_in_corner_right_back texture" << std::endl;
		}
		if (!textures[6]["earth_back"].loadFromFile("Textures/Textures_map/earth_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load earth_back texture" << std::endl;
		}
		if (!textures[6]["sand_back"].loadFromFile("Textures/Textures_map/sand_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load sand_back texture" << std::endl;
		}
		if (!textures[6]["gravel_back"].loadFromFile("Textures/Textures_map/gravel_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load gravel_back texture" << std::endl;
		}
		if (!textures[6]["ground8_back"].loadFromFile("Textures/Textures_map/ground8_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ground8_back texture" << std::endl;
		}
		if (!textures[6]["ground7_back"].loadFromFile("Textures/Textures_map/ground7_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load ground7_back texture" << std::endl;
		}

		////front filters
		if (!textures[6]["water_top_layer_back"].loadFromFile("Textures/Textures_map/water_top_layer_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load water_top_layer_back texture" << std::endl;
		}
		if (!textures[6]["water_down_layer_back"].loadFromFile("Textures/Textures_map/water_down_layer_back.png")) {
			std::cout << "Error -> TextureManager -> couldn't load water_down_layer_back texture" << std::endl;
		}
		if (!textures[6]["bush"].loadFromFile("Textures/Textures_map/bush.png")) {
			std::cout << "Error -> TextureManager -> couldn't bush texture" << std::endl;
		}

		//weapons
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[7]["sword1"].loadFromFile("Textures/Weapons/sword1.png")) {
			std::cout << "Error -> TextureManager -> couldn't sword1 texture" << std::endl;
		}
		if (!textures[7]["staff1"].loadFromFile("Textures/Weapons/staff1.png")) {
			std::cout << "Error -> TextureManager -> couldn't staff1 texture" << std::endl;
		}
		if (!textures[7]["bow1"].loadFromFile("Textures/Weapons/bow1.png")) {
			std::cout << "Error -> TextureManager -> couldn't bow1 texture" << std::endl;
		}

		//enemies Textures/Enemies/boss_wolf.png
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[8]["bush_killer"].loadFromFile("Textures/Enemies/bush_killer.png")) {
			std::cout << "Error -> TextureManager -> couldn't bush_killer texture" << std::endl;
		}
		if (!textures[8]["eye"].loadFromFile("Textures/Enemies/eye.png")) {
			std::cout << "Error -> TextureManager -> couldn't eye texture" << std::endl;
		}
		if (!textures[8]["hornet"].loadFromFile("Textures/Enemies/hornet.png")) {
			std::cout << "Error -> TextureManager -> couldn't hornet texture" << std::endl;
		}
		if (!textures[8]["beehive"].loadFromFile("Textures/Enemies/beehive.png")) {
			std::cout << "Error -> TextureManager -> couldn't beehive texture" << std::endl;
		}
		if (!textures[8]["kusaka"].loadFromFile("Textures/Enemies/kusaka.png")) {
			std::cout << "Error -> TextureManager -> couldn't kusaka texture" << std::endl;
		}
		if (!textures[8]["chubacabra"].loadFromFile("Textures/Enemies/RedMutant.png")) {
			std::cout << "Error -> TextureManager -> couldn't RedMutant texture" << std::endl;
		}
		if (!textures[8]["boss_wolf"].loadFromFile("Textures/Enemies/boss_wolf.png")) {
			std::cout << "Error -> TextureManager -> couldn't boss_wolf texture" << std::endl;
		}

		//enemies' ammunition  Textures/Enemies/laser.png
		textures.push_back(unordered_map<string, Texture>());
		if (!textures[9]["sheet"].loadFromFile("Textures/Enemies/sheet.png")) {
			std::cout << "Error -> TextureManager -> couldn't sheet texture" << std::endl;
		}
		if (!textures[9]["laser"].loadFromFile("Textures/Enemies/laser.png")) {
			std::cout << "Error -> TextureManager -> couldn't laser texture" << std::endl;
		}
		//std::cout << sizeof(textures);
		//std::cout << "uoigiuoiuofu   ";
	}

	Texture& TextureManager::getTexture(int index, string name)
	{
		return textures[index][name];
	}
