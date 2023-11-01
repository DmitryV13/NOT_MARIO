#include "stdafx.h"
#include "Player.h"

    Player::Player(TileMap& map): sandbox(map){
        initVariables();
        initTexture();
        initSprite();
        initAnimation();
        initPhysics();
    }

    void Player::initVariables(){
        animationState = PLAYER_ANIMATION_STATES::IDLE;
    }

    void Player::initTexture(){
        if (!player_T.loadFromFile("Textures/hero.png")) {
            std::cout << "Error -> Player -> couldn't load player texture" << std::endl;
        }
    }

    void Player::initSprite(){
        player_S.setTexture(player_T);
        currentFrame = IntRect(0, 23, 56, 73);
        player_S.setTextureRect(currentFrame);
    }

    void Player::initAnimation(){
        animationSwitch = true;
        animationTimer.restart();
    }

    void Player::initPhysics(){
        velocityMax = 14.f;
        velocityMin = 0.5f;
        acceleration = 1.7f;
        deceleration = 0.77f;//0.77
        gravity = 2.5f;
        velocityMaxY = 15.f;

        spaceRealeased = false;
        onGround = false;
        isJumping = false;
        jumpVelocity = 7.f;
        jumpCount = 0;
        jumpLimit = 3;

        isFlying = false;
        flyVelocity = 0;
    }

    void Player::render(sf::RenderTarget& target){
        target.draw(player_S);
    }

    void Player::resetJumpAccess(){
        onGround = true;
        isJumping=false;
        jumpCount = 0;
        spaceRealeased = false;
    }

    void Player::walk(const float dir_x){
        // acceleration
        velocity.x += dir_x * acceleration;

        // limits
        if (std::abs(velocity.x) > velocityMax) {
            velocity.x = velocityMax * ((velocity.x > 0.f) ? 1.f : -1.f);
        }
       
        //velocity.y += dir_y * gravity;
    }


    void Player::jump(const float dir_y) {
        if (onGround) {
            onGround = false;
            isJumping = true;
            jumpCount++;
            jumpVelocity = 7.f;
        } else if (isJumping && jumpCount < jumpLimit && spaceRealeased) {
            spaceRealeased = false;
            jumpCount++;
            jumpVelocity = 7.f;
        }

    }

    void Player::fly(const float dir_y) {
        isFlying = true;
        flyVelocity = dir_y * gravity;
    }

    void Player::update(){
        updateMovement();
        updateAnimation();
        updatePhysics();
    }

    void Player::updatePhysics(){

        // gravity
        velocity.y += 1.f * gravity;
        if (std::abs(velocity.y) > velocityMaxY) {
            velocity.y = velocityMaxY * ((velocity.y > 0.f) ? 1.f : -1.f);
        }

        //jumping
        if (isJumping) {
            velocity.y -= jumpVelocity;
            //jump deceleratin
            jumpVelocity *= 0.96;      
        }

        //flying
        velocity.y += flyVelocity;
        if (flyVelocity < -0.01f) {
            if (!isFlying) {
                //fly deceleratin
                flyVelocity *= 0.96;
            }
        }
        else {
            flyVelocity = 0.f;
        }
       // std::cout << flyVelocity << std::endl;
        // deceleration
        velocity *= deceleration;
        
        // limits
        if (std::abs(velocity.x) < velocityMin || updateCollisionX()) {
            velocity.x = 0.f;
        }
        if (std::abs(velocity.y) < velocityMin || updateCollisionY()) {
            velocity.y = 0.f;
        }

        
        player_S.move(velocity);
    }

    void Player::updateMovement() {
        animationState = PLAYER_ANIMATION_STATES::IDLE;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            walk(4.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            walk(-4.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            onGround = false;
            isJumping = false;
            fly(-1.4f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            //untill water will be done it won't have implementation
            
            //move(0.f, 1.f);
            //animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            jump(-20.0f);
            animationState = PLAYER_ANIMATION_STATES::JUMPING;
        }
    }

    void Player::updateAnimation(){
        //if (animationState == PLAYER_ANIMATION_STATES::IDLE) {
        //    if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
        //        currentFrame.left += 75;
        //        if (currentFrame.left >= 450.f) {
        //            currentFrame.left = 0.f;
        //        }
        //
        //        animationTimer.restart();
        //        player_S.setTextureRect(currentFrame);
        //    }
        //}
        //else 
        if (animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                currentFrame.left += 75;
                if (currentFrame.left >= 450.f) {
                    currentFrame.left = 0.f;
                }
                currentFrame.width = 56;
                player_S.setTextureRect(currentFrame);
                animationTimer.restart();
            }
        }
        else if (animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                currentFrame.left -= 75;
                if (currentFrame.left <= 0.f) {
                    currentFrame.left = 450.f;
                }
                currentFrame.width = -56;
                player_S.setTextureRect(currentFrame);
                animationTimer.restart();
            }
        }
        
        // OTHER KEY EVENTS

        //else if (animationState == PLAYER_ANIMATION_STATES::MOVING_UP) {
        //    if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
        //        currentFrame.left += 75;
        //        if (currentFrame.left >= 450.f) {
        //            currentFrame.left = 0.f;
        //        }
        //
        //        animationTimer.restart();
        //        player_S.setTextureRect(currentFrame);
        //    }
        //}
        //else if (animationState == PLAYER_ANIMATION_STATES::MOVING_DOWN) {
        //    if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
        //        currentFrame.left += 75;
        //        if (currentFrame.left >= 450.f) {
        //            currentFrame.left = 0.f;
        //        }
        //
        //        animationTimer.restart();
        //        player_S.setTextureRect(currentFrame);
        //    }
        //}
        //else if (animationState == PLAYER_ANIMATION_STATES::JUMPING) {
        //    if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
        //        currentFrame.left += 75;
        //        if (currentFrame.left >= 450.f) {
        //            currentFrame.left = 0.f;
        //        }
        //
        //        animationTimer.restart();
        //        player_S.setTextureRect(currentFrame);
        //    }
        //}
        //else if (animationState == PLAYER_ANIMATION_STATES::FALLING) {
        //    if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
        //        currentFrame.left += 75;
        //        if (currentFrame.left >= 450.f) {
        //            currentFrame.left = 0.f;
        //        }
        //
        //        animationTimer.restart();
        //        player_S.setTextureRect(currentFrame);
        //    }
        //}
        else {
            animationTimer.restart();
        }
    }

    void Player::resetAnimationTimer(){
        animationTimer.restart();
        animationSwitch = true;
    }

    bool Player::updateCollisionX(){
        bool wasCollision = false;
        sf::Vector2f newPosition(getPosition().x, getPosition().y);
        for (int i = player_S.getPosition().y / 60; i < (player_S.getPosition().y + player_S.getGlobalBounds().height) / 60; i++) {
            for (int j = (player_S.getPosition().x + velocity.x) / 60; j < (player_S.getPosition().x + velocity.x + player_S.getGlobalBounds().width) / 60; j++) {
                if (sandbox.isBlock(i, j)) {
                    if (velocity.x > 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox.getSizeTexture() - player_S.getGlobalBounds().width;
                    }
                    if (velocity.x < 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox.getSizeTexture() + sandbox.getSizeTexture();
                    }
                }
            }
        }
        player_S.setPosition(newPosition.x, newPosition.y);
        return wasCollision;
    }
    
    bool Player::updateCollisionY(){
        bool wasCollision = false;
        sf::Vector2f newPosition(player_S.getPosition().x, player_S.getPosition().y);

        for (int i = (player_S.getPosition().y + velocity.y) / 60; i < (player_S.getPosition().y + velocity.y + player_S.getGlobalBounds().height) / 60; i++) {
            for (int j = player_S.getPosition().x / 60; j < (player_S.getPosition().x + player_S.getGlobalBounds().width) / 60; j++) {
                if (sandbox.isBlock(i, j)) {
                    if (velocity.y > 0) {
                        wasCollision = true;
                        newPosition.y = (i * sandbox.getSizeTexture() - player_S.getGlobalBounds().height);
                        resetJumpAccess();
                    }
                    if (velocity.y < 0) {
                        wasCollision = true;
                        newPosition.y = i * sandbox.getSizeTexture() + sandbox.getSizeTexture();
                        //speedY = 0;
                    }
                }
            }
        }
        setPosition(newPosition.x, newPosition.y);
        return wasCollision;
    }

    void Player::resetNTHJump(){
        spaceRealeased = true;
    }

    void Player::resetIsFlying() {
        isFlying = false;
    }

    const bool& Player::getAnimationSwitch(){
        bool tmpSwitch = animationSwitch;
        if (animationSwitch) {
            animationSwitch = false;
        }
        return tmpSwitch;
    }

    const FloatRect Player::getGlobalBounds() const {
        return player_S.getGlobalBounds();
    }

    const sf::Vector2f Player::getPosition() const {
        return player_S.getPosition();
    }

    const sf::Vector2f Player::getVelocity() const {
        return velocity;
    }

    void Player::setPosition(const float x, const float y) {
        player_S.setPosition(x, y);
    }

    void Player::resetVelocityY() {
        velocity.y = 0.f;
    }
//   void Player::checkCollisionX() {
//      for (int i = coordinates.top / 73; i < ((coordinates.top + coordinates.height) / 73); i++)
//          for (int j = coordinates.left / 73; j < ((coordinates.width + coordinates.left) / 73); j++) {
//              if (levelMap.TileMap[i][j] != ' ') {
//                  if (speedX > 0) {
//                      coordinates.left = j * levelMap.sizeTexture - coordinates.width;
//                  }
//                  if (speedX < 0) {
//                      coordinates.left = j * levelMap.sizeTexture + levelMap.sizeTexture;
//                  }
//              }
//          }
//  }
//
//   void Player::checkCollisionY() {
//      for (int i = coordinates.top / 73; i < ((coordinates.top + coordinates.height) / 73); i++)
//          for (int j = coordinates.left / 73; j < ((coordinates.width + coordinates.left) / 73); j++) {
//              if (levelMap.TileMap[i][j] != ' ') {
//                  if (speedY > 0) {
//                      coordinates.top = i * levelMap.sizeTexture - coordinates.height;
//                      speedY = 0;
//                      onGround = true;
//                  }
//                  if (speedY < 0) {
//                      coordinates.top = i * levelMap.sizeTexture + levelMap.sizeTexture;
//                      speedY = 0;
//                  }
//              }
//          }
//  }
//

