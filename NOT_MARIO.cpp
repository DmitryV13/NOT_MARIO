#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
const int H = 20;
const int W = 100;
const int size_texture = 73;
const int screenHeight = 600;
const int screenWidth = 1500;

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
enum Direction { Left, Right };
Direction gostDirection = Right;  
Direction zombiDirection = Right; 

class Enemy
{
public:
    virtual void set(int x, int y) = 0;
    virtual void update(float time, float y) = 0;
    void Collision();

    sf::Sprite enemy_S;
    sf::Texture enemy_T;
    sf::FloatRect rect;
    float currentFrame;
    float dx, dy;
    float HP;
    float power;
    bool life;
};

class Gost : public Enemy
{
public:
    void set(int x, int y) override;
    void update(float time, float y) override;
    Gost() :Enemy() {
        HP = 100;
        dx = 0.01;
        dy = 0.01;
        power = 20;
        life = true;
    }

    ~Gost() = default;
    //void battle(float HP_PLAYER, float power_player);
    //void MoveEnemy(std::string map[H], float startX, int startY);
};
class Zombi:public  Enemy
{
public:
    void set(int x, int y) override;
    void update(float time, float y) override;
    Zombi() :Enemy() {
        HP = 300;
        dx = 0.02;
        dy = 0.02;
        power = 50;
        life = true;
    }
    ~Zombi() = default;

private:

};



void Gost::set(int x, int y)
{

    enemy_S.setTexture(enemy_T);
    rect = sf::FloatRect(x, y, 60, 60);
    currentFrame = 0;

}
void Zombi::set(int x, int y)
{

    enemy_S.setTexture(enemy_T);
    rect = sf::FloatRect(x, y, 20, 60);
    currentFrame = 0;


}
void Gost::update(float time, float y)
{

    rect.top = y;
    rect.left += dx * time;
    Collision();
    //currentFrame += time * 0.005;
     //if (currentFrame > 2)currentFrame -= 2;
    if (dx > 0) {
        gostDirection = Right;
    }
    else if (dx < 0) {
        gostDirection = Left;
    }
    if (gostDirection == Left) {
        enemy_S.setTextureRect(sf::IntRect(60, 0, -60, 60));
    }
    else {
        enemy_S.setTextureRect(sf::IntRect(0, 0, 60, 60));

    }
     
   
    enemy_S.setPosition(rect.left, rect.top);

}
void Zombi::update(float time, float y)
{
    rect.top = y;
    float newX = rect.left + dx * time;
    bool collisionDetected = false;

    if (newX >= 0 && newX <= (W * size_texture - rect.width)) {
       
        for (int j = (int)(newX / size_texture); j < (int)((newX + rect.width) / size_texture); j++) {
            for (int i = (int)(rect.top / size_texture); i < (int)((rect.top + rect.height) / size_texture); i++) {
                if (TileMap[i][j + 1] == 'B' || TileMap[i][j] == 'G' || TileMap[i][j] == 'D' || TileMap[i][j] == 'E' || TileMap[i][j] == '9' || TileMap[i][j] == 'F') {
                    collisionDetected = true;
                    break;
                }
            }
            if (collisionDetected) {
                break;
            }
        }
    }
    else {
        collisionDetected = true; 
    }

    if (collisionDetected) {
        dx = -dx; 
        if (dx > 0) {
            zombiDirection = Right;
        }
        else if (dx < 0) {
            zombiDirection = Left;
        }
    }
    else {
       
        rect.left = newX;
    }

    Collision();

    currentFrame += time  * 0.002;
    if (currentFrame > 5) currentFrame -= 5;

    
    if (dx > 0) {
        zombiDirection = Right;
    }
    else if (dx < 0) {
        zombiDirection = Left;
    }
    if (zombiDirection == Left) {

        enemy_S.setTextureRect(sf::IntRect(50 * int(currentFrame), 0, -50, 60));
    }
    else {

        enemy_S.setTextureRect(sf::IntRect(50 * int(currentFrame), 0, 50, 60));
    }
    enemy_S.setPosition(rect.left, rect.top);

}
void Enemy::Collision()
{
    for (int j = (int)(rect.left / size_texture); j < (int)((rect.left + rect.width) / size_texture); j++) {
        for (int i = (int)(rect.top / size_texture); i < (int)((rect.top + rect.height) / size_texture); i++) {
            if (TileMap[i][j + 1] == 'B' || TileMap[i][j] == 'G'|| TileMap[i][j] == 'D'|| TileMap[i][j] == 'E'|| TileMap[i][j] == '9'|| TileMap[i][j] == 'F') {


                dx = -dx;
                return;
            }
        }
    }
}
/*
void Gost::MoveEnemy(std::string map[H], float startX, int startY) {
    int lookAhead = 3; 
    bool obstacleAhead = false;
    update(startX, startY);
   
    for (int i = 1; i <= lookAhead; ++i) {
        int nextX = (int)(rect.left / size_texture) + i;
        int nextY = (int)(rect.top / size_texture);

        if (nextX >= W) {
            break;
        }

  
        if (map[nextY][nextX] == 'B') {
            obstacleAhead = true;

            
            int maxHeight = 3;
            int checkX = nextX;
            int checkY = nextY - 1;

            while (checkY >= 0 && map[checkY][checkX] == 'B') {
                --checkY;
                --maxHeight;
            }

            if (maxHeight > 0) {
              
                dy = -0.2;
                break;
            }
            else {
               
                dx = -dx;
                break;
            }
        }
    }

    
    if (!obstacleAhead) {
        return;
    }
}*/


//  Keys for control
// W - forward
// S - backward
// A - left
// D - right
// Q - enlarge
// E - shrink

int main()
{
    Gost gost;
    Zombi zombi;
    sf::Clock clock;
    //window characteristics
   

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
    //
    // 
    // 
    // 
    // 
    // //
 
    if (!gost.enemy_T.loadFromFile("Images/gost.png")) {
        return -1;
    }
    gost.set(225, 1200);
    if (!zombi.enemy_T.loadFromFile("Images/zombi.png")) {
        return -1;
    }
    zombi.set(877, 1200);
    
   
    ////
    // 
    // 
    // 
    // 
    // 
    //

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
    //block_S.setTextureRect(sf::IntRect(183, 18, size_texture, size_texture));
    ball_S.setPosition(0, 0);

    //  ---------GAME_CODE----------
    while (window.isOpen())
    {
        //
        // 
        // 
        // 
        // 
        // 
        // //
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        if (time > 20) time = 20;
   
        zombi.update(time, 1200);
        gost.update(time,1200);
        //gost.MoveEnemy(TileMap, time, 1200);
        ////
        // 
        // 
        // 
        // 
        // 
        // //
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
            window.clear(sf::Color::White);
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
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
                        block_S.setTextureRect(sf::IntRect(352 + 3, 182 + 3, size_texture, size_texture));
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
            window.draw(gost.enemy_S);
            window.draw(zombi.enemy_S);
            window.draw(ball_S);
            window.display();
    }
    return 0;
}