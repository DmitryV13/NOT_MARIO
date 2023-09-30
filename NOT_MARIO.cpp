#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    shape.setPosition(400, 400);
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//                shape.move(0, 5);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//                shape.move(5, 0);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//                shape.move(-5, 0);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//                shape.move(0, -5);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
//                shape.setScale(2, 2);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
//                shape.setScale(0.5, 0.5);
//            }
//            
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}
//
#include <SFML/Graphics.hpp>

const int H = 10;
const int W = 100;
const int size_texture = 60;

std::string TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                                                                                  A",
    "A                                                                                                  A",
    "A                                                                                                  A",
    "A         BB                                                              BB                       A",
    "A        BBBBBB    BB                                 BBBBBB            BBBBBB      BB             A",
    "A      BBBBBBBBBBBBBBBB              BBBBB           BBBBBBBBB  B  BB  BBBBBBBBBB BBBBBB           A",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
};

//  Keys for control
// W - forward
// S - backward
// A - left
// D - right
// Q - enlarge
// E - shrink

int main()
{
    //window characteristics
    const int screenHeight = 600;
    const int screenWidth = 1500;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "NOT_MARIO");

    // window, which will see usual user
    sf::View view;
    view.reset(sf::FloatRect(0, 0, screenWidth, screenHeight));
    window.setView(view);

    // textures
    sf::Texture block_T;
    sf::Texture ball_T;

    if (!ball_T.loadFromFile("Images/ball.png")) {
        return -1;
    }

    if (!block_T.loadFromFile("Images/cube.jpg")) {
        return -1;
    }

    // characteristics of map
    float absoluteLeft = 0.0f;
    float absoluteTop = 0.0f;
    float absoluteRight = W * size_texture;
    float absoluteBottom = H * size_texture;

    // characteristics of window
    float windowLeft = 0.0f;
    float windowTop = 0.0f;
    float windowRight = static_cast<float>(window.getSize().x);
    float windowBottom = static_cast<float>(window.getSize().y);

    // game-area variables
    int ballSpeed = 10;

    // sprites
    sf::Sprite block_S(block_T);
    sf::Sprite ball_S(ball_T);
    block_S.setTextureRect(sf::IntRect(4, 4, size_texture, size_texture));
    ball_S.setPosition(0, 0);

    //  ---------GAME_CODE----------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2f spritePosition = ball_S.getPosition();

            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (spritePosition.y + ball_S.getLocalBounds().height >= windowBottom) {
                    if (spritePosition.y + ball_S.getLocalBounds().height >= absoluteBottom) {
                        windowBottom = absoluteBottom;
                        windowTop = absoluteBottom-screenHeight;
                        spritePosition.y = absoluteBottom - ball_S.getLocalBounds().height;
                    }
                    else {
                        view.move(0,ballSpeed);
                        window.setView(view);

                        windowTop += ballSpeed;
                        windowBottom += ballSpeed;

                        ball_S.move(0,ballSpeed);
                    }
                }
                else {
                    ball_S.move(0,ballSpeed);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (spritePosition.x + ball_S.getLocalBounds().width >= windowRight) {
                    if (spritePosition.x + ball_S.getLocalBounds().width >= absoluteRight) {
                        windowLeft = absoluteRight-screenWidth;
                        windowRight = absoluteRight;
                        spritePosition.x = absoluteRight - ball_S.getLocalBounds().width;
                    }
                    else {
                        view.move(ballSpeed, 0);
                        window.setView(view);

                        windowLeft += ballSpeed;
                        windowRight += ballSpeed;

                        ball_S.move(ballSpeed, 0);
                    }
                }
                else {
                    ball_S.move(ballSpeed, 0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (spritePosition.x <= windowLeft) {
                    if (spritePosition.x <= absoluteLeft) {
                        windowLeft = absoluteLeft;
                        windowRight = absoluteLeft+screenWidth;
                        spritePosition.x = absoluteLeft;
                    }
                    else {
                        view.move(-ballSpeed, 0);
                        window.setView(view);

                        windowLeft -= ballSpeed;
                        windowRight -= ballSpeed;

                        ball_S.move(-ballSpeed, 0);
                    }
                }
                else {
                    ball_S.move(-ballSpeed, 0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (spritePosition.y <= windowTop) {
                    spritePosition.y = windowTop;
                }
                else {
                    ball_S.move(0, -ballSpeed);
                }
                if (spritePosition.y <= windowTop) {
                    if (spritePosition.y <= absoluteTop) {
                        windowBottom = absoluteTop+screenHeight;
                        windowTop = absoluteTop;
                        spritePosition.y = absoluteTop;
                    }
                    else {
                        view.move(0, -ballSpeed);
                        window.setView(view);

                        windowTop -= ballSpeed;
                        windowBottom -= ballSpeed;

                        ball_S.move(0, -ballSpeed);
                    }
                }
                else {
                    ball_S.move(0, -ballSpeed);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                ball_S.setScale(2, 2);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                ball_S.setScale(0.5, 0.5);
            }

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

        window.draw(block_S);
        window.draw(ball_S);
        window.display();
    }
    return 0;
}