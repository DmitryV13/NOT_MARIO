#include "stdafx.h"
#include "Bow.h"

	Bow::Bow(Vector2f player_position, FloatRect player_bounds, TileMap* sandbox_, const vector<vector<Enemy*>*>& enemies_, TextureManager* t_manager_, int index, string name)
		:enemies(enemies_), sandbox(sandbox_), t_manager(t_manager_) {
		initSprite(player_position, player_bounds, index, name);
		initVariables();
	}
	
	void Bow::initSprite(Vector2f player_position, FloatRect player_bounds, int index, string name){
		bow_S.setTexture(t_manager->getTexture(index, name));
		currentFrame = IntRect(0, 0, 36, 74);
		bow_S.setTextureRect(currentFrame);
		bow_S.setOrigin(18, 37);
		bow_S.setPosition(player_position.x + 27, player_position.y + 41);
	}
	
	void Bow::initVariables(){
		attack_activation = false;
		bow_pulled = false;
		side_of_attack = 0;
		previous_side = 0;
	}
	
	void Bow::initAnimation(){
		animationTimer.restart();
	}
	
	void Bow::update(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords){
		updatePosition(player_position, player_side, window, view_cords);
		updateAnimation();
	}
	
	void Bow::updatePosition(Vector2f player_position, short player_side, RenderWindow* window, FloatRect view_cords){
		Vector2f mouse_pos(Mouse::getPosition(*window));
		if (player_side == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
			currentFrame.width = 36.f;
			if (previous_side == 0) {
				previous_side = 1;
				currentFrame.left -= 36.f;
			}
			bow_S.setTextureRect(currentFrame);
			bow_S.setPosition(player_position.x + 27, player_position.y + 41);
			rot_angle = 180 / 3.14 * std::atan2(mouse_pos.y + (view_cords.top - view_cords.height / 2) - bow_S.getPosition().y, mouse_pos.x + (view_cords.left - view_cords.width / 2) - bow_S.getPosition().x);
			bow_S.setRotation(rot_angle);
		}
		else {
			if (previous_side == 1) {
				previous_side = 0;
				currentFrame.left += 36.f;
			}
			currentFrame.width = -36.f;
			bow_S.setTextureRect(currentFrame);
			//21-82
			bow_S.setPosition(player_position.x + 21, player_position.y + 41);
			rot_angle =180 / 3.14 * std::atan2(mouse_pos.y + (view_cords.top - view_cords.height / 2) - bow_S.getPosition().y, mouse_pos.x + (view_cords.left - view_cords.width / 2) - bow_S.getPosition().x);
			bow_S.setRotation(180 + rot_angle);
		}
		if (!arrows.empty() && !arrows[arrows.size() - 1]->isFlying()) {
			arrows[arrows.size() - 1]->setPosition(bow_S.getPosition());
			arrows[arrows.size() - 1]->setRotationAngle(rot_angle);
		}
	}

	void Bow::updateArrowPosition(){

	}
	
	void Bow::updateAnimation(){
		//if (attack_activation) {
		if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
			if (animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
				if (!bow_pulled && Mouse::isButtonPressed(Mouse::Left)) {
					currentFrame.top = 0;
					if (currentFrame.left == 0) {
						arrows.push_back(new Arrow(bow_S.getPosition(), side_of_attack, sandbox, enemies, t_manager, 0, "Arrow1"));
					}
					currentFrame.left += 36;
					if (currentFrame.left == 144) {
						bow_pulled = true;
						//arrows.push_back(new Arrow(bow_S.getPosition(), sandbox));
					}
					currentFrame.width = 36;
					animationTimer.restart();
					bow_S.setTextureRect(currentFrame);
				}
			}
		}
		else if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
			if (animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
				if (!bow_pulled && Mouse::isButtonPressed(Mouse::Left)) {
					currentFrame.top = 0;
					
					if (currentFrame.left == 36) {
						arrows.push_back(new Arrow(bow_S.getPosition(), side_of_attack, sandbox, enemies, t_manager, 0, "Arrow1"));
					}
					currentFrame.left += 36;
					if (currentFrame.left == 180) {
  						bow_pulled = true;
					}
					currentFrame.width = -36;
					animationTimer.restart();
					bow_S.setTextureRect(currentFrame);
				}
			}
		}
	}
	
	void Bow::updateProjectiles(){
		bool erased = false;
		for (int i = 0; i < arrows.size(); i++) {
			erased = false;
			arrows[i]->update();
			if (arrows[i]->isFlying() && !arrows[i]->isStuck()) {
				if (arrows[i]->updateHit()) {
					arrows.erase(arrows.begin() + i);
					erased = true;
				}
				if (!erased) {
					arrows[i]->updateCollision();
				}
			}
		}
	}
	
	void Bow::render(RenderTarget& target){
		target.draw(bow_S);
	}
	
	void Bow::renderProjectiles(RenderTarget& target){
		for (auto& i : arrows) {
			i->render(target);
		}
	}
	
	void Bow::attack(short side_attack, Vector2f mouse_pos, FloatRect view_cords, bool is_btn_pressed){
		this->side_of_attack = side_attack;
		
		arrow_dir = Vector2f(mouse_pos.x + (view_cords.left - view_cords.width / 2), mouse_pos.y + (view_cords.top - view_cords.height / 2));

		
		if (is_btn_pressed) {
			if (animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
				
				if (arrows.size() > 30) {
					delete arrows[0];
					arrows.erase(arrows.begin());
				}
			}
		}
		else {
			bow_pulled = false;
			if (side_of_attack == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
				if (currentFrame.left == 144) {
					arrows[arrows.size() - 1]->letOff(arrow_dir);
				}
				else {
					if (arrows.size() != 0 && !arrows[arrows.size() - 1]->isFlying()) {
						delete arrows[arrows.size() - 1];
						arrows.erase(arrows.begin() + arrows.size() - 1);
					}
				}
				currentFrame.left = 0;
				currentFrame.width = 36;
			}
			else {
				if (currentFrame.left == 180) {
					arrows[arrows.size() - 1]->letOff(arrow_dir);
				}
				else {
					if (arrows.size() != 0 && !arrows[arrows.size() - 1]->isFlying()) {
						delete arrows[arrows.size() - 1];
						arrows.erase(arrows.begin() + arrows.size() - 1);
					}
				}
				currentFrame.left = 36;
				currentFrame.width = -36;
			}
			bow_S.setTextureRect(currentFrame);
		}
	}
