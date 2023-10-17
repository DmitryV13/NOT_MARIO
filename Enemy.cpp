#include "stdafx.h"
#include "Enemy.h"




sf::Vector2f Enemy:: generateRandomStartPosition( int mapWidth, int mapHeight)
{
    //positional distribution
	//sf::Vector2f startPos;
   // int x = rand() % 6;
   //// return sf::Vector2f(8 * 73, 73 * 7);
   // 
   // if(x == 1)return sf::Vector2f(73, mapHeight - 73 * 4);
   // if(x == 2) return sf::Vector2f(mapWidth - 73 * 50, mapHeight - 73 * 4);
   // if (x == 3)return sf::Vector2f(mapWidth - 73 * 80, mapHeight - 73 * 4);
   // if (x == 4) return sf::Vector2f(8 * 73, 73 * 7);
   // if (x == 5) return sf::Vector2f(32 * 73, 73 * 6);

    //  randomized distribution
    int maxAttempts = 100000;

    for (int i = 0; i < maxAttempts; i++) {

        int x = 73 + rand() % (mapWidth - 73 * 2 + 1);
        int y = 73 + rand() % (mapHeight - 73 * 2 + 1);


        bool collisionDetected = false;
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                int blockX = (x + dx) / 73;
                int blockY = (y + dy) / 73;
                if (sandbox.isBlock(blockY, blockX)) {
                    collisionDetected = true;
                    break;
                }
            }
            if (collisionDetected) {
                break;
            }
        }

        if (!collisionDetected) {

            return sf::Vector2f(x, y);
        }
    }


    return sf::Vector2f(0, 0);
}

void Enemy::init_variables()
{
    animationState = Enemy_ANIMATION_STATES::ENEMY_IDLE;
}

Enemy::Enemy(TileMap& map) : sandbox(map)
{

    init_variables();
    //init_sprite();
    init_animation();
    init_physics();
    sf::Vector2f startPosition = generateRandomStartPosition(sandbox.getMapWidth(), sandbox.getMapHeight());
    setPosition(startPosition.x, startPosition.y);
    //setPosition(120, 120);
    walk(1.0f);

}

sf::Vector2f Enemy::getPosition() const
{
    return Enemy_S.getPosition();
}

const FloatRect Enemy::getGlobalBounds() const
{
    return Enemy_S.getGlobalBounds();
}

void Enemy::setPosition(const float x, const float y)
{
    Enemy_S.setPosition(x, y);
}

void Enemy::render(sf::RenderTarget& target)
{
    target.draw(Enemy_S);
}

void Enemy::update()
{
    updateMovement();
    updateAnimation();
    updatePhysics();
}

void Enemy::resetAnimationTimer()
{
    animationTimer.restart();
    animationSwitch = true;
}

void Enemy::updateAnimation()
{

    if (animationState == Enemy_ANIMATION_STATES::ENEMY_MOVING_RIGHT) {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch()) {
            currentFrame.left += 50;
            if (currentFrame.left >= 450.f) {
                currentFrame.left = 0.f;
            }
            currentFrame.width = 50;
            Enemy_S.setTextureRect(currentFrame);
            animationTimer.restart();
        }
    }
    else if (animationState == Enemy_ANIMATION_STATES::ENEMY_MOVING_LEFT) {
        if (animationTimer.getElapsedTime().asSeconds() >= 0.2f || get_animation_switch()) {
            currentFrame.left -= 50;
            if (currentFrame.left <= 0.f) {
                currentFrame.left = 450.f;
            }
            currentFrame.width = -50;
            Enemy_S.setTextureRect(currentFrame);
            animationTimer.restart();
        }
    }

    else {
        animationTimer.restart();
    }
}

void Enemy::init_animation()
{
    animationSwitch = true;
    animationTimer.restart();
}

const bool& Enemy::get_animation_switch()
{
    bool tmpSwitch = animationSwitch;
    if (animationSwitch) {
        animationSwitch = false;
    }
    return tmpSwitch;
}

void Enemy::init_physics()
{
    displacementMax = 4.f;
    displacementMin = 0.5f;
    acceleration = 2.7f;
    deceleration = 0.77f;//0.77
    gravity = 2.5f;
    velocityMaxY = 15.f;

    onGround = false;
    jumpVelocity = 7.f;

    moving = 1.f;

    stepLeft = 0;
    stepRight = 0;
    jumpTile = false;
    displacement.x = 0.f;
    displacement.y = 0.f;


}

void Enemy::walk(const float dir_x)
{
    
    if (dir_x > 0)
        stepRight++;
    if (dir_x < 0)
        stepLeft++;
    if (onGround) {
        displacement.x += dir_x * acceleration;
        displacement.y += 1.f * gravity;
    }
    else if (jumpTile) {
        displacement.x += dir_x * acceleration;
        displacement.y += 1.f * gravity*2;
    }
    
    // limits
    if (std::abs(displacement.x) > displacementMax) {
        displacement.x = displacementMax * ((displacement.x > 0.f) ? 1.f : -1.f);
    }
}

void Enemy::updateMovement()
{
    if (!onGround)iterationStart = 0;
    if (displacement.x == 0.f && displacement.x == 0.f &&!onGround) {
        iterationStart++;
        walk(-1.f);
        walk(1.f);
    }
    animationState = Enemy_ANIMATION_STATES::ENEMY_IDLE;
    if (updateCollisionY())
        onGround = true;
    
    if (updateCollisionX()) 
            jump(-20.0f);

    if (displacement.x == 0.f && iterationStart > iterationEnd)
    {
        moving *= -1.f;
        iterationStart = 0;

    }else iterationStart++;

    if (stepRight == maxStep) {
        iterationStart = 0;
    	moving *= -1.f;
        stepRight = 0;
    }
    if (stepLeft== maxStep) {
        moving *= -1.f;
        stepLeft = 0;
        iterationStart = 0;
    }
    	
    if (moving > 0.f) animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_RIGHT;
    else  animationState = Enemy_ANIMATION_STATES::ENEMY_MOVING_LEFT;

    walk(moving);
   
}


void Enemy::resetVelocityY()
{
    displacement.y = 0.f;
}



void Enemy::resetJumpAccess()
{
    resetVelocityY();
    onGround = true;
    jumpTile = false;
    
}


void Enemy::jump(const float dir_y)
{
    
    if (onGround) {
        onGround = false;
        jumpTile = true;
        jumpVelocity = 10.5f;
    }
    
}


void Enemy::updatePhysics()
{
    // gravity
    displacement.y += 1.f * gravity;
    
    if (std::abs(displacement.y) > velocityMaxY) {
        displacement.y = velocityMaxY * ((displacement.y > 0.f) ? 1.f : -1.f);
    }

    //jumping
    if (jumpTile) {
        displacement.y -= jumpVelocity;
        //jump deceleratin
        jumpVelocity *= 0.96;
    }

    // deceleration
    displacement *= deceleration;

    // limits
    if (std::abs(displacement.x) < displacementMin || updateCollisionX()) {
        displacement.x = 0.f;
    }
    if (std::abs(displacement.y) < displacementMin || updateCollisionY()) {
        displacement.y = 0.f;
    }

    Enemy_S.move(displacement);
}



bool Enemy::updateCollisionX()
{
    bool wasCollision = false;
    sf::Vector2f newPosition(getPosition().x, getPosition().y);
    for (int i = Enemy_S.getPosition().y / 73; i < (Enemy_S.getPosition().y + Enemy_S.getGlobalBounds().height) / 73; i++) {
        for (int j = (Enemy_S.getPosition().x + displacement.x) / 73; j < (Enemy_S.getPosition().x + displacement.x + Enemy_S.getGlobalBounds().width) / 73; j++) {
            if (sandbox.isBlock(i, j)) {
                if (displacement.x >= 0) {
                    wasCollision = true;
                    jumpTile = true;
                    newPosition.x = j * sandbox.getSizeTexture() - Enemy_S.getGlobalBounds().width;
                    if (iterationStart == 0) currentBlockX = j;
                    
                    
                }
                if (displacement.x < 0) {
                    wasCollision = true;
                    jumpTile = true;
                   
                    if (iterationStart == 0 && jumpTile) currentBlockX = j;
                  
                    newPosition.x = j * sandbox.getSizeTexture() + sandbox.getSizeTexture();

                }
            }
        }
    }
    Enemy_S.setPosition(newPosition.x, newPosition.y);
    return wasCollision;
}

bool Enemy::updateCollisionY()
{
    bool wasCollision = false;
    sf::Vector2f newPosition(Enemy_S.getPosition().x, Enemy_S.getPosition().y);

    for (int i = (Enemy_S.getPosition().y + displacement.y) / 73; i < (Enemy_S.getPosition().y + displacement.y + Enemy_S.getGlobalBounds().height) / 73; i++) {
        for (int j = Enemy_S.getPosition().x / 73; j < (Enemy_S.getPosition().x + Enemy_S.getGlobalBounds().width) / 73; j++) {
            if (sandbox.isBlock(i, j)) {
                
                if (displacement.y > 0) {
                    wasCollision = true;
                    currentBlockY = i;
                    if (iterationStart < iterationEnd)currentBlockY = (i * sandbox.getSizeTexture() - Enemy_S.getGlobalBounds().height) / 73;
                	newPosition.y = (i * sandbox.getSizeTexture() - Enemy_S.getGlobalBounds().height);
                    
                    
                }
                if (displacement.y < 0) {
                    wasCollision = true;
                	//resetJumpAccess();
                    currentBlockY = i;
                   
                    newPosition.y = i * sandbox.getSizeTexture() + sandbox.getSizeTexture();
                   
                }
            }
        }
    }
    
    setPosition(newPosition.x, newPosition.y);
    return wasCollision;
}






