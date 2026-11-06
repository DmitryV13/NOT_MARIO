#include "stdafx.h"
#include "game/Game.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    Game game;
    game.start();
    std::cout << sizeof(game) << std::endl;
    return 0;
}