#include "stdafx.h"
#include "Projectile.h"

	Projectile::Projectile(Vector2f init_pos, Vector2f dest_pos_, TileMap* sandbox_, vector<kusaka*>* k_, vector<Eye_evil*>* e_, vector<RedMutant*>* r_, vector<WolfBoss*>* w_)
		:k(k_), e(e_), r(r_), w(w_), dest_pos(dest_pos_), speed(10), sandbox(sandbox_){
		//std::cout << init_pos.x << "  " << init_pos.y << std::endl;
		initTexture();
		initSprite(init_pos);
		initVariables();
	}
	
	void Projectile::initTexture(){
		if (!projectile_T.loadFromFile("Textures/Weapons/projectile1.png")) {
			std::cout << "Error -> Projectile -> couldn't load projectile texture" << std::endl;
		}
	}
	
	void Projectile::initSprite(Vector2f init_pos){
		projectile_S.setTexture(projectile_T);
		projectile_S.setTextureRect(IntRect(0, 0, 18, 18));
		projectile_S.setScale(2,2);
		projectile_S.setOrigin(9,9);
		projectile_S.setPosition(Vector2f(init_pos.x, init_pos.y-42+12));
	}

	void Projectile::initVariables(){
		Vector2f s = dest_pos - projectile_S.getPosition();
		norm_s = s / static_cast<float>(sqrt(pow(s.x, 2) + pow(s.y, 2)));
	}
	
	void Projectile::update(){
		projectile_S.move(norm_s * speed);
	}

	bool Projectile::updateCollision(){
		for (int i = (projectile_S.getPosition().y-4) / 64; i < (projectile_S.getPosition().y + 3) / 64; i++) {
			for (int j = (projectile_S.getPosition().x-4) / 64; j < (projectile_S.getPosition().x + 3) / 64; j++) {
				if (sandbox->outOfMap(i, j) && sandbox->isBlock(i, j)) {
					FloatRect bul = projectile_S.getGlobalBounds();
					FloatRect til(j*64, i*64, 64, 64);
					if (bul.intersects(til)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Projectile::updateHit(){
		for (auto& enemy : *e)
		{
			if (projectile_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
				enemy->changeHP(10);
				return true;
			}
		}
		for (auto& enemy : *k)
		{
			if (projectile_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
				enemy->changeHP(10);
				return true;
			}
		}
		for (auto& enemy : *r)
		{
			if (projectile_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
				enemy->changeHP(10);
				return true;
			}
		}
		for (auto& enemy : *w)
		{
			if (projectile_S.getGlobalBounds().intersects((enemy)->get_global_bounds())) {
				enemy->changeHP(10);
				return true;
			}
		}
		
		return false;
	}

	
	
	void Projectile::render(RenderTarget& target){
		target.draw(projectile_S);
	}
	