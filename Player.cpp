#include "stdafx.h"
#include "Player.h"

    //Player::Player(Texture& texture, RenderWindow& window_, Map& levelMap_)
    //    :absoluteRight(levelMap.Width* levelMap.sizeTexture)
    //    ,absoluteBottom(levelMap.Height* levelMap.sizeTexture)
    //    ,levelMap(levelMap_)
    //    ,player_S(texture)
    //    ,coordinates(547, 173, 56, 73)
    //    ,speedX(0)
    //    ,speedY(0)
    //    ,currentFrame(0){
    //    player_S.setTextureRect(sf::IntRect(0, 23, 56, 73));
    //}
    Player::Player(){
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
        if (!player_T.loadFromFile("Images/hero.png")) {
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
        velocityMax = 4.f;
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

    void Player::move(const float dir_x, const float dir_y){
        // acceleration
        velocity.x += dir_x * acceleration;

        // limits
        if (std::abs(velocity.x) > velocityMax) {
            velocity.x = velocityMax * ((velocity.x > 0.f) ? 1.f : -1.f);
        }

        velocity.y += dir_y * gravity;
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

        // deceleration
        velocity *= deceleration;

        // limits
        if (std::abs(velocity.x) < velocityMin) {
            velocity.x = 0.f;
        }
        if (std::abs(velocity.y) < velocityMin) {
            velocity.y = 0.f;
        }
        player_S.move(velocity);
    }

    // Collisions willwork only if there is a border on global map
    //void Player::updateMovement(double time, RenderWindow& window) {
    //    coordinates.left += speedX * time;
    //    checkingBordersX();
    //    checkCollisionX();
    //    
    //
    //    fallingTest();
    //    if (!onGround) {
    //        speedY = speedY + acceleration * time;
    //    }
    //    coordinates.top += speedY * (time * heightCoeficient);
    //    checkingBordersY();
    //    checkCollisionY();
    //    
    //    changeFrames(time);
    //    speedX = 0;
    //    player_S.setPosition(coordinates.left, coordinates.top);
    //}
    void Player::updateMovement() {
        animationState = PLAYER_ANIMATION_STATES::IDLE;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(1.f, 0.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(-1.f, 0.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            onGround = false;
            isJumping = false;
            move(0.f, -1.4f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move(0.f, 1.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
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

    void Player::resetNTHJump(){
        spaceRealeased = true;
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
//   void Player::changeFrames(double& time) {
//      currentFrame += 0.004 * time;
//      if (currentFrame > 6) currentFrame -= 6;
//      if (speedX > 0) {
//          player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame, 23, 56, 73));
//      }
//      if (speedX < 0) {
//          player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame + 75, 23, -56, 73));
//      }
//  }
//
//   void Player::fallingTest(){
//      if (levelMap.TileMap[((int)(coordinates.top + coordinates.height)) / 73][(int)(coordinates.left / 73)] == ' ' &&
//          levelMap.TileMap[((int)(coordinates.top + coordinates.height)) / 73][(int)((coordinates.width + coordinates.left) / 73)] == ' ') {
//          onGround = false;// only one change in this.class
//      }
//  }
//
//   void Player::checkingBordersX() {
//      if (coordinates.left + coordinates.width >= absoluteRight)
//          coordinates.left = absoluteRight - coordinates.width;
//      if (coordinates.left <= 0)
//          coordinates.left = 0;
//  }
//
//   void Player::checkingBordersY() {
//        if (coordinates.top + coordinates.height >= absoluteBottom)
//            coordinates.top = absoluteBottom - coordinates.height;
//        if (coordinates.top <= 0)
//            coordinates.top = 0;
//    }