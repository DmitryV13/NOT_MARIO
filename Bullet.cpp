#include "stdafx.h"
#include "Bullet.h"

	Bullet::Bullet(Vector2f init_pos, Vector2f dest_pos_, TileMap* sandbox_) : dest_pos(dest_pos_), speed(10), sandbox(sandbox_){
		std::cout << init_pos.x << "  " << init_pos.y << std::endl;
		initTexture();
		initSprite(init_pos);
		initVariables();
	}
	
	void Bullet::initTexture(){
		if (!bullet_T.loadFromFile("Textures/Weapons/staffBullet.png")) {
			std::cout << "Error -> Bullet -> couldn't load bullet texture" << std::endl;
		}
	}
	
	void Bullet::initSprite(Vector2f init_pos){
		bullet_S.setTexture(bullet_T);
		bullet_S.setTextureRect(IntRect(0, 0, 18, 18));
		bullet_S.setScale(2,2);
		bullet_S.setOrigin(9,9);
		bullet_S.setPosition(Vector2f(init_pos.x, init_pos.y-42+12));
	}

	void Bullet::initVariables(){
		Vector2f s = dest_pos - bullet_S.getPosition();
		norm_s = s / static_cast<float>(sqrt(pow(s.x, 2) + pow(s.y, 2)));
	}
	
	void Bullet::update(){
		bullet_S.move(norm_s * speed);
	}

	bool Bullet::updateCollision(){
		Vector2f newPosition(bullet_S.getPosition().x, bullet_S.getPosition().y);
		for (int i = (bullet_S.getPosition().y-4) / 60; i < (bullet_S.getPosition().y + 3) / 60; i++) {
			for (int j = (bullet_S.getPosition().x-4) / 60; j < (bullet_S.getPosition().x + 3) / 60; j++) {
				if (sandbox->isBlock(i, j)) {
					FloatRect bul = bullet_S.getGlobalBounds();
					FloatRect til(j*60, i*60, 60, 60);
					if (bul.intersects(til)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	
	
	void Bullet::render(RenderTarget& target){
		target.draw(bullet_S);
	}
	