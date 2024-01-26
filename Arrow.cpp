#include "stdafx.h"
#include "Arrow.h"

	Arrow::Arrow(Vector2f init_pos, short side_ ,TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_)
		:enemies(enemies_), side(side_), speed(10), sandbox(sandbox_) {
		initTexture();
		initSprite(init_pos);
		initVariables();
	}

	void Arrow::initTexture(){
		if (!arrow_T.loadFromFile("Textures/Weapons/arrow1.png")) {
			std::cout << "Error -> Arrow -> couldn't load arrow texture" << std::endl;
		}
	}
	
	void Arrow::initSprite(Vector2f init_pos){
		arrow_S.setTexture(arrow_T);
		arrow_S.setTextureRect(IntRect(0, 0, 40, 5));
		arrow_S.setOrigin(18, 2);
		arrow_S.setScale(1.2, 1.2);
		arrow_S.setPosition(init_pos.x, init_pos.y);
	}
	
	void Arrow::initVariables(){
		is_flying = false;
		stuck = false;
	}
	
	void Arrow::update(){
		if (is_flying) {
			arrow_S.move(norm_s * speed);
		}
	}

	void Arrow::letOff(Vector2f dest_pos_){
		dest_pos = dest_pos_;
		Vector2f s = dest_pos - arrow_S.getPosition();
		norm_s = s / static_cast<float>(sqrt(pow(s.x, 2) + pow(s.y, 2)));
		is_flying = true;
	}

	void Arrow::setPosition(Vector2f position){
		arrow_S.setPosition(position);
	}

	void Arrow::setRotationAngle(float angle){
		arrow_S.setRotation(angle);
	}

	const bool Arrow::isFlying() const{
		return is_flying;
	}

	const bool Arrow::isStuck() const{
		return stuck;
	}


	bool Arrow::updateHit() {
		for (auto enemy_l : enemies)
		{
			for(auto enemy : *enemy_l ){
				if (arrow_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
					enemy->changeHP(10);
					return true;
				}
			}
		}

		return false;
	}
	
	bool Arrow::updateCollision(){
		for (int i = (arrow_S.getPosition().y - 4) / 64; i < (arrow_S.getPosition().y + 3) / 64; i++) {
			for (int j = (arrow_S.getPosition().x - 4) / 64; j < (arrow_S.getPosition().x + 3) / 64; j++) {
				if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j)) {
					FloatRect bul = arrow_S.getGlobalBounds();
					FloatRect til(j * 64, i * 64, 64, 64);
					if (bul.intersects(til)) {
						norm_s.x = 0;
						norm_s.y = 0;
						stuck = true;
						return true;
					}
				}
			}
		}
		return false;
	}
	
	void Arrow::render(RenderTarget& target){
		target.draw(arrow_S);
	}
	