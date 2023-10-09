#include <SFML/Graphics.hpp>


const int H = 20;
const int W = 100;
const int size_texture = 73;

class Map {
private:
    struct Node {
        char front_block;
        char back_block;
        short int matrix;
        Node() {
            this->front_block = ' ';
            this->back_block = ' ';
            this->matrix = 0;
        }
    };
    Node* pos;
public:
    Map() {
        pos = new Node{};
    }
    short int get_matrix() {
        return pos->matrix;
    }
    char get_front_block() {
        return pos->front_block;
    }
    char get_back_block() {
        return pos->back_block;
    }
    void map_build(char block) {
        pos->front_block = block;
    }
    sf::Sprite map_paint(int i, int j, sf::Sprite block_S) {
        if (pos->front_block == 'B') {
            block_S.setTextureRect(sf::IntRect(97 + 3, 18 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'C') {
            block_S.setTextureRect(sf::IntRect(183 + 3, 18 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);           
        }
        if (pos->front_block == 'D') {
            block_S.setTextureRect(sf::IntRect(267 + 3, 18 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'E') {
            block_S.setTextureRect(sf::IntRect(97 + 3, 102 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'F') {
            block_S.setTextureRect(sf::IntRect(183 + 3, 102 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'G') {
            block_S.setTextureRect(sf::IntRect(267 + 3, 102 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'H') {
            block_S.setTextureRect(sf::IntRect(97 + 3, 188 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'I') {
            block_S.setTextureRect(sf::IntRect(183 + 3, 188 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'J') {
            block_S.setTextureRect(sf::IntRect(267 + 3, 188 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'K') {
            block_S.setTextureRect(sf::IntRect(352 + 3, 182 + 7, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'L') {
            block_S.setTextureRect(sf::IntRect(13 + 3, 188 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'M') {
            block_S.setTextureRect(sf::IntRect(352 + 3, 272 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'N') {
            block_S.setTextureRect(sf::IntRect(13 + 3, 272 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'O') {
            block_S.setTextureRect(sf::IntRect(97 + 3, 272 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'P') {
            block_S.setTextureRect(sf::IntRect(183 + 3, 272 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == 'Q') {
            block_S.setTextureRect(sf::IntRect(267 + 3, 272 + 3, size_texture, size_texture));
            block_S.setPosition(j * size_texture, i * size_texture);            
        }
        if (pos->front_block == '0') {
            block_S.setTextureRect(sf::IntRect(454, 32, 45, 45));
            block_S.setPosition(j * size_texture, i * size_texture + 30);            
        }
        if (pos->front_block == '1') {
            block_S.setTextureRect(sf::IntRect(514, 39, 35, 37));
            block_S.setPosition(j * size_texture, i * size_texture + 37);            
        }
        if (pos->front_block == '7') {
            block_S.setTextureRect(sf::IntRect(445, 90, 170, 180));
            block_S.setPosition(j * size_texture, i * size_texture - 104);            
        }
        if (pos->front_block == '8') {
            block_S.setTextureRect(sf::IntRect(618, 105, 170, 170));
            block_S.setPosition(j * size_texture, i * size_texture - 90);            
        }
        if (pos->front_block == '9') {
            block_S.setTextureRect(sf::IntRect(478, 300, 80, 38));
            block_S.setPosition(j * size_texture, i * size_texture + 35);            
        }
        if (pos->front_block == ')') {
            block_S.setTextureRect(sf::IntRect(566, 300, 80, 38));
            block_S.setPosition(j * size_texture, i * size_texture + 35);           
        }
       return block_S;
    }
};

std::string TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                                                                                                   A",
    "A                 7                                                                                 A",
    "A                OPQ                                                                                A",
    "A     0  98            9 0                                                                          A",
    "A    BCCCCCCCCD        OPQ                                                                          A",
    "A)   EFFFFFFFFG                                                                                     A",
    "AD   NIIIIIIIIM    17 0  )                                                                          A",
    "AG      0          BCCCCCCCCD                                                                       A",
    "AG 19 BCCCD   0   9EFFFFFFFFG                                                                       A",
    "AJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIA",
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

    if (!ball_T.loadFromFile("Textures/Textures_map/ball.jpg")) {
        return -1;
    }

    if (!block_T.loadFromFile("Textures/Textures_map/earth.png")) {
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
    ball_S.setPosition(0, 0);

    // build Map
    Map TilMap[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            TilMap[i][j].map_build(TileMap[i][j]);
        }
    }

    //  ---------GAME_CODE----------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (spritePosition.y + ball_S.getLocalBounds().height >= windowBottom) {
                    if (spritePosition.y + ball_S.getLocalBounds().height >= absoluteBottom) {
                        windowBottom = absoluteBottom;
                        windowTop = absoluteBottom - screenHeight;
                        spritePosition.y = absoluteBottom - ball_S.getLocalBounds().height;
                    }
                    else {
                        view.move(0, ballSpeed);
                        window.setView(view);

                        windowTop += ballSpeed;
                        windowBottom += ballSpeed;

                        ball_S.move(0, ballSpeed);
                    }
                }
                else {
                    ball_S.move(0, ballSpeed);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (spritePosition.x + ball_S.getLocalBounds().width >= windowRight) {
                    if (spritePosition.x + ball_S.getLocalBounds().width >= absoluteRight) {
                        windowLeft = absoluteRight - screenWidth;
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
                        windowRight = absoluteLeft + screenWidth;
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
                        windowBottom = absoluteTop + screenHeight;
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
        // Map rendering
        window.clear(sf::Color::White);
        for (int i = 0; i < H; i++){
            for (int j = 0; j < W; j++){
                if (TilMap[i][j].get_front_block() == ' ' || TilMap[i][j].get_front_block() == 'A') continue;
                window.draw(TilMap[i][j].map_paint(i, j, block_S)); 
            }
        }         
        window.draw(ball_S);
        window.display();
    }

    return 0;
}
// df,ldlfd