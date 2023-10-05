#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Player.h"

using sf::Clock;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::View;
using std::cout;

const int H = 10;
const int W = 100;
const int size_texture = 60;

std::string TileMap[H] = {
    "                  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "                                                                                                   A",
    "                                                                                                   A",
    "                                                                                                   A",
    "A         BB                                                              BB                       A",
    "A        BBBBBB    BB                                 BBBBBB            BBBBBB      BB             A",
    "A      BBBBBBBBBBBBBBBB              BBBBB           BBBBBBBBB  B  BB  BBBBBBBBBB BBBBBB           A",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
};

int findGroundX(int index) {
    for (int i = 0; i < H; i++) {
        if (TileMap[i][index] != ' ')
            return i*size_texture;
    }
}

//window characteristics
const int screenHeight = 600;
const int screenWidth = 1500;    

// characteristics of map
float absoluteLeft = 0.0f;
float absoluteTop = 0.0f;
float absoluteRight = W * size_texture;
float absoluteBottom = H * size_texture;

// characteristics of window
float windowLeft = 0.0f;
float windowTop = 0.0f;
float windowRight = 1500.0f;
float windowBottom = 600.0f;


int ground = 150;


class PlayerA
{
public:
    Sprite player_S;
    float speedX;
    float speedY;
    float acceleration = 0.005;
    sf::FloatRect coordinates;
    bool onGround;
    float currentFrame;
   
    PlayerA(Texture& texture, RenderWindow& window_, View& view_) {
        player_S.setTexture(texture);
        player_S.setTextureRect(sf::IntRect(0, 23, 56, 73));
        coordinates = FloatRect(60, 83, 56, 73);
        speedX = 0;
        speedY = 0;
        currentFrame = 0;
    }
    void update(float time, RenderWindow& window, View& view) {
        coordinates.left += speedX * time;
        if (!onGround) {
            speedY = speedY + acceleration * time;           
        }
        onGround = false;
        coordinates.top += speedY * time;
        if (coordinates.top + coordinates.height >= findGroundX((int)coordinates.left / 20)){
            coordinates.top = findGroundX((int)coordinates.left / 20);
            speedY = 0;
            onGround = true;
        }
        currentFrame += 0.01 * time;
        if (currentFrame > 6) currentFrame -= 6;

        if (speedX > 0) {
            if (coordinates.left + player_S.getLocalBounds().width >= windowRight) {
                if (coordinates.left + player_S.getLocalBounds().width >= absoluteRight) {
                    windowLeft = absoluteRight - screenWidth;
                    windowRight = absoluteRight;
                    coordinates.left = absoluteRight - player_S.getLocalBounds().width;
                    player_S.setPosition(coordinates.left, coordinates.top);
                    view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                    window.setView(view);
                }
                else {
                    float offset = speedX - (windowRight - (coordinates.left + player_S.getLocalBounds().width));
                    view.move(offset, 0);
                    window.setView(view);
            
                    windowLeft += offset;
                    windowRight += offset;
                    
                    player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame, 23, 56, 73));
                }
            }
            else {
                player_S.setTextureRect(sf::IntRect(75 * (int)currentFrame, 23, 56, 73));
            }
        }
        if (speedX < 0) {
            if (coordinates.left  <= windowLeft) {
                if (coordinates.left  <= absoluteLeft) {
                    windowLeft = absoluteLeft;
                    windowRight = absoluteLeft + screenWidth;
                    coordinates.left = absoluteLeft;
                    player_S.setPosition(coordinates.left, coordinates.top);
                    view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                    window.setView(view);
                }
                else {
                    float offset = speedX - (coordinates.left - windowLeft);
                    view.move(-offset, 0);
                    window.setView(view);
                    windowLeft -= offset;
                    windowRight -= offset;
                    player_S.setTextureRect(sf::IntRect((75 * (int)currentFrame) + 75, 23, -56, 73));
                }
            }
            else {
                player_S.setTextureRect(sf::IntRect((75 * (int)currentFrame) + 75, 23, -56, 73));
            }
            
        }
        speedX = 0;
        player_S.setPosition(coordinates.left, coordinates.top);
    }

    void collisionX() {
        for (int i = coordinates.top/60; i <(coordinates.top+coordinates.height)/60; i++){
            for (int j = coordinates.left / 60; i < (coordinates.left + coordinates.width) / 60; i++) {
                if (TileMap[i][j] != ' ') {
                    if (speedX > 0) {
                        coordinates.left = j * 60 - coordinates.width;
                    }
                    if (speedX < 0) {
                        coordinates.left = j * 60 +60;
                    }
                }
            }
        }
    }
    void collisionY() {
        for (int i = coordinates.top / 60; i < (coordinates.top + coordinates.height) / 60; i++) {
            for (int j = coordinates.left / 60; i < (coordinates.left + coordinates.width) / 60; i++) {
                if (TileMap[i][j] != ' ') {
                    if (speedY > 0) {
                        coordinates.top = i * 60 - coordinates.height;
                        speedY = 0;
                        onGround = true;
                    }
                    if (speedY < 0) {
                        coordinates.top = i * 60 + 60;
                        speedY = 0;
                    }
                }
            }
        }
    }
};












//  Keys for control
// W - forward
// S - backward
// A - left
// D - right
// Q - enlarge
// E - shrink
//
// currentFrame - speed of changing frames
// speed - sprite's speed
// time - time for covering the distance
// s=v*t

int main()
{


    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO");
    // window, which will see usual user
    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
    window.setView(view);

    // textures
    sf::Texture block_T;
    sf::Texture hero_T;
    

    if (!hero_T.loadFromFile("Images/hero.png")) {
        return -1;
    }
    hero_T.setSmooth(true);
    if (!block_T.loadFromFile("Images/cube.jpg")) {
        return -1;
    }

    // game-area variables
    float ballSpeed = 4.2;

    // sprites
    sf::Sprite block_S(block_T);
    sf::Sprite hero_S(hero_T);
    block_S.setTextureRect(sf::IntRect(4, 4, size_texture, size_texture));
    
    //hero_S.setPosition(0, 0);
    //hero_S.setTextureRect(sf::IntRect(0, 23, 56, 73));//x y width height

    //Player mainPlayer(hero_T, W, H, size_texture, screenHeight, screenWidth);
    PlayerA pl(hero_T, window, view);
    Clock clock;
    //  ---------GAME_CODE----------
    while (window.isOpen())
    { 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;

        sf::Event event;
        while (window.pollEvent(event))
        {
            
            
            
            cout << pl.coordinates.top << std::endl;
            //sf::Vector2f spritePosition = mainPlayer.player_S.getPosition();
            sf::Vector2f spritePosition = hero_S.getPosition();

            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                //mainPlayer.moveDown(window, view);
               // if (spritePosition.y + hero_S.getLocalBounds().height + ballSpeed >= windowBottom) {
               //     if (spritePosition.y + hero_S.getLocalBounds().height + ballSpeed >= absoluteBottom) {
               //         windowBottom = absoluteBottom;
               //         windowTop = absoluteBottom-screenHeight;
               //         spritePosition.y = absoluteBottom - hero_S.getLocalBounds().height;
               //         hero_S.setPosition(spritePosition);
               //         view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
               //         window.setView(view);
               //     }
               //     else {
               //         float offset = ballSpeed - (windowBottom - (spritePosition.y + hero_S.getLocalBounds().height));
               //         view.move(0, offset);
               //         window.setView(view);
               // 
               //         windowTop += offset;
               //         windowBottom += offset;
               // 
               //         hero_S.move(0,ballSpeed);
               //     }
               // }
               // else {
               //     hero_S.move(0,ballSpeed);
               // }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
               //mainPlayer.moveRight(window, view);
               
                //if (spritePosition.x + hero_S.getLocalBounds().width + ballSpeed >= windowRight) {
                //    if (spritePosition.x + hero_S.getLocalBounds().width + ballSpeed  >= absoluteRight) {
                //        windowLeft = absoluteRight-screenWidth;
                //        windowRight = absoluteRight;
                //        spritePosition.x = absoluteRight - hero_S.getLocalBounds().width;
                //        hero_S.setPosition(spritePosition);
                //        view.setCenter(windowRight-(screenWidth/2),windowBottom-(screenHeight/2));
                //        window.setView(view);
                //    }
                //    else {
                //        float offset = ballSpeed - (windowRight - (spritePosition.x + hero_S.getLocalBounds().width));
                //        view.move(offset, 0);
                //        window.setView(view);
                //
                //        windowLeft += offset;
                //        windowRight += offset;
                //
                //        hero_S.move(ballSpeed*time, 0);
                //        currentFrame += 0.01*time;
                //        cout << (int)currentFrame*75<<" ";
                //        if (currentFrame > 6) currentFrame -= 6;
                //        hero_S.setTextureRect(sf::IntRect((75 * (int)currentFrame), 23, 56, 73));
                //    }
                //}
                //else {
                //    hero_S.move(ballSpeed*time, 0);
                //    currentFrame += 0.04*time;
                //    if (currentFrame > 6) currentFrame -= 6;
                //    hero_S.setTextureRect(sf::IntRect((75 * (int)currentFrame), 23, 56, 73));
                //}
                pl.speedX=ballSpeed;
                
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
               // mainPlayer.moveLeft(window, view);
               // if (spritePosition.x - ballSpeed <= windowLeft) {
               //     if (spritePosition.x - ballSpeed <= absoluteLeft) {
               //         windowLeft = absoluteLeft;
               //         windowRight = absoluteLeft+screenWidth;
               //         spritePosition.x = absoluteLeft;
               //         hero_S.setPosition(spritePosition);
               //         view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
               //         window.setView(view);
               //     }
               //     else {
               //         float offset = ballSpeed - (spritePosition.x - windowLeft);
               //         view.move(-offset, 0);
               //         window.setView(view);
               //         windowLeft -= offset;
               //         windowRight -= offset;
               // 
               //         hero_S.move(-ballSpeed*time, 0);
               //         currentFrame += 0.01 * time;
               //         if (currentFrame > 6) currentFrame -= 6;
               //         hero_S.setTextureRect(sf::IntRect((75 * (int)currentFrame) + 75, 23, -56, 73));
               //     }
               // }
               // else {
               //     hero_S.move(-ballSpeed*time, 0);
               //     currentFrame += 0.01 * time;
               //     if (currentFrame > 6) currentFrame -= 6;
               //     hero_S.setTextureRect(sf::IntRect((75 * (int)currentFrame)+75, 23, -56, 73));
               // }
                pl.speedX=-ballSpeed;
                
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
              //  mainPlayer.moveUp(window, view);
                //if (spritePosition.y - ballSpeed <= windowTop) {
                //    if (spritePosition.y - ballSpeed <= absoluteTop) {
                //        windowBottom = absoluteTop+screenHeight;
                //        windowTop = absoluteTop;
                //        spritePosition.y = absoluteTop;
                //        hero_S.setPosition(spritePosition);
                //        view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                //        window.setView(view);
                //    }
                //    else {
                //        float offset = ballSpeed - (spritePosition.y - windowTop);
                //        view.move(0, -offset);
                //        window.setView(view);
                //        windowTop -= offset;
                //        windowBottom -= offset;
                //
                //        hero_S.move(0, -ballSpeed);
                //    }
                //}
                //else {
                //    hero_S.move(0, -ballSpeed);
                //}
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (pl.onGround) {
                    pl.speedY = -1.2;
                    pl.onGround = false;
                }
            }

            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            //    mainPlayer.player_S.setScale(2, 2);
            //}

            //if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            //    mainPlayer.player_S.setScale(0.5, 0.5);
            //    
            //}

        }
        window.clear();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'A' || TileMap[i][j] == 'B') {
                    block_S.setPosition(j * size_texture, i * size_texture);
                    window.draw(block_S);
                }
            }
        }
        pl.update(time, window, view);
        window.draw(pl.player_S);
        window.display();
    }
    return 0;
}