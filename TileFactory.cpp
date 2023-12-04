#include "stdafx.h"
#include "TileFactory.h"
#include <chrono>
    
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
    
    // A - grass upward
    // B - earth
    // C - grass left
    // D - grass right
    // L - left top
    // P - right top
    // l - left top small
    // p - right top small
    
    sf::IntRect TileFactory::initRect_tile(char tile_C) {
        //if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
        //if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60); }
        //if (tile_C == 'C') { return sf::IntRect(2, 66, 60, 60); }
        //if (tile_C == 'c') { return sf::IntRect(2, 130, 60, 60); }
        //if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60); }
        //if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60); }
        //if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60); }
        if (tile_C == 'A') { return sf::IntRect(60, 0, 60, 60); }
        if (tile_C == 'B') { return sf::IntRect(0, 0, 60, 60); }
        if (tile_C == 'C') { return sf::IntRect(0, 60, 60, 60); }
        if (tile_C == 'c') { return sf::IntRect(0, 120, 60, 60); }
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
    
    void filterPBF1(int target[], int n, int ground[], int begI) {
    for (int i = 0, j=begI; i < n; i++, j++) {
        if (ground[j] - target[i]<=2) {
            target[i] -= 2;
        }
    }
}
    
    coord* TileFactory::generate_landscape() {
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
    
    void TileFactory::generate_solid_surface(vector<int>& x, vector<int>& y, vector<vector<char>>& map) {
    coord* init_cord = generationF4();

    for (int i = 0; i < init_cord->size; ++i) {
        x[i] = init_cord->x[i];
        y[i] = init_cord->y[i];
    }
    int i = init_cord->size;
    free(init_cord);

    for (; i < m; ) {
        coord* cordinates = generate_landscape();
        int amplitude = cordinates->y[cordinates->size - 1] - cordinates->y[0];
        int offset_pos = y[i - 1] - cordinates->y[0];
        int offset_neg = y[i - 1] - cordinates->y[cordinates->size - 1];

        if (y[i - 1] + amplitude < 33) {
            for (int j = 0; j < cordinates->size && i < m; ++j, i++) {
                x[i] = i;
                y[i] = cordinates->y[j] + offset_pos;
            }
        }
        else {
            for (int j = cordinates->size - 1; j >= 0 && i < m; --j, i++) {
                x[i] = i;
                y[i] = cordinates->y[j] + offset_neg;
            }
        }
        free(cordinates);
    }

    //fill
    for (int j = 0; j < m; ++j) {
        for (int i = y[j]; i < n; i++) {
            map[i][x[j]] = 'B';
        }
    }
}
    
    void TileFactory::generation_map(vector<vector<char>>& map) {
        vector<int> x(m);
        vector<int> y(m);
        //int x[200];
        //int y[200];
        for (int i = 0; i < m; ++i) {
            x[i] = 0;
            y[i] = 0;
        }
        generate_solid_surface(x, y, map);
    
        std::vector<std::pair<int, int>> coords_for_water = lakes_generation(x, y, map);
    
        tunnels_generation(y, map);
    
        generate_platforms(x, y, map);
    
        fill_lakes(x, y, coords_for_water, map);
    
        texture_arrangement(map);
        
    }
    
    void TileFactory::fill_lakes(vector<int>& x, vector<int>& y, vector<pair<int, int>> coords_for_water, vector<vector<char>>& map) {
    for (int i = 0; i < coords_for_water.size(); i++) {
        fill_lake(y[coords_for_water[i].first], x[coords_for_water[i].first]+1, y[coords_for_water[i].first], map);


    }
}
    
    void TileFactory::fill_lake(int& water_level, int pos_x, int pos_y, vector<vector<char>>& map) {
    if (pos_x < 0 || pos_x >= m || pos_y < 0 || pos_y >= n) return;
    if (map[pos_y][pos_x] != ' ' || pos_y<water_level) return;

    map[pos_y][pos_x] = 'c';
    //moving down
    fill_lake(water_level, pos_x, pos_y + 1, map);
    //moving left
    fill_lake(water_level, pos_x - 1, pos_y, map);
    //moving up
    fill_lake(water_level, pos_x, pos_y - 1, map);
    //moving right
    fill_lake(water_level, pos_x + 1, pos_y, map);
}
    
    //lake width 7-20
    //lake's surface will cover empty blocks or blocks at the same level as initial block
    std::vector<std::pair<int, int>>  TileFactory::lakes_generation(vector<int>& x, vector<int>& y, vector<vector<char>>& map) {
    bool not_olbs;//not on level before seven
    bool not_olas;//not on level after seven
    short lake_min_width = 7;
    short lake_max_width = 20;

    std::vector<std::pair<int, int>> first_point_cords;

    //searching for suitable places
    for (int i = 0; i+lake_max_width < m; ) {
        not_olas = true;
        not_olbs = false;

        for (int j = 1; j < lake_min_width+1; j++) {
            if (y[i] > y[i + j]) {//signs are inverted
                i += j;
                not_olbs = true;
                break;
            }
        }
        if (not_olbs) {
            not_olbs = false;
            continue;
        }
        for (int j = 8; j < lake_max_width+1; j++){
            if (y[i] > y[i + j]) {
                not_olas = false;
                first_point_cords.push_back({i, i + j });
                i += j;
                break;
            }
        }
        if (not_olas) {
            i += lake_max_width;
            continue;
        }
    }

    //prepare lakes' places for filling with water 
    for (int i = 0; i < first_point_cords.size(); i++) {
        int constY = first_point_cords[i].first;

        //surface line
        for (int j = first_point_cords[i].first + 1; j < first_point_cords[i].second - 1; j++) {
            map[y[constY]][x[j]] = ' ';
        }

        //bottom line
        int constL = 1;
        int constR = -1;
        short limBL = 0, limBR = 1;
        short lakeWidth = first_point_cords[i].second - first_point_cords[i].first;
        if (lakeWidth > 15) {
            limBL = 1;
            limBR = 2;
        }
        for (int k = 1; k < lakeWidth / 3; k++) {
            int left = limBL + rand() % (limBR - limBL + 1);
            int right = limBL + rand() % (limBR - limBL + 1);
            constL += left;
            constR -= right;
            for (int j = first_point_cords[i].first + constL; j < first_point_cords[i].second + constR; j++) {
                map[y[constY] + k][x[j]] = ' ';
            }
        }

        //fill till bottom line with empty cells
        //for (int k = 0; k < lakeWidth; k++) {
        //    for (int j = first_point_cords[i].first + 1; j < first_point_cords[i].second - 1; j++) {
        //        std::cout << y[constY]+k << "    " << x[j] << std::endl;
        //        if(y[constY] + k <n && x[j]<m)
        //            if (map[y[constY] + k][x[j]] == ' ')
        //            map[y[constY] + k][x[j]] = ' ';
        //    }
        //}
    }
    return first_point_cords;
}
    
    void TileFactory::generate_platforms(vector<int>& x, vector<int>& y, vector<vector<char>>& map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distributionCount(10, 17);
    int number_of_platforms = distributionCount(gen);

    for (int i = 0; i < number_of_platforms; i++) {

        std::uniform_int_distribution<int> distributionWidth(2, 7);
        int width = distributionWidth(gen);
        int height = (int)(width/2) + rand() % (width - (int)(width / 2) + 1);

        std::uniform_int_distribution<int> distributionX(2, m-2-width);
        int start_index_pos_x = distributionX(gen);

        if ((y[start_index_pos_x] - 3 - height) < 3) continue;
        std::uniform_int_distribution<int> distributionY(3, y[start_index_pos_x]-3-height);
        int start_cord_pos_y = distributionY(gen);
        generate_platform(x[start_index_pos_x], start_cord_pos_y, width, height, map);
        platform_filter_y(x[start_index_pos_x], start_cord_pos_y, y, width, height, map);
    }
}
    
    void TileFactory::generate_platform(int pos_x, int pos_y, int width, int height, vector<vector<char>>& map) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            map[pos_y + j][pos_x + i] = 'B';
        }
    }
}
    
    void TileFactory::platform_filter_y(int pos_x, int pos_y, vector<int>& y, int width, int height, vector<vector<char>>& map){
    for (int i = 0; i < width; i++) {
        for (int j = height-1; j >=height-2; ) {
            if (map[pos_y + j + 2][pos_x + i] != ' ') {
                map[pos_y + j][pos_x + i] = ' ';
                j--;
            }
            else break;
        }
    }
}
    
    void TileFactory::one_tunnel_generation(int pos_x, int pos_y, int height, vector<vector<char>>& map) {
    if (height == 0) return;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pos_y + j <= 1 || pos_y + j > n-2 || pos_x + i <= 1 || pos_x + i > m-2 || map[pos_y + j][pos_x + i] == ' ') {
                return;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            map[pos_y + j][pos_x + i] = ' ';
        }
    }
    int posibility = rand() % (100);
    if (posibility < 20) {//up
        one_tunnel_generation(pos_x, pos_y - 2, height-1, map);
    }
    else if (posibility < 80) {//forward
        one_tunnel_generation(pos_x + 2, pos_y, height - 1, map);
    }
    else if (posibility < 102) {//down
        one_tunnel_generation(pos_x, pos_y + 2, height - 1, map);
    }
}
    
    //straight up
    void TileFactory::upward(int pos_x, int pos_y, vector<vector<char>>& map) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pos_y + j <= 1 || pos_y + j > 38 || pos_x + i <= 1 || pos_x + i > m-2) {
                //std::cout << "j - " << pos_y + j << ",i - " << pos_x + i << std::endl;
                return;
            }
        }
    }
    int count = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (map[pos_y+j][pos_x+i]==' ') {
                count++;
            }
        }
    }
    if (count == 4) return;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            map[pos_y + j][pos_x + i] = ' ';
        }
    }
    int posibility = rand() % (100);
    if (posibility < 50) {//up
        upward(pos_x, pos_y - 2, map);
    }
    else if (posibility < 102) {//forward
        upward(pos_x + 2, pos_y, map);
    }
}
    
    void TileFactory::left_zigzag(int pos_x, int pos_y, vector<vector<char>>& map) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (pos_x + i <= 1) {
                return right_zigzag(pos_x + 2, pos_y - 2, map);
            }
        }
    }
    if (map[pos_y+3][pos_x] == ' ' && map[pos_y+3][pos_x + 1]==' ') return;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            map[pos_y + j][pos_x + i] = ' ';
        }
    }
    return left_zigzag(pos_x - 2, pos_y - 2, map);
}
    
    void TileFactory::right_zigzag(int pos_x, int pos_y, vector<vector<char>>& map) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (pos_x + i > m-2) {
                return left_zigzag(pos_x - 2, pos_y - 2, map);
            }
        }
    }
    if (map[pos_y + 3][pos_x] == ' ' && map[pos_y + 3][pos_x + 1] == ' ') return;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            map[pos_y + j][pos_x + i] = ' ';
        }
    }
    return right_zigzag(pos_x + 2, pos_y - 2, map);
}
    
    void TileFactory::tunnels_generation(vector<int>& y, vector<vector<char>>& map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distributionCount(3, 10);
    std::uniform_int_distribution<int> distributionX(2, m-4);
    int number_of_tunnels = distributionCount(gen);

    for (int i = 0; i < number_of_tunnels; i++){
        int position_x = distributionX(gen);
        std::uniform_int_distribution<int> distributionY(y[position_x], n-3);
        int position_y = distributionY(gen);
        one_tunnel_generation(position_x, position_y, n, map);
        int posibility = rand() % (100);
        if (posibility < 50)
            left_zigzag(position_x - 2, position_y - 2, map);
        else right_zigzag(position_x + 2, position_y - 2, map);
        //find_surface(position_x, position_y-2, map);
    }
}
    
    void TileFactory::texture_arrangement(vector<vector<char>>& map){
        for (int i = 1; i < n; ++i){
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'B' && map[i - 1][j] == ' ') {
                    map[i][j] = 'A';
                }
                if (map[i][j] == 'c' && map[i - 1][j] == ' ' || j - 1 >= 0 && map[i][j - 1] == 'C' && map[i][j] == 'c') {
                    map[i][j] = 'C';
                }
            }
        }
    }
    
    TileFactory::TileFactory(int n_, int m_) : n(n_), m(m_){
        srand(static_cast<unsigned int>(time(nullptr)));
        auto start = std::chrono::high_resolution_clock::now();
        vector<vector<char>> map(n, vector<char>(m));
        //char map[n][m];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                map[i][j] = ' ';
            }
        }
    
        generation_map(map);
    
    
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
    
        Tile tile_A(initRect_tile('A'), 'A', 'A');
        Tile tile_B(initRect_tile('B'), 'B', 'B');
        Tile tile_C(initRect_tile('C'), 'C', 'C');
        Tile tile_c(initRect_tile('c'), 'c', 'c');
        Tile tile_D(initRect_tile('D'), 'D', 'D');
        Tile tile_L(initRect_tile('L'), 'L', 'L');
        Tile tile_P(initRect_tile('P'), 'P', 'P');
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == 'A') { tile_map_inFactory[i][j] = tile_A; }
                if (map[i][j] == 'B') { tile_map_inFactory[i][j] = tile_B; }
                if (map[i][j] == 'C') { tile_map_inFactory[i][j] = tile_C; }
                if (map[i][j] == 'c') { tile_map_inFactory[i][j] = tile_c; }
                if (map[i][j] == 'D') { tile_map_inFactory[i][j] = tile_D; }
                if (map[i][j] == 'L') { tile_map_inFactory[i][j] = tile_L; }
                if (map[i][j] == 'P') { tile_map_inFactory[i][j] = tile_P; }
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;
    }