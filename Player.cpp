#include "stdafx.h"
#include "Player.h"

    Player::Player(TileMap& map){
        sandbox = &map;
        initVariables();
        initTexture();
        initSprite();
       // initWeapon();
        initAnimation();
        initPhysics();
    }

    Player::Player(TileMap& map, Vector2f position){
        sandbox = &map;
        initVariables();
        initTexture();
        initSprite(position);
        //initWeapon();
        initAnimation();
        initPhysics();
    }

    IntRect Player::get_pl_frame()
    {
        return currentFrame;
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
        player_S.setPosition(10, 10);

    }

    void Player::initSprite(Vector2f position){
        player_S.setTexture(player_T);
        currentFrame = IntRect(2, 80, 48, 70);
        player_S.setTextureRect(currentFrame);
        //initial position
        player_S.setPosition(position);
    }

    void Player::initWeapon(const vector<vector<Enemy*>*>& enemies) {
        weapons.push_back(new Fist());
        weapons.push_back(new Bow(player_S.getPosition(), player_S.getGlobalBounds(), sandbox, enemies));
        weapons.push_back(new Sword(player_S.getPosition(), player_S.getGlobalBounds(), enemies));
        weapons.push_back(new CombatStaff(player_S.getPosition(), player_S.getGlobalBounds(), sandbox, enemies, info));
    }

    void Player::initAnimation(){
        animationSwitch = true;
        animationTimer.restart();
    }

    void Player::initPhysics(){
        stan_timer.restart();
        info = new GeneralInfo(100, 80);
        info->setGlobalBounds(player_S.getGlobalBounds());
        info->setPosition(player_S.getPosition());

        velocityMax = 6.f;
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

        alive = true;
        movingDirection = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    }

    void Player::render(RenderTarget& target){
        if (info->getHP() <= 0) {
            alive = false;
            animationState == PLAYER_ANIMATION_STATES::DEAD;
            currentFrame.top = 303;
            currentFrame.left = 288;
            currentFrame.width = 48;
            animationTimer.restart();
            player_S.setTextureRect(currentFrame);
        }
        //std::cout << getPosition().x << " " <<getPosition().y<<"\n";
        target.draw(player_S);
        if (alive) {
        weapons[chosen_weapon]->render(target);
        }
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
        info->changeVelocityX(dir_x * acceleration);

        // limits
        if (std::abs(info->getVelocity().x) > velocityMax) {
            info->setVelocityX(velocityMax * ((info->getVelocity().x > 0.f) ? 1.f : -1.f));
        }
       
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

bool Player::stan()
{
    if (info->getVelocity().x != 0.f)return false;
    else return true;
}

void Player::update(RenderWindow* window, FloatRect view_cords){
    if (alive && !checkStan()){
        updateMovement(window, view_cords);
        updateAnimation();
        updatePhysics();

        info->setGlobalBounds(player_S.getGlobalBounds());
        info->setPosition(player_S.getPosition());

        if (!info->isManaUsed()) {
            info->changeMana(1);
        }

        updateWeapon(window, view_cords);
        updateProjectiles();
    }
}

    void Player::updatePhysics(){
        // gravity
        info->changeVelocityY(1.f * gravity);
        if (std::abs(info->getVelocity().y) > velocityMaxY) {
            info->setVelocityY(velocityMaxY * ((info->getVelocity().y > 0.f) ? 1.f : -1.f));
        }
        
        //jumping
        if (isJumping) {
            info->changeVelocityY(-jumpVelocity);
            //jump deceleration
            jumpVelocity *= 0.96;      
        }
        
        //flying
        info->changeVelocityY(flyVelocity);
        if (flyVelocity < -0.01f) {
            if (!isFlying) {
                //fly deceleration
                flyVelocity *= 0.96;
            }
        }
        else {
            flyVelocity = 0.f;
        }
        // deceleration
        info->setVelocityX(info->getVelocity().x * deceleration);
        info->setVelocityY(info->getVelocity().y * deceleration);
        // std::cout << "x - " << getPosition().x << ", y - " << getPosition().y << std::endl;
        // limits
        
        updateCollision();
        
        if (std::abs(info->getVelocity().x) < velocityMin || updateCollisionX()) {
            info->setVelocityX(0.f);
        }
        if (std::abs(info->getVelocity().y) < velocityMin || updateCollisionY()) {
            info->setVelocityY(0.f);
        }
        
        
        player_S.move(info->getVelocity());
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
            walk(14.f);
            animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            movingDirection = PLAYER_ANIMATION_STATES::MOVING_LEFT;
            walk(-14.f);
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
            //std::cout << player_S.getPosition().x << " " << getPosition().y << std::endl;
            if (chosen_weapon < weapons.size())
                weapons[chosen_weapon]->attack(movingDirection, Vector2f(Mouse::getPosition(*window)), view_cords, true);
        }
        if (!Mouse::isButtonPressed(Mouse::Left)) {
            if (chosen_weapon < weapons.size())
                weapons[chosen_weapon]->attack(movingDirection, Vector2f(Mouse::getPosition(*window)), view_cords, false);
            
        }
        //std::cout << info->isManaUsed() << std::endl;
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
        if(chosen_weapon<weapons.size())
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

    void Player::setDeceleration(float dec){
        deceleration = dec;
    }

    void Player::change_weapon(short count){
        if (checkStan())
            return;
        chosen_weapon+=count;
        if (chosen_weapon >= static_cast<short>(weapons.size())) {
            chosen_weapon = 0;
        }
        if (chosen_weapon < 0) {
            chosen_weapon = weapons.size() - 1;
        }
    }

    void Player::changeHP(short z){
        info->changeHP(z);
        if (info->getHP() <= 0) {
            alive = false;
            animationState = PLAYER_ANIMATION_STATES::DEAD;
            currentFrame.top = 320;
            currentFrame.left = 288;
            currentFrame.width = 48;
            animationTimer.restart();
            player_S.setTextureRect(currentFrame);
        }
    }

    bool Player::updateCollisionX(){
        bool wasCollision = false;
        Vector2f newPosition(getPosition().x, getPosition().y);
        for (int i = player_S.getPosition().y / 64; i < (player_S.getPosition().y + player_S.getGlobalBounds().height) / 64; i++) {
            for (int j = (player_S.getPosition().x + info->getVelocity().x) / 64; j < (player_S.getPosition().x + info->getVelocity().x + player_S.getGlobalBounds().width) / 64; j++) {
                if (sandbox->isBlock(i, j)) {
                    if (info->getVelocity().x > 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox->getSizeTexture() - player_S.getGlobalBounds().width;
                    }
                    if (info->getVelocity().x < 0) {
                        wasCollision = true;
                        newPosition.x = j * sandbox->getSizeTexture() + sandbox->getSizeTexture();
                    }
                }
                //std::cout << sandbox->getInteraction(i, j) << std::endl;
            }
        }
        player_S.setPosition(newPosition.x, newPosition.y);
        return wasCollision;
    }
    
    bool Player::updateCollisionY(){
        bool wasCollision = false;
        Vector2f newPosition(player_S.getPosition().x, player_S.getPosition().y);
        
        for (int i = (player_S.getPosition().y + info->getVelocity().y) / 64; i < (player_S.getPosition().y + info->getVelocity().y + player_S.getGlobalBounds().height) / 64; i++) {
            for (int j = player_S.getPosition().x / 64; j < (player_S.getPosition().x + player_S.getGlobalBounds().width) / 64; j++) {
                if (sandbox->isBlock(i, j)) {
                    if (info->getVelocity().y > 0) {
                        wasCollision = true;
                        newPosition.y = (i * sandbox->getSizeTexture() - player_S.getGlobalBounds().height);
                        resetJumpAccess();
                    }
                    if (info->getVelocity().y < 0) {
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

    void Player::updateCollision() {
        if ((getPosition().y + info->getVelocity().y + getGlobalBounds().height) > sandbox->getMapHeight()) {
            resetVelocityY();
            setPosition(
                getPosition().x,
                sandbox->getMapHeight() - getGlobalBounds().height);
            info->setVelocityY(0.f);
            resetJumpAccess();
        }
        if (getPosition().y + info->getVelocity().y < 0.f) {
            setPosition(
                getPosition().x,
                0);
            info->setVelocityY(0.f);
        }
        if ((getPosition().x + info->getVelocity().x + getGlobalBounds().width) > sandbox->getMapWidth()) {
            setPosition(
                sandbox->getMapWidth() - getGlobalBounds().width,
                getPosition().y);
            info->setVelocityX(0.f);
        }
        if (getPosition().x + info->getVelocity().x < 0) {
            setPosition(
                0,
                getPosition().y);
            info->setVelocityX(0.f);
        }
    }

    bool Player::checkStan(){
        if (stan_timer.getElapsedTime().asSeconds() <= info->getStanTime()) {
            return true;
        }
        else {
            info->setStanTime(0);
            stan_timer.restart();
            return false;
        }
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

    GeneralInfo* Player::getGeneralInfo(){
        return info;
    }

    const Vector2f Player::getPosition() const {
        return player_S.getPosition();
    }

    //const Vector2f Player::getVelocity() const {
    //    return velocity;
    //}
    //
    const short Player::getHP() const{
        return info->getHP();
    }
    //
    //short* Player::getHPp()
    //{
    //    return &HP;
    //}

    void Player::setPosition(const float x, const float y) {
        player_S.setPosition(x, y);
    }

    void Player::resetVelocityY() {
        info->setVelocityY(0.f);
    }