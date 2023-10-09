#include "stdafx.h"
#include "Tile.h"

	Tile::Tile(std::string path_T, sf::IntRect textureRect, int interaction_)
		:interaction(interaction_)
		,currentFrame(textureRect) {
		initTexture(path_T);
		initSprite();
	}
	
	const sf::Vector2f Tile::getPosition() const
	{
		return tile_S.getPosition();
	}

	void Tile::initTexture(std::string path_T){
		if (!tile_T.loadFromFile(path_T)) {
			std::cout << "Error -> Tile -> couldn't load tile texture" << std::endl;
		}
	}

	void Tile::initSprite(){
		tile_S.setTexture(tile_T);
		tile_S.setTextureRect(currentFrame);
	}
	
	void Tile::setPosition(const float x, const float y){
		tile_S.setPosition(x, y);
	}

	void Tile::update(){

	}
	
	void Tile::render(sf::RenderTarget& target){
		target.draw(tile_S);
	}
	