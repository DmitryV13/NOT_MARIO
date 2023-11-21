#include "stdafx.h"//for each class
#include "Game.h"

using sf::Clock;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::View;
using std::cout;
using std::endl;




int main() {
    srand(static_cast<unsigned>(time(0)));

    Game game;
    game.start();

    return 0;
}