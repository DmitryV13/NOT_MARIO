#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Player.h"
#include "Map.h"
#include "MyView.h"
#include <chrono>

using sf::Clock;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::View;
using std::cout;
using std::endl;


const int H = 20;
const int W = 100;
const int size_texture = 73;

std::string TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                                    FF                                            A",
    "A                                               FF                                                 A",
    "A                                           FF                                                     A",
    "A                                                                                                  A",
    "A                                    FFFFFFF                                                       A",
    "A                                   FF                                                             A",
    "A                             FF   FF                                                              A",
    "A                                                                                                  A",
    "A                        FFFFFF                                                                    A",
    "A                             FF                                                                   A",
    "A                              FF                                                                  A",
    "A                               FFF                                                                A",
    "A                                    FFF                                                           A",
    "A                                         FFFF                                                     A",
    "A                                           FFFF                                                   A",
    "AG                 EFFFF       FFFFG                                                              FA",
    "AJKCCLHF    CCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AFFFFFFF   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AIIIIIIIAAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIA",
};


//window characteristics
const int screenHeight = 600;
const int screenWidth = 1500;    

// characteristics of map
double absoluteLeft = 0.0f;
double absoluteTop = 0.0f;
double absoluteRight = W * size_texture;
double absoluteBottom = H * size_texture;

// characteristics of window
double windowLeft = 0.0f;
double windowTop = 0.0f;
double windowRight = 1500.0f;
double windowBottom = 600.0f;

//  Keys for control
// W - forward
// S - backward
// A - left
// D - right
// Q - enlarge
// E - shrink

int main()
{


    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO");

    // window, which will see usual user
   //sf::View view;
   //view.reset(sf::FloatRect(0, 900, screenWidth, screenHeight));
    

    // textures
    sf::Texture block_T;
    sf::Texture hero_T;

    if (!hero_T.loadFromFile("Images/hero.png")) {
        return -1;
    }

    if (!block_T.loadFromFile("Images/earth.png")) {
        return -1;
    }



    // game-area variables
    double ballSpeed = 4.2;

    // sprites
    sf::Sprite block_S(block_T);


    Map map(H, W, size_texture, TileMap);

    MyView gameView(map, windowRight, windowBottom, screenWidth, screenHeight);

    window.setView(gameView.view);
    window.setFramerateLimit(144);
    Player player_1(hero_T, window, map);

    Clock clock;
    //  ---------GAME_CODE----------
    while (window.isOpen())
    {

        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player_1.speedX = ballSpeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player_1.speedX = -ballSpeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (player_1.onGround) {
                    player_1.speedY = -0.4;
                    player_1.onGround = false;
                }
            }

        }
        window.clear(sf::Color::White);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                //std::cout << "i - " << i << std::endl << "j - " << j << std::endl;
                if (TileMap[i][j] == ' ') {
                    continue;
                }
                if (TileMap[i][j] == 'B') {
                    block_S.setTextureRect(sf::IntRect(97 + 3, 18 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'C') {
                    block_S.setTextureRect(sf::IntRect(183 + 3, 18 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'D') {
                    block_S.setTextureRect(sf::IntRect(267 + 3, 18 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'E') {
                    block_S.setTextureRect(sf::IntRect(97 + 3, 102 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'F') {
                    block_S.setTextureRect(sf::IntRect(183 + 3, 102 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'G') {
                    block_S.setTextureRect(sf::IntRect(267 + 3, 102 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'H') {
                    block_S.setTextureRect(sf::IntRect(97 + 3, 188 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'I') {
                    block_S.setTextureRect(sf::IntRect(183 + 3, 188 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'J') {
                    block_S.setTextureRect(sf::IntRect(267 + 3, 188 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'K') {
                    block_S.setTextureRect(sf::IntRect(352 + 3, 182 + 7, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'L') {
                    block_S.setTextureRect(sf::IntRect(13 + 3, 188 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'M') {
                    block_S.setTextureRect(sf::IntRect(352 + 3, 272 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'N') {
                    block_S.setTextureRect(sf::IntRect(13 + 3, 272 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'O') {
                    block_S.setTextureRect(sf::IntRect(97 + 3, 272 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'P') {
                    block_S.setTextureRect(sf::IntRect(183 + 3, 272 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'Q') {
                    block_S.setTextureRect(sf::IntRect(267 + 3, 272 + 3, size_texture, size_texture));
                    block_S.setPosition(j * size_texture, i * size_texture);
                }
                if (TileMap[i][j] == 'A') {
                    continue;
                }
                if (TileMap[i][j] == '0') {
                    block_S.setTextureRect(sf::IntRect(454, 32, 45, 45));
                    block_S.setPosition(j * size_texture, i * size_texture + 30);
                }
                if (TileMap[i][j] == '1') {
                    block_S.setTextureRect(sf::IntRect(514, 39, 35, 37));
                    block_S.setPosition(j * size_texture, i * size_texture + 37);
                }
                if (TileMap[i][j] == '7') {
                    block_S.setTextureRect(sf::IntRect(445, 90, 170, 180));
                    block_S.setPosition(j * size_texture, i * size_texture - 104);
                }
                if (TileMap[i][j] == '8') {
                    block_S.setTextureRect(sf::IntRect(618, 105, 170, 170));
                    block_S.setPosition(j * size_texture, i * size_texture - 90);
                }
                if (TileMap[i][j] == '9') {
                    block_S.setTextureRect(sf::IntRect(478, 300, 80, 38));
                    block_S.setPosition(j * size_texture, i * size_texture + 35);
                }
                if (TileMap[i][j] == ')') {
                    block_S.setTextureRect(sf::IntRect(566, 300, 80, 38));
                    block_S.setPosition(j * size_texture, i * size_texture + 35);
                }
                window.draw(block_S);
            }
        }
        player_1.update(time, window);
        gameView.updateView(player_1.coordinates);
        window.setView(gameView.view);
        window.draw(player_1.player_S);
        window.display();
    }
    return 0;
}

