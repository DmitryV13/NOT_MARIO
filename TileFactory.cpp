#include "stdafx.h"
#include "TileFactory.h"

class coord {
public:
    int x[20];
    int y[20];
    int size;

    coord(float xb[], float yb[], int s){
        size = s;
        for (int i = 0; i < size; ++i) {
            x[i] = xb[i];
            y[i] = yb[i];
        }
    }

    coord(std::vector<float> xb, std::vector<float> yb, int s){
        size = s;
        for (int i = 0; i < size; ++i) {
            x[i] = xb[i];
            y[i] = yb[i];
        }
    }
};

sf::IntRect TileFactory::initRect_tile(char tile_C) {
    if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
    if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60); }
    if (tile_C == 'C') { return sf::IntRect(2, 66, 60, 60); }
    if (tile_C == 'c') { return sf::IntRect(2, 130, 60, 60); }
    if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60); }
    if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60); }
    if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60); }
}

//hills
coord* TileFactory::generationF1() {
    float y[20];
    float x[20];

    float shift = 20 + rand() % (30 - 20 + 1);
    float incline = 0.0 + (1.0 - 0.0) * (static_cast<double>(rand()) / RAND_MAX);
    float waveSize = 0.1 + (0.5 - 0.1) * (static_cast<double>(rand()) / RAND_MAX);
    //{0,1} - incline
    //{20,30} - shift

    for (float i = 0, j = 0; j < 20; i += 0.2, j++) {
        x[(int)j] = i * 3.1415;
    }

    for (int i = 0; i < 20; i++) {
        y[i] = sin((x[i]*waveSize) / 0.7 + shift) - cos(x[i] + 3) +incline * x[i];
    }
    float startPointRange = 25 - y[19];
    float rangeExpansionX = 1.67;
    int startCoef = rand() % ((int)startPointRange + 1);


    for (int i = 0; i < 20; ++i) {
        x[i] = (int)(x[i] * rangeExpansionX);
        y[i] = (int)(y[i] * 1 + (8 + startCoef));
    }
    coord* res = new coord(x, y, 20);
    return res;
}

//highway
coord* TileFactory::generationF2() {
    float y[20];
    float x[20];

    float waveSize = 0.5 + (0.8 - 0.5) * (static_cast<double>(rand()) / RAND_MAX);
    float halfMaxHeight = cos(0) * waveSize;
    float startPointRange = 25 - halfMaxHeight * 2;
    int startCoef = rand() % ((int)startPointRange + 1);
    float incline = 0.0 + (0.2 - 0.0) * (static_cast<double>(rand()) / RAND_MAX);
    int shift = rand() % (11 + 1);
    //{0.0, startPointRange} startCoef
    //{0, 0.2} incline
    //{0, 11} shift
    //{0.5, 0.8} wave size

    for (float i = 0, j = 0; j < 20; i += 0.2, j++) {
        x[(int)j] = i * 3.1415;
    }

    for (int i = 0; i < 20; i++) {
        y[i] = cos(x[i] + shift) * waveSize + incline * x[i] + halfMaxHeight;
    }

    for (int i = 0; i < 20; ++i) {
        x[i] = (int)(x[i] * 1.67);
        y[i] = (int)(y[i] * 1 + (8 + startCoef));
    }

    coord* res = new coord(x, y, 20);
    return res;
}

//downhill
coord* TileFactory::generationF3() {
    int size = 2 + rand() % (7 - 2 + 1);
    std::vector<float> y(size);
    std::vector<float> x(size);

    //{2, 10} incline

    for (int i = 0; i < size; i++) {
        x[i] = i;
    }

    float startPointRange = 25 - x[size - 1] / 2;
    int startCoef = rand() % ((int)startPointRange + 1);
    int incline = 2 + rand() % (10 - 2 + 1);

    for (int i = 0; i < size; i++) {
        y[i] = x[i] / incline;
    }

    for (int i = 0; i < size; ++i) {
        y[i] = (int)(y[i] * 1 + (8 + startCoef));
    }

    coord* res = new coord(x, y, size);
    return res;
}

//road
coord* TileFactory::generationF4() {
    int size = 2 + rand() % (5 - 2 + 1);
    //{5, 10} size
    std::vector<float> y(size);
    std::vector<float> x(size);

    int startCoef = 7 + rand() % ((int)32 - 7 + 1);

    for (int i = 0; i < size; i++) {
        x[i] = i;
    }

    for (int i = 0; i < size; ++i) {
        y[i] = startCoef;
    }

    coord* res = new coord(x, y, size);
    return res;
}

coord* generationPBF1(int scatter) {
    std::vector<float> x(scatter);
    std::vector<float> y(scatter);
    float ampl = scatter > 7 ? 0.2 : 0.1;
    float offset = scatter > 7 ? 5.0 : 2.5;
    for (int i = 0; i < scatter; i++) {
        x[i] = 10.0/scatter * i;
    }

        for (int i = scatter/2; i < scatter-1; i++){
            x[i] = x[i + 1];
        }
        x[scatter - 1] = 10;

    for (int i = 0; i < scatter; i++) {
        y[i] =  ( - ampl * ((x[i] - 5) * (x[i] - 5))) + offset;
    }

    coord* res = new coord(x, y, scatter);
    return res;
}

void filterPBF1(int target[], int n, int ground[], int begI) {
    for (int i = 0, j=begI; i < n; i++, j++) {
        if (ground[j] - target[i]<=2) {
            target[i] -= 2;
        }
    }
}

//coord* filterPBF2(int taregt[], int n, int ground[], int begI, int endI) {
//
//}

coord* TileFactory::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 100);
    int algorithm_number = distribution(gen);
    if (0 <= algorithm_number && algorithm_number <= 70)
        return generationF1();
    if (70 < algorithm_number && algorithm_number <= 80)
        return generationF2();
    if (80 < algorithm_number && algorithm_number <= 90)
        return generationF3();
    if (90 < algorithm_number && algorithm_number <= 100)
        return generationF4();
}

void TileFactory::generation_map(char map[40][200]) {

}

//7-20 lakes
std::vector<std::pair<int, int>> lakesGeneration(int y[], int n) {
    int favorablePlaces=0;
    bool notOnLevelBeforeS;//seven
    bool notOnLevelAfterS;
    std::vector<std::pair<int, int>> beginEndCord;
    for (int i = 0; i+20 < 200; ) {
        notOnLevelAfterS = true;
        notOnLevelBeforeS = false;

        for (int j = 1; j < 8; j++) {
            if (y[i] > y[i + j]) {
                i += j;
                notOnLevelBeforeS = true;
                break;
            }
        }
        if (notOnLevelBeforeS) {
            notOnLevelBeforeS = false;
            continue;
        }
        for (int j = 8; j < 21; j++){
            if (y[i] > y[i + j]) {
                notOnLevelAfterS = false;
                beginEndCord.push_back({i, i + j });
                i += j;
                break;
            }
        }
        if (notOnLevelAfterS) {
            i += 20;
            continue;
        }
    }
    return beginEndCord;
}

void platformGeneration(int y[200], int x[200], char map[40][200]) {
    std::vector<std::pair<int, int>> beginEndCord;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution1(3, 15);
    int numberOfPlatforms = distribution1(gen);

    std::cout << numberOfPlatforms << std::endl;

    for (int i = 0; i < numberOfPlatforms; i++) {
        std::uniform_int_distribution<int> distributionW(5,6);
        int width = distributionW(gen);

        std::uniform_int_distribution<int> distributionInd(0, 199-width);
        int firstIndex = distributionInd(gen);

        std::uniform_int_distribution<int> distributionIndHeight(3, y[firstIndex] - width>3 ? y[firstIndex] - width : y[firstIndex]);
        int initHeight = distributionIndHeight(gen);

        //firstIndex + k  -  index for x array
        //initHeight+j  -  index for map matrix
        

        
        for (int k = 0; k < width; k++) {
                map[initHeight][x[firstIndex + k]] = 'A';
        }


        coord* tmp = generationPBF1(width);
        filterPBF1(tmp->y, tmp->size, y, firstIndex);

        for (int k = 0; k < width; k++){
            for (int l = initHeight; l < initHeight + tmp->y[k]; l++) {
                map[l][x[firstIndex + k]] = 'A';
            }
        }
        free(tmp);
        std::cout << std::endl;
    }
}    

TileFactory::TileFactory() {
    srand(static_cast<unsigned int>(time(nullptr)));
    char map[40][200];
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 200; ++j) {
            map[i][j] = ' ';
        }
    }

    int xF[200];
    int yF[200];
    for (int i = 0; i < 200; ++i) {
        xF[i] = 0;
        yF[i] = 0;
    }
    coord* initCord = generationF4();

    for (int i = 0; i < initCord->size; ++i) {
        xF[i] = initCord->x[i];
        yF[i] = initCord->y[i];
    }
    int i = initCord->size;
    free(initCord);

    for (; i < 200; ) {
        coord* cord = generate();
        int Ampl = cord->y[cord->size - 1] - cord->y[0];
        int offsetPos = yF[i - 1] - cord->y[0];
        int offsetNeg = yF[i - 1] - cord->y[cord->size - 1];

        if (yF[i - 1] + Ampl < 33) {
            for (int j = 0; j < cord->size && i < 200; ++j, i++) {
                xF[i] = i;
                yF[i] = cord->y[j] + offsetPos;
            }
        }
        else {
            for (int j = cord->size - 1; j >= 0 && i < 200; --j, i++) {
                xF[i] = i;
                yF[i] = cord->y[j] + offsetNeg;
            }
        }
        free(cord);
    }

    
    std::vector<std::pair<int, int>> tmp= lakesGeneration(yF, 200);
   //for (int  i = 0; i < tmp.size(); i++)
   //{
   //    std::cout << xF[tmp[i].first] << "," << yF[tmp[i].first] << " - " << xF[tmp[i].second] <<","<< yF[tmp[i].second]<< std::endl;
   //}

    for (int j = 0; j < 200; ++j) {
        map[yF[j]][xF[j]] = 'A';
        for (int i = yF[j]+1; i < 40; i++){
            map[i][xF[j]] = 'B';
        }
    }
    //earth contour
    //for (int i = 0; i < tmp.size(); i++) {
    //    for (int j = tmp[i].first+1; j < tmp[i].second; j++) {
    //        //std::cout << xF[tmp[i].first] << "," << yF[tmp[i].first] << " - " << xF[tmp[i].second] << "," << yF[tmp[i].second] << std::endl;
    //        map[yF[j]][xF[j]] = 'C';
    //    }
    //}

    for (int i = 0; i < tmp.size(); i++) {
        int constY = tmp[i].first;
        for (int j = tmp[i].first + 1; j < tmp[i].second-1; j++) {
            map[yF[constY]][xF[j]] = 'C';
        }
        int constL = 1;
        int constR = -1;
        short limBL=0, limBR=1;
        short lakeWidth = tmp[i].second - tmp[i].first;
        if(lakeWidth > 15) {
            limBL = 1;
            limBR = 2;
        }
        for (int k = 1; k < lakeWidth / 3; k++) {
           // int size = 2 + rand() % (5 - 2 + 1);
            
            int left = limBL + rand() % (limBR - limBL + 1);
            int right = limBL + rand() % (limBR - limBL + 1);
            constL += left;
            constR -= right;
            for (int j = tmp[i].first + constL; j < tmp[i].second + constR; j++) {
                map[yF[constY] + k][xF[j]] = 'c';
            }
        }
        for (int k = 0; k < lakeWidth; k++) {
            for (int j = tmp[i].first + 1; j < tmp[i].second - 1; j++) {
                if (map[yF[constY] + k][xF[j]] == ' ')
                    map[yF[constY] + k][xF[j]] = 'c';
            }
        }
    }

    platformGeneration(yF, xF, map);
    //std::cout << "UFUUFUIFUFYIFYFYIFYIFIYFFUIIFUUIUI";
    //for (int i = 0; i < 40; i++) {
    //    for (int j = 0; j < 200; j++) {
    //        std::cout << map[i][j];
    //    }
    //    std::cout << std::endl;
    //}

    // A - grass upward
    // B - earth
    // C - grass left
    // D - grass right
    // L - left top
    // P - right top
    // l - left top small
    // p - right top small

    Tile tile_A(initRect_tile('A'), 'A', 'A');
    Tile tile_B(initRect_tile('B'), 'B', 'B');
    Tile tile_C(initRect_tile('C'), 'C', 'C');
    Tile tile_c(initRect_tile('c'), 'c', 'c');
    Tile tile_D(initRect_tile('D'), 'D', 'D');
    Tile tile_L(initRect_tile('L'), 'L', 'L');
    Tile tile_P(initRect_tile('P'), 'P', 'P');

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            if (map[i][j] == 'A') { tile_map_inFactory[i][j] = tile_A; }
            if (map[i][j] == 'B') { tile_map_inFactory[i][j] = tile_B; }
            if (map[i][j] == 'C') { tile_map_inFactory[i][j] = tile_C; }
            if (map[i][j] == 'c') { tile_map_inFactory[i][j] = tile_c; }
            if (map[i][j] == 'D') { tile_map_inFactory[i][j] = tile_D; }
            if (map[i][j] == 'L') { tile_map_inFactory[i][j] = tile_L; }
            if (map[i][j] == 'P') { tile_map_inFactory[i][j] = tile_P; }
        }
    }
}