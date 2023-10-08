#include "Player.h"
#include <string.h>
#include<iostream>

    Player::Player(Texture& texture, RenderWindow& window_, Map& levelMap_)
        :absoluteRight(levelMap.Width* levelMap.sizeTexture)
        ,absoluteBottom(levelMap.Height* levelMap.sizeTexture)
        ,levelMap(levelMap_)
        ,player_S(texture)
        ,coordinates(547, 173, 56, 73)
        ,speedX(0)
        ,speedY(0)
        ,currentFrame(0){
        player_S.setTextureRect(sf::IntRect(0, 23, 56, 73));
    }

    // Collisions willwork only if there is a border on global map
    void Player::update(double time, RenderWindow& window) {
        coordinates.left += speedX * time;
        checkingBordersX();
        checkCollisionX();
        

        fallingTest();
        if (!onGround) {
            speedY = speedY + acceleration * time;
        }
        coordinates.top += speedY * (time * heightCoeficient);
        checkingBordersY();
        checkCollisionY();
        
        changeFrames(time);
        speedX = 0;
        player_S.setPosition(coordinates.left, coordinates.top);
    }

    void Player::checkCollisionX() {
        for (int i = coordinates.top / 73; i < ((coordinates.top + coordinates.height) / 73); i++)
            for (int j = coordinates.left / 73; j < ((coordinates.width + coordinates.left) / 73); j++) {
                if (levelMap.TileMap[i][j] != ' ') {
                    if (speedX > 0) {
                        coordinates.left = j * levelMap.sizeTexture - coordinates.width;
                    }
                    if (speedX < 0) {
                        coordinates.left = j * levelMap.sizeTexture + levelMap.sizeTexture;
                    }
                }
            }
    }

    void Player::checkCollisionY() {
        for (int i = coordinates.top / 73; i < ((coordinates.top + coordinates.height) / 73); i++)
            for (int j = coordinates.left / 73; j < ((coordinates.width + coordinates.left) / 73); j++) {
                if (levelMap.TileMap[i][j] != ' ') {
                    if (speedY > 0) {
                        coordinates.top = i * levelMap.sizeTexture - coordinates.height;
                        speedY = 0;
                        onGround = true;
                    }
                    if (speedY < 0) {
                        coordinates.top = i * levelMap.sizeTexture + levelMap.sizeTexture;
                        speedY = 0;
                    }
                }
            }
    }

    void Player::changeFrames(double& time) {
        currentFrame += 0.004 * time;
        if (currentFrame > 6) currentFrame -= 6;
        if (speedX > 0) {
            player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame, 23, 56, 73));
        }
        if (speedX < 0) {
            player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame + 75, 23, -56, 73));
        }
    }

    void Player::fallingTest(){
        if (levelMap.TileMap[((int)(coordinates.top + coordinates.height)) / 73][(int)(coordinates.left / 73)] == ' ' &&
            levelMap.TileMap[((int)(coordinates.top + coordinates.height)) / 73][(int)((coordinates.width + coordinates.left) / 73)] == ' ') {
            onGround = false;// only one change in this.class
        }
    }

    void Player::checkingBordersX() {
        if (coordinates.left + coordinates.width >= absoluteRight)
            coordinates.left = absoluteRight - coordinates.width;
        if (coordinates.left <= 0)
            coordinates.left = 0;
    }

    void Player::checkingBordersY() {
        if (coordinates.top + coordinates.height >= absoluteBottom)
            coordinates.top = absoluteBottom - coordinates.height;
        if (coordinates.top <= 0)
            coordinates.top = 0;
    }