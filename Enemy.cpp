#include "Enemy.h"
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
void Enemy::collision()
{
    for (int j = static_cast<int>(rect.left / size_texture); j < static_cast<int>((rect.left + rect.width) / size_texture); j++) {
        for (int i = static_cast<int>(rect.top / size_texture); i < static_cast<int>((rect.top + rect.height) / size_texture); i++) {
            if (TileMap[i][j + 1] == 'B' || TileMap[i][j+1] == 'G' || TileMap[i][j + 1] == 'D' || TileMap[i][j + 1] == 'E' ||
                TileMap[i][j + 1] == 'F') {


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
