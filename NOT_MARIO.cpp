#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

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
    window.
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
    float ballSpeed = 300;

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
                if (spritePosition.y + ball_S.getLocalBounds().height + ballSpeed >= windowBottom) {
                    if (spritePosition.y + ball_S.getLocalBounds().height + ballSpeed >= absoluteBottom) {
                        windowBottom = absoluteBottom;
                        windowTop = absoluteBottom-screenHeight;
                        spritePosition.y = absoluteBottom - ball_S.getLocalBounds().height;
                        ball_S.setPosition(spritePosition);
                        view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                        window.setView(view);
                    }
                    else {
                        float offset = ballSpeed - (windowBottom - (spritePosition.y + ball_S.getLocalBounds().height));
                        view.move(0, offset);
                        window.setView(view);

                        windowTop += offset;
                        windowBottom += offset;

                        ball_S.move(0,ballSpeed);
                    }
                }
                else {
                    ball_S.move(0,ballSpeed);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (spritePosition.x + ball_S.getLocalBounds().width + ballSpeed >= windowRight) {
                    if (spritePosition.x + ball_S.getLocalBounds().width + ballSpeed  >= absoluteRight) {
                        windowLeft = absoluteRight-screenWidth;
                        windowRight = absoluteRight;
                        spritePosition.x = absoluteRight - ball_S.getLocalBounds().width;
                        ball_S.setPosition(spritePosition);
                        view.setCenter(windowRight-(screenWidth/2),windowBottom-(screenHeight/2));
                        window.setView(view);
                    }
                    else {
                        float offset = ballSpeed - (windowRight - (spritePosition.x + ball_S.getLocalBounds().width));
                        view.move(offset, 0);
                        window.setView(view);

                        windowLeft += offset;
                        windowRight += offset;

                        ball_S.move(ballSpeed, 0);
                    }
                }
                else {
                    ball_S.move(ballSpeed, 0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (spritePosition.x - ballSpeed <= windowLeft) {
                    if (spritePosition.x - ballSpeed <= absoluteLeft) {
                        windowLeft = absoluteLeft;
                        windowRight = absoluteLeft+screenWidth;
                        spritePosition.x = absoluteLeft;
                        ball_S.setPosition(spritePosition);
                        view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                        window.setView(view);
                    }
                    else {
                        float offset = ballSpeed - (spritePosition.x - windowLeft);
                        view.move(-offset, 0);
                        window.setView(view);
                        windowLeft -= offset;
                        windowRight -= offset;

                        ball_S.move(-ballSpeed, 0);
                    }
                }
                else {
                    ball_S.move(-ballSpeed, 0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (spritePosition.y - ballSpeed <= windowTop) {
                    if (spritePosition.y - ballSpeed <= absoluteTop) {
                        windowBottom = absoluteTop+screenHeight;
                        windowTop = absoluteTop;
                        spritePosition.y = absoluteTop;
                        ball_S.setPosition(spritePosition);
                        view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                        window.setView(view);
                    }
                    else {
                        float offset = ballSpeed - (spritePosition.y - windowTop);
                        view.move(0, -offset);
                        window.setView(view);
                        windowTop -= offset;
                        windowBottom -= offset;

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