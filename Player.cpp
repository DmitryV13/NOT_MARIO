#include "stdafx.h"
#include "Player.h"

    Player::Player(TileMap& map) {
        sandbox = &map;
        initVariables();
        initTexture();
        initSprite();
        initWeapon();
        initAnimation();
        initPhysics();
    }

    void Player::initVariables(){
        animationState = PLAYER_ANIMATION_STATES::IDLE_RIGHT;
        chosen_weapon = 0;
    }

    void Player::initTexture(){
        if (!player_T.loadFromFile("Textures/Heroes/hero1.png")) {
            std::cout << "Error -> Player -> couldn't load player texture" << std::endl;
        }
    }

    void Player::initSprite(){
        player_S.setTexture(player_T);
        currentFrame = IntRect(2, 80, 48, 70);
        player_S.setTextureRect(currentFrame);
        //initial position
        //player_S.setPosition(67, 78);
    }

    void Player::initWeapon() {
        weapons.push_back(new Fist());
        weapons.push_back(new Bow(player_S.getPosition(), player_S.getGlobalBounds(), sandbox));
        weapons.push_back(new Sword(player_S.getPosition(), player_S.getGlobalBounds()));
        weapons.push_back(new CombatStaff(player_S.getPosition(), player_S.getGlobalBounds(), sandbox));
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

        movingDirection = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    }

    void Player::render(RenderTarget& target){
        target.draw(player_S);
        weapons[chosen_weapon]->render(target);
        renderProjectiles(target);
    }

    void Player::renderProjectiles(RenderTarget& target){
        for (int i = 0; i < weapons.size(); i++) {
            weapons[i]->renderProjectiles(target);
        }
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
            animationState = PLAYER_ANIMATION_STATES::JUMPING;
            onGround = false;
            isJumping = true;
            jumpCount++;
            jumpVelocity = 7.f;
        } else if (isJumping && jumpCount < jumpLimit && spaceRealeased) {
            animationState = PLAYER_ANIMATION_STATES::JUMPING;
            spaceRealeased = false;
            jumpCount++;
            jumpVelocity = 7.f;
        }

    }

    void Player::fly(const float dir_y) {
        isFlying = true;
        flyVelocity = dir_y * gravity;
    }

    void Player::update(RenderWindow* window, FloatRect view_cords){
        updateMovement(window, view_cords);
        updateAnimation();
        updatePhysics();
        updateWeapon(window, view_cords);
        updateProjectiles();
        updatePresence();
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
            //jump deceleration
            jumpVelocity *= 0.96;      
        }

        //flying
        velocity.y += flyVelocity;
        if (flyVelocity < -0.01f) {
            if (!isFlying) {
                //fly deceleration
                flyVelocity *= 0.96;
            }
        }
        else {
            flyVelocity = 0.f;
        }
        //std::cout << flyVelocity << std::endl;
        // deceleration
        velocity *= deceleration;
       // std::cout << "x - " << getPosition().x << ", y - " << getPosition().y << std::endl;
        // limits
        if (std::abs(velocity.x) < velocityMin || updateCollisionX()) {
            velocity.x = 0.f;
        }
        if (std::abs(velocity.y) < velocityMin || updateCollisionY()) {
            velocity.y = 0.f;
        }

        
        player_S.move(velocity);
    }

    void Player::updateMovement(RenderWindow* window, FloatRect view_cords) {
        if (movingDirection== PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
            animationState = PLAYER_ANIMATION_STATES::IDLE_RIGHT;
        }
        else {
            animationState = PLAYER_ANIMATION_STATES::IDLE_LEFT;
        }

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            movingDirection = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
            walk(4.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            movingDirection = PLAYER_ANIMATION_STATES::MOVING_LEFT;
            walk(-4.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            onGround = false;
            isJumping = false;
            fly(-1.4f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            //untill water will be done it won't have implementation
            
            //move(0.f, 1.f);
            //animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            jump(-20.0f);
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            weapons[chosen_weapon]->attack(movingDirection, Vector2f(Mouse::getPosition(*window)), view_cords, true);
        }
        if (!Mouse::isButtonPressed(Mouse::Left)) {
            weapons[chosen_weapon]->attack(movingDirection, Vector2f(Mouse::getPosition(*window)), view_cords, false);
        }
    }

    void Player::updateAnimation(){
        if (animationState == PLAYER_ANIMATION_STATES::IDLE_LEFT) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                currentFrame.top = 80;
                currentFrame.left += 48;
                if (currentFrame.left >= 336.f) {
                    currentFrame.left = 48.f;
                }
                currentFrame.width = -48;
                animationTimer.restart();
                player_S.setTextureRect(currentFrame);
            }
        }else
            if(animationState == PLAYER_ANIMATION_STATES::IDLE_RIGHT) {
                if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                    currentFrame.top = 80;
                    currentFrame.left += 48;
                    if (currentFrame.left >= 288.f) {
                        currentFrame.left = 0.f;
                    }
                    currentFrame.width = 48;
                    animationTimer.restart();
                    player_S.setTextureRect(currentFrame);
                }
            }
        else 
        if (animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.05f || getAnimationSwitch()) {
                currentFrame.top = 160;
                currentFrame.left += 48;
                if (currentFrame.left >= 288.f) {
                    currentFrame.left = 0.f;
                }
                currentFrame.width = 48;
                player_S.setTextureRect(currentFrame);
                animationTimer.restart();
            }
        }
        else if (animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
            if (animationTimer.getElapsedTime().asSeconds() >= 0.05f || getAnimationSwitch()) {
                currentFrame.top = 160;
                currentFrame.left -= 48;
                if (currentFrame.left <= 0.f) {
                    currentFrame.left = 288.f;
                }
                currentFrame.width = -48;
                player_S.setTextureRect(currentFrame);
                animationTimer.restart();
            }
        }
        
        // OTHER KEY EVENTS

        else if (animationState == PLAYER_ANIMATION_STATES::MOVING_UP) {
            if (movingDirection==PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
                if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                    currentFrame.top = 240;
                    currentFrame.left += 48;
                    if (currentFrame.left >= 288.f) {
                        currentFrame.left = 0.f;
                    }
                    currentFrame.width = 48;
                    animationTimer.restart();
                    player_S.setTextureRect(currentFrame);
                }
            }
            else {
                if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch()) {
                    currentFrame.top = 240;
                    currentFrame.left += 48;
                    if (currentFrame.left >= 336.f) {
                        currentFrame.left = 48.f;
                    }
                    currentFrame.width = -48;
                    animationTimer.restart();
                    player_S.setTextureRect(currentFrame);
                }
            }
        }
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

    void Player::updateWeapon(RenderWindow* window, FloatRect view_cords){
        weapons[chosen_weapon]->update(player_S.getPosition(), movingDirection, window, view_cords);
    }

    void Player::updateProjectiles(){
        for (int i = 0; i < weapons.size(); i++){
            weapons[i]->updateProjectiles();
        }
    }

    void Player::resetAnimationTimer(){
        animationTimer.restart();
        animationSwitch = true;
    }

    void Player::change_weapon(short count){
        chosen_weapon+=count;
        if (chosen_weapon >= static_cast<short>(weapons.size())) {
            chosen_weapon = 0;
        }
        if (chosen_weapon < 0) {
            chosen_weapon = weapons.size() - 1;
        }
    }

    bool Player::updateCollisionX(){
        bool wasCollision = false;
        Vector2f newPosition(getPosition().x, getPosition().y);
        for (int i = player_S.getPosition().y / 60; i < (player_S.getPosition().y + player_S.getGlobalBounds().height) / 60; i++) {
            for (int j = (player_S.getPosition().x + velocity.x) / 60; j < (player_S.getPosition().x + velocity.x + player_S.getGlobalBounds().width) / 60; j++) {
                if (sandbox->isBlock(i, j)) {
                    if (velocity.x > 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox->getSizeTexture() - player_S.getGlobalBounds().width;
                    }
                    if (velocity.x < 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
                    }
                }
            }
        }
        player_S.setPosition(newPosition.x, newPosition.y);
        return wasCollision;
    }
    
    bool Player::updateCollisionY(){
        bool wasCollision = false;
        Vector2f newPosition(player_S.getPosition().x, player_S.getPosition().y);

        for (int i = (player_S.getPosition().y + velocity.y) / 60; i < (player_S.getPosition().y + velocity.y + player_S.getGlobalBounds().height) / 60; i++) {
            for (int j = player_S.getPosition().x / 60; j < (player_S.getPosition().x + player_S.getGlobalBounds().width) / 60; j++) {
                if (sandbox->isBlock(i, j)) {
                    if (velocity.y > 0) {
                        wasCollision = true;
                        newPosition.y = (i * sandbox->getSizeTexture() - player_S.getGlobalBounds().height);
                        resetJumpAccess();
                    }
                    if (velocity.y < 0) {
                        wasCollision = true;
                        newPosition.y = i * sandbox->getSizeTexture() + sandbox->getSizeTexture();
                        //speedY = 0;
                    }
                }
            }
        }
        setPosition(newPosition.x, newPosition.y);
        return wasCollision;
    }

    void Player::updatePresence(){
        int indexI[6];
        int indexJ[6];
        for (int i = 0; i < 6; i++) {
            indexI[i] = -1;
            indexJ[i] = -1;
        }  
        int i1 = 0, j1 = 0;
        for (int i = (player_S.getPosition().y + velocity.y) / 60; i < (player_S.getPosition().y + velocity.y + player_S.getGlobalBounds().height) / 60; i++) {
            for (int j = player_S.getPosition().x / 60; j < (player_S.getPosition().x + player_S.getGlobalBounds().width) / 60; j++) {
                indexI[i1++] = i;
                indexJ[j1++] = j;
            }
        }
        //sandbox->updatePlayerPresence(indexI, indexJ);
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

    const Vector2f Player::getPosition() const {
        return player_S.getPosition();
    }

    const Vector2f Player::getVelocity() const {
        return velocity;
    }

    void Player::setPosition(const float x, const float y) {
        player_S.setPosition(x, y);
    }

    void Player::resetVelocityY() {
        velocity.y = 0.f;
    }

