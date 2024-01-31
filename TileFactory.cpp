﻿
#include "stdafx.h"
#include "TileFactory.h"

TileFactory::TileFactory(float temp_W, float temp_H, short int level) :
    generation_template(template_W, std::vector<char>(template_H)),
    template_W(temp_W),
    template_H(temp_H),
    level(level)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (level == 1) {
        generation_map_Boev(generation_template);
    }
    else if (level == 2) {
        for (int i = 0; i < template_W; ++i) {
            for (int j = 0; j < template_H; ++j) {
                generation_template[i][j] = ' ';
            }
        }
        generation_map_Voicu(generation_template);
    }
    else {
        for (int i = 0; i < template_W; i++) {
            for (int j = 0; j < template_H; j++) {
                generation_template[i][j] = 'N';
            }
        }
        map_generation(generation_template);

        filter_map(generation_template);

        filter_map(generation_template);

        filter_map1(generation_template);

        artist_method(generation_template);

        fill_lakes_with_ground(generation_template);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;
}

char TileFactory::give_generation_letter(int i, int j)
{
    return generation_template[i][j];
}


//Max
void TileFactory::generation_map_Boev(std::vector<std::vector<char>>& map)
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_real_distribution<double> dist_wather_width(5, 25);
    std::uniform_real_distribution<double> dist_wather_deep(2, 6);

    double random_number;
    int random_width;
    int random_deep;
    double probability = 0.30;
    int helper = 0;
    int helper_2 = 0;
    int i = template_W / 2;


    for (int j = 0; j < template_H; j++)
    {
        random_number = dist(gen);

        if (random_number <= probability / 2 && i < (template_W - template_W / 3) && j >= 3)
        {
            i++;
            map[i][j] = 'A';

            if (map[i - 1][j - 2] == ' ')
            {
                if (map[i][j - 2] != ' ')
                {
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'A';
                }
                else
                {
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'L';
                }
            }
            else map[i - 1][j - 1] = 'P';

            helper = i + 1;
            helper_2 = helper;
            while (helper < template_W)
            {
                if (helper - helper_2 >= 5)
                {
                    map[helper][j] = 'G';
                    helper++;
                    continue;
                }
                map[helper][j] = 'B';
                helper++;
            }
            helper = i - 1;
            while (helper >= 0)
            {
                map[helper][j] = ' ';
                helper--;
            }
            continue;
        }

        if (random_number > probability / 2 && random_number <= probability && i > template_W / 3 && j >= 3)
        {
            i--;
            map[i][j] = 'L';
            helper = i + 1;
            helper_2 = helper;
            while (helper < template_W)
            {
                if (helper - helper_2 >= 5)
                {
                    map[helper][j] = 'G';
                    helper++;
                    continue;
                }
                map[helper][j] = 'B';
                helper++;
            }
            helper = i - 1;
            while (helper >= 0)
            {
                map[helper][j] = ' ';
                helper--;
            }
            continue;
        }

        if (random_number > probability && random_number <= 0.4 && i <= template_W - (template_W / 3) && i > template_W / 3 && j >= 3)
        {

            if (random_number <= 0.335)
            {
                i = i - 2;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                helper = i + 2;
                helper_2 = helper;
                while (helper < template_W)
                {
                    if (helper - helper_2 >= 5)
                    {
                        map[helper][j] = 'G';
                        helper++;
                        continue;
                    }
                    map[helper][j] = 'B';
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0)
                {
                    map[helper][j] = ' ';
                    helper--;
                }
                continue;
            }

            if (random_number > 0.335 && random_number <= 0.370) {
                i = i + 2;
                map[i][j] = 'A';
                map[i - 2][j - 1] = 'P';
                map[i - 1][j - 1] = 'D';
                if (map[i][j - 2] == ' ')
                {
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'L';
                }
                else if (map[i - 1][j - 2] == ' ')
                {
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'A';
                }
                else if (map[i - 2][j - 2] == ' ')
                {
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = 'P';//
                }
                else {}
                helper = i + 1;
                helper_2 = helper;
                while (helper < template_W)
                {
                    if (helper - helper_2 >= 5)
                    {
                        map[helper][j] = 'G';
                        helper++;
                        continue;
                    }
                    map[helper][j] = 'B';
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0)
                {
                    map[helper][j] = ' ';
                    helper--;
                }
                continue;
            }

            if (random_number > 0.370 && random_number <= 0.385)
            {
                i = i - 3;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                map[i + 2][j] = 'C';
                helper = i + 3;
                helper_2 = helper;
                while (helper < template_W) {
                    if (helper - helper_2 >= 5)
                    {
                        map[helper][j] = 'G';
                        helper++;
                        continue;
                    }
                    map[helper][j] = 'B';
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0)
                {
                    map[helper][j] = ' ';
                    helper--;
                }
                continue;
            }

            if (random_number > 0.385 && random_number <= 0.4)
            {
                i = i + 3;
                map[i][j] = 'A';
                map[i - 3][j - 1] = 'P';
                map[i - 2][j - 1] = 'D';
                map[i - 1][j - 1] = 'D';
                if (map[i][j - 2] == ' ')
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'A';
                }
                else if (map[i - 1][j - 2] == ' ')
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = ' ';
                    map[i][j - 1] = 'A';//
                }
                else if (map[i - 2][j - 2] == ' ')
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = ' ';
                    map[i - 1][j - 1] = 'P';//
                }
                else if (map[i - 3][j - 2] == ' ')
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = 'P';
                }
                else {}
                helper = i + 1;
                helper_2 = helper;
                while (helper < template_W)
                {
                    if (helper - helper_2 >= 5)
                    {
                        map[helper][j] = 'G';
                        helper++;
                        continue;
                    }
                    map[helper][j] = 'B';
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0)
                {
                    map[helper][j] = ' ';
                    helper--;
                }
                continue;
            }
        }

        if (random_number > 0.4 && random_number <= 0.420 && j <= (template_H - 50) && j >= 3 && i <= template_W - 8)
        {
            random_width = dist_wather_width(gen);
            random_deep = dist_wather_deep(gen);
            int tmp = j;
            int ch = 0;
            while (j - tmp <= random_width)
            {
                map[i][j] = 'W';
                ch = 0;
                while (ch <= random_deep)
                {
                    ch++;
                    map[i + ch][j] = 'w';
                }
                helper = ch + i;
                helper_2 = helper;
                while (helper < template_W)
                {
                    if (helper - helper_2 >= 2)
                    {
                        map[helper][j] = 'G';
                        helper++;
                        continue;
                    }
                    map[helper][j] = 'B';
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0)
                {
                    map[helper][j] = ' ';
                    helper--;
                }
                j++;
            }
            map[i][j] = 'A';
            helper = i + 1;
            helper_2 = helper;
            while (helper < template_W)
            {
                if (helper - helper_2 >= 5)
                {
                    map[helper][j] = 'G';
                    helper++;
                    continue;
                }
                map[helper][j] = 'B';
                helper++;
            }
            helper = i - 1;
            while (helper >= 0)
            {
                map[helper][j] = ' ';
                helper--;

            }
            continue;
        }

        if (i < template_H && i > 1)
        {
            map[i][j] = 'A';
            helper = i + 1;
            helper_2 = helper;
            while (helper < template_W)
            {
                if (helper - helper_2 >= 5)
                {
                    map[helper][j] = 'G';
                    helper++;
                    continue;
                }
                map[helper][j] = 'B';
                helper++;
            }
            helper = i - 1;
            while (helper >= 0)
            {
                map[helper][j] = ' ';
                helper--;

            }
            continue;
        }
    }



    probability = 0.75;
    std::uniform_real_distribution<float> dist_L(template_H - (template_H - 20), (template_H - 20));
    std::uniform_real_distribution<float> dist_count(template_H / 12, template_H / 10);
    std::uniform_real_distribution<float> dist_H(template_W - (template_W / 4), template_W - (template_W / 5));
    std::uniform_real_distribution<float> dist_count_dig(20, 150);
    int h = template_W - template_W / 5;
    int tmp_h;
    int l;
    int count = dist_count(gen);
    int count_dig;

    for (int curr = 0; curr <= count; curr++)
    {
        tmp_h = dist_H(gen);
        l = dist_L(gen);
        count_dig = dist_count_dig(gen);

        while (count_dig > 0)
        {
            for (int i = tmp_h - 1; i <= tmp_h + 1; i++)
            {
                for (int j = l - 1; j <= l + 1; j++)
                {
                    if (map[i][j] == 'G')
                        map[i][j] = ' ';
                }
            }
            random_number = dist(gen);
            if (random_number <= probability / 2 && tmp_h <= template_W - 6) tmp_h = tmp_h + 1;
            else if (random_number <= probability && random_number > probability / 2 && tmp_h >= template_W / 2) tmp_h = tmp_h - 1;
            else {}

            if (l <= template_H - 10) l = l + 2;
            else { break; }
            count_dig--;
        }
    }

    probability = 0.90;
    count = template_H / 100;
    int flag;
    for (int curr = 0; curr <= count; curr++)
    {
        tmp_h = template_W / 3;
        l = dist_L(gen);
        flag = 1;

        while (tmp_h < h)
        {
            for (int i = tmp_h - 2; i <= tmp_h + 2; i++)
            {
                for (int j = l - 2; j <= l + 2; j++)
                {
                    if (map[i][j] == 'W' || map[i][j] == 'w') flag *= 0;
                }
            }
            if (!flag) break;

            for (int i = tmp_h - 1; i <= tmp_h + 1; i++)
            {
                for (int j = l - 1; j <= l + 1; j++)
                {
                    map[i][j] = ' ';
                }
            }
            random_number = dist(gen);
            if (random_number <= probability / 2 && l < template_H - 10) l = l + 1;
            else if (random_number <= probability && random_number > probability / 2 && l > 10) l = l - 1;
            else {}

            tmp_h++;
        }
    }



    std::uniform_real_distribution<float> dist_quantity(template_H - template_H / 1.5, template_H - template_H / 3);
    std::uniform_real_distribution<double> dist_island_width(3, 20);
    std::uniform_real_distribution<double> dist_island_deep(1, 4);
    std::uniform_real_distribution<float> dist_h(3, template_W / 2.5);
    std::uniform_real_distribution<float> dist_l(5, template_H - 40);
    probability = 30;
    int quantity = dist_quantity(gen);
    for (int ch = 0; ch <= quantity; ch++)
    {
        random_number = dist(gen);
        if (random_number <= probability)
        {
            h = dist_h(gen);
            l = dist_l(gen);
            random_width = dist_island_width(gen);
            random_deep = dist_island_deep(gen);
            int tmp = l;
            int ch = 0;
            int flag = 0;
            if (map[h - 1][l] == ' ' && map[h][l - 1] == ' ' && map[h + random_deep + 1][l] == ' ' && map[h + random_deep][l - 1] == ' ' && map[h][l + random_width + 1] == ' ' && map[h - 1][l + random_width] == ' ' && map[h + random_deep][l + random_width + 1] == ' ' && map[h + random_deep + 1][l + random_width] == ' ')
            {
                if (map[h - 3][l] == ' ' && map[h][l - 3] == ' ' && map[h + random_deep + 3][l] == ' ' && map[h + random_deep][l - 3] == ' ' && map[h][l + random_width + 3] == ' ' && map[h - 3][l + random_width] == ' ' && map[h + random_deep][l + random_width + 3] == ' ' && map[h + random_deep + 3][l + random_width] == ' ')
                {
                    while (l - tmp <= random_width) {

                        if (flag == 0) { map[h][l] = 'L'; }
                        else if (flag == random_width) { map[h][l] = 'P'; }
                        else { map[h][l] = 'A'; }

                        ch = 0;
                        while (ch <= random_deep)
                        {
                            ch++;
                            if (flag == 0) { map[h + ch][l] = 'C'; }
                            else if (flag == random_width) { map[h + ch][l] = 'D'; }
                            else { map[h + ch][l] = 'B'; }

                        }
                        flag++;
                        l++;
                    }
                }
            }
            else continue;
        }
        else continue;
    }
}

//Dimon
class coord {
public:
    int x[20];
    int y[20];
    int size;

    coord(float xb[], float yb[], int s) {
        size = s;
        for (int i = 0; i < size; ++i) {
            x[i] = xb[i];
            y[i] = yb[i];
        }
    }

    coord(std::vector<float> xb, std::vector<float> yb, int s) {
        size = s;
        for (int i = 0; i < size; ++i) {
            x[i] = xb[i];
            y[i] = yb[i];
        }
    }
};

class lakeC {
public:
    short dir;
    int x;
    int y;
    lakeC(short dir_, int x_, int y_) {
        dir = dir_;
        x = x_;
        y = y_;
    }
};

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
        y[i] = sin((x[i] * waveSize) / 0.7 + shift) - cos(x[i] + 3) + incline * x[i];
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
    for (int i = 0, j = begI; i < n; i++, j++) {
        if (ground[j] - target[i] <= 2) {
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

    for (; i < template_H; ) {
        coord* cordinates = generate_landscape();
        int amplitude = cordinates->y[cordinates->size - 1] - cordinates->y[0];
        int offset_pos = y[i - 1] - cordinates->y[0];
        int offset_neg = y[i - 1] - cordinates->y[cordinates->size - 1];

        if (y[i - 1] + amplitude < 33) {
            for (int j = 0; j < cordinates->size && i < template_H; ++j, i++) {
                x[i] = i;
                y[i] = cordinates->y[j] + offset_pos;
            }
        }
        else {
            for (int j = cordinates->size - 1; j >= 0 && i < template_H; --j, i++) {
                x[i] = i;
                y[i] = cordinates->y[j] + offset_neg;
            }
        }
        free(cordinates);
    }

    //fill
    for (int j = 0; j < template_H; ++j) {
        for (int i = y[j]; i < template_W; i++) {
            map[i][x[j]] = 'B';
        }
    }
}

void TileFactory::generation_map_Voicu(vector<vector<char>>& map) {
    vector<int> x(template_H);
    vector<int> y(template_H);
    for (int i = 0; i < template_H; ++i) {
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
        fill_lake(y[coords_for_water[i].first], x[coords_for_water[i].first] + 1, y[coords_for_water[i].first], map);


    }
}

void TileFactory::fill_lake(int& water_level, int pos_x, int pos_y, vector<vector<char>>& map) {
    stack<lakeC> lakeTiles;
    lakeTiles.push(lakeC(1, pos_x, pos_y));

    while (!lakeTiles.empty()) {
        if (lakeTiles.top().dir == 1) {
            if (lakeTiles.top().x < 0 || lakeTiles.top().x >= template_H
                || lakeTiles.top().y < 0 || lakeTiles.top().y >= template_W
                || map[lakeTiles.top().y][lakeTiles.top().x] != ' ' || lakeTiles.top().y < water_level
                || lakeTiles.top().dir == 4) {
                lakeTiles.pop();
                continue;
            }
            map[lakeTiles.top().y][lakeTiles.top().x] = 'w';
        }
        if (lakeTiles.top().dir > 4) {
            lakeTiles.pop();
            continue;
        }
        switch (lakeTiles.top().dir) {
            //moving down
        case 1:
            lakeTiles.top().dir++;
            lakeTiles.push(lakeC(1, lakeTiles.top().x, lakeTiles.top().y + 1));
            break;
            //moving left
        case 2:
            lakeTiles.top().dir++;
            lakeTiles.push(lakeC(1, lakeTiles.top().x - 1, lakeTiles.top().y));
            break;
            //moving up
        case 3:
            lakeTiles.top().dir++;
            lakeTiles.push(lakeC(1, lakeTiles.top().x, lakeTiles.top().y - 1));
            break;
            //moving right
        case 4:
            lakeTiles.top().dir++;
            lakeTiles.push(lakeC(1, lakeTiles.top().x + 1, lakeTiles.top().y));
            break;
        }
    }
}

std::vector<std::pair<int, int>>  TileFactory::lakes_generation(vector<int>& x, vector<int>& y, vector<vector<char>>& map) {
    bool not_olbs;//not on level before seven
    bool not_olas;//not on level after seven
    short lake_min_width = 7;
    short lake_max_width = 20;

    std::vector<std::pair<int, int>> first_point_cords;

    //searching for suitable places
    for (int i = 0; i + lake_max_width < template_H; ) {
        not_olas = true;
        not_olbs = false;

        for (int j = 1; j < lake_min_width + 1; j++) {
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
        for (int j = 8; j < lake_max_width + 1; j++) {
            if (y[i] > y[i + j]) {
                not_olas = false;
                first_point_cords.push_back({ i, i + j });
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
        int height = (int)(width / 2) + rand() % (width - (int)(width / 2) + 1);

        std::uniform_int_distribution<int> distributionX(2, template_H - 2 - width);
        int start_index_pos_x = distributionX(gen);

        if ((y[start_index_pos_x] - 3 - height) < 3) continue;
        std::uniform_int_distribution<int> distributionY(3, y[start_index_pos_x] - 3 - height);
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

void TileFactory::platform_filter_y(int pos_x, int pos_y, vector<int>& y, int width, int height, vector<vector<char>>& map) {
    for (int i = 0; i < width; i++) {
        for (int j = height - 1; j >= height - 2; ) {
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
            if (pos_y + j <= 1 || pos_y + j > template_W - 2 || pos_x + i <= 1 || pos_x + i > template_H - 2 || map[pos_y + j][pos_x + i] == ' ') {
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
        one_tunnel_generation(pos_x, pos_y - 2, height - 1, map);
    }
    else if (posibility < 80) {//forward
        one_tunnel_generation(pos_x + 2, pos_y, height - 1, map);
    }
    else if (posibility < 102) {//down
        one_tunnel_generation(pos_x, pos_y + 2, height - 1, map);
    }
}

void TileFactory::upward(int pos_x, int pos_y, vector<vector<char>>& map) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (pos_y + j <= 1 || pos_y + j > 38 || pos_x + i <= 1 || pos_x + i > template_H - 2) {
                //std::cout << "j - " << pos_y + j << ",i - " << pos_x + i << std::endl;
                return;
            }
        }
    }
    int count = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (map[pos_y + j][pos_x + i] == ' ') {
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
    //for (int i = 0; i < 2; i++) {
        //for (int j = 0; j < 4; j++) {
    if (pos_x + 1 <= 2) {//i
        return right_zigzag(pos_x + 2, pos_y - 2, map);
    }
    //}
//}
    if (map[pos_y + 3][pos_x] == ' ' && map[pos_y + 3][pos_x + 1] == ' ') return;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            map[pos_y + j][pos_x + i] = ' ';
        }
    }
    return left_zigzag(pos_x - 2, pos_y - 2, map);
}

void TileFactory::right_zigzag(int pos_x, int pos_y, vector<vector<char>>& map) {
    //for (int i = 0; i < 2; i++) {
        //for (int j = 0; j < 4; j++) {
    if (pos_x + 2 > template_H - 3) {//i
        return left_zigzag(pos_x - 2, pos_y - 2, map);
    }
    //}
//}
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
    std::uniform_int_distribution<int> distributionCount(3, 27);
    std::uniform_int_distribution<int> distributionX(2, template_H - 4);
    int number_of_tunnels = distributionCount(gen);

    for (int i = 0; i < number_of_tunnels; i++) {
        int position_x = distributionX(gen);
        std::uniform_int_distribution<int> distributionY(y[position_x], template_W - 3);
        int position_y = distributionY(gen);
        one_tunnel_generation(position_x, position_y, template_W, map);
        int posibility = rand() % (100);
        if (posibility < 50)
            left_zigzag(position_x - 2, position_y - 2, map);
        else right_zigzag(position_x + 2, position_y - 2, map);
        //find_surface(position_x, position_y-2, map);
    }
}

void TileFactory::texture_arrangement(vector<vector<char>>& map) {
    for (int i = 1; i < template_W; ++i) {
        for (int j = 0; j < template_H; ++j) {
            if (map[i][j] == 'B' && map[i - 1][j] == ' ') {
                map[i][j] = 'A';
            }
            if (map[i][j] == 'w' && map[i - 1][j] == ' ' || j - 1 >= 0 && map[i][j - 1] == 'W' && map[i][j] == 'w') {
                map[i][j] = 'W';
            }
        }
    }
}
//Dimon


//Richard
void TileFactory::map_generation(vector<vector<char>>& template_2)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int i = rand() % (int)(template_W * 0.25) + (int)(template_W * 0.38), j = 0;
    start_of_map_generation_(template_2, i, j, gen);
}

void TileFactory::start_of_map_generation_(vector<vector<char>>& map, int& i, int& j, std::mt19937 gen)
{
    std::uniform_int_distribution<int> cofShift(template_W * 0.08, template_W * 0.15);

    int min = 1;
    int max = 5;
    std::uniform_int_distribution<int> distribution(min, max);
    int choice = distribution(gen);
    bool wormhole_b = true;
    int coutn = 5;
    int SHIFT;
    while (j < template_H)
    {
        SHIFT = cofShift(gen);
        int choice = distribution(gen);
        if (choice == 1 && i > 87 * template_W / 100)
            flatland(map, i, j, SHIFT, gen);
        else if (choice == 2)
            mountainous_terrain(map, i, j, SHIFT, gen);
        else if (choice == 3)
            water_bodies(map, i, j, SHIFT, gen);
        else if (choice == 4)
            tunnel(map, i, j, SHIFT, gen);

        else if (choice == 5 && wormhole_b)
        {
            wormhole(map, i, j, SHIFT, gen);
            coutn--;
            if (coutn <= 0) wormhole_b = false;
        }
        else flatland(map, i, j, SHIFT, gen);
    }
    cavern(map, i, j, SHIFT, gen);
    cavern(map, i, j, SHIFT, gen);
    cavern(map, i, j, SHIFT, gen);



}

void TileFactory::flatland(vector<vector<char>>& map, int& i, int& j, int shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    int count = 0;
    int bool_tap = 0;
    for (int top = 0; top < shift && top < template_W; top++)
    {
        int right = j;
        for (; right < j + shift && right > 0 && right < template_H; right++)
        {
            for (int down = i; down > 0 && down < template_W; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
            {
                if (map[down][right] == 'N')map[down][right] = 'B';
            }
            for (int up = i - 1; up >= 0 && up < template_W; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåðõ
            {
                if (map[up][right] == 'N')map[up][right] = ' ';
            }
        }

        j = right;
        bool_tap = distribution(gen);
        if (bool_tap != 0)count = 1;
        if (i >= 15 && i <= 25)i += bool_tap;
        else if (i >= 25)
        {
            i += -1;
            bool_tap = -1;
        }
        else
        {
            i += 1;
            bool_tap = 1;
        }
    }
}

void TileFactory::mountainous_terrain(vector<vector<char>>& map, int& i, int& j, int& shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    int bool_tap = distribution(gen);


    for (int STEP = 0; STEP < shift; STEP++)
    {
        int right = j;
        for (; right < j + shift && right >= 0 && right < template_H; right++)
        {
            for (int down = i; down < template_W && down >= 0; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
            {
                if (map[down][right] == 'N')map[down][right] = 'B';
            }
            for (int up = i - 1; up < template_W && up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåðõ
            {
                if (map[up][right] == 'N')map[up][right] = ' ';
            }
            i += bool_tap;
        }
        j = right;
        for (; right < j + shift / 2 && right >= 0 && right < template_H; right++)
        {
            for (int down = i; down >= 0 && down < template_W; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
            {
                if (map[down][right] == 'N')map[down][right] = 'B';
            }
            for (int up = i - 1; up < template_W && up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåðõ
            {
                if (map[up][right] == 'N')map[up][right] = ' ';
            }
        }
        j = right;
        if (i >= template_W * 0.25 && i <= template_W * 0.65) bool_tap = distribution(gen);
        else if (i >= template_W * 0.65) bool_tap = -1;
        else bool_tap = 1;
    }
}

void TileFactory::water_bodies(vector<vector<char>>& map, int& i, int& j, int shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    int bool_tap = 1;
    int stat_i = i;

    for (int STEP = 0; STEP < 2; STEP++)
    {
        int right = j;
        for (; right < j + shift && right >= 0 && right < template_H; right++)
        {
            for (int down = i; down >= 0 && down < template_W; down++)
            {
                if (map[down][right] == 'N')map[down][right] = 'B';
            }
            for (int up = i - 1; up < template_W && up >= 0; up--)

            {
                if (up == stat_i)map[up][right] = 'W';
                if (up > stat_i) map[up][right] = 'w';
                if (map[up][right] == 'N')map[up][right] = ' ';
            }
            i += bool_tap;
        }
        j = right;
        for (; right < j + shift && right >= 0 && right < template_H; right++)
        {
            for (int down = i; down >= 0 && down < template_W; down++)
            {
                if (map[down][right] == 'N')map[down][right] = 'B';
            }
            for (int up = i - 1; up < template_W && up >= 0; up--)
            {
                if (up == stat_i)map[up][right] = 'W';
                if (up > stat_i) map[up][right] = 'w';
                if (map[up][right] == 'N')map[up][right] = ' ';
            }
        }
        j = right;
        bool_tap = -1;
    }
}

void TileFactory::tunnel(vector<vector<char>>& map, int& i, int& j, int shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    std::uniform_int_distribution<int> emptiness(template_W * 0.08, template_W * 0.15);
    int bool_tap = 1;
    int stat_i = i;
    i += bool_tap;
    int count_emptiness = 0;
    int count_block = 0;

    int right = j;

    for (; right < j + shift * 3 && right >= 0 && right < template_H; right++)
    {
        for (int down = i; down >= 0 && down < template_W; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
        {
            if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
        }
        count_emptiness = emptiness(gen);
        count_block = emptiness(gen);

        for (int up = i - 1; up < template_W && up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåðõ
        {
            map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
        }
        i += distribution(gen);
    }
    j = right;
}

void TileFactory::wormhole(vector<vector<char>>& map, int& i, int& j, int shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    int bool_tap = 1;
    int stat_i = i;
    int stat_j = j;

    if (i > template_W * 0.75)return;
    int right = j;
    int top = 0;
    int count = shift + 3;


    for (; right < j + 4 && right >= 0 && right < template_H; right++)
    {
        top = i;

        for (int down = i + 1; down >= 0 && down < template_W; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
        {
            if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
        }
        for (; top < i + 5 && top >= 0 && top < template_W; top++)
        {
            map[top][right] = ' ';
        }
        for (int up = i - 1; up < template_W && up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåðõ

        {

            if (map[up][right] == 'N')map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
        }
    }

    if (j > template_H / 2)
    {
        std::uniform_int_distribution<int> stp_d(3, 4);
        int stp = stp_d(gen);
        right = j;
        for (; right > j - shift * 10 && right < template_H && right >= 0; right--)
        {
            top = i + 1;
            for (; top < i + 7 && top >= 0 && top < template_W - 1; top++)
            {
                map[top][right] = ' ';
            }
            i += distribution(gen);
            if (distribution(gen))
            {
                i += 1;
            }
        }
    }
    else
    {
        std::uniform_int_distribution<int> stp_d(3, 4);
        int stp = stp_d(gen);
        right = j;
        for (; right < j + shift * 4 && right >= 0 && right < template_H; right++)
        {
            top = i + 1;
            for (; top < i + 7 && top >= 0 && top < template_W - 1; top++)
            {
                map[top][right] = ' ';
            }
            i += distribution(gen);
            if (distribution(gen))
            {
                i += 1;
            }
        }
    }
    j = stat_j + 4;
    i = stat_i;
}

void TileFactory::cavern(vector<vector<char>>& map, int& i, int& j, int shift, std::mt19937 gen)
{
    std::uniform_int_distribution<int> distribution(-1, 1);
    std::uniform_int_distribution<int> cavern_rand(template_W / 2, 87 * template_W / 100);
    std::uniform_int_distribution<int> cavern_rand_step(template_W * 0.1, template_W * 0.15);
    int right = 0;
    int top = cavern_rand(gen);
    int step = cavern_rand_step(gen);
    i = top;
    for (; right < template_H - 1 && right >= 0; right++)
    {
        step = cavern_rand_step(gen);
        for (; top < i + step && top < template_W - 1 && top >= 0; top++)
        {
            map[top][right] = ' ';
        }
        top = i;
        if (top > 87 * template_W / 100) top += -1;
        else top += distribution(gen);
        i = top;
    }
}

//stripping blocks 
void TileFactory::filter_map(vector<vector<char>>& map)
{
    int emptyNeighbors;
    for (int i = 0; i < template_W; i++)
    {
        for (int j = 0; j < template_H; j++)
        {


            if (map[i][j] != ' ')
            {
                emptyNeighbors = count_empty_neighbors(map, i, j);

                if (emptyNeighbors > 4)
                {
                    map[i][j] = ' ';

                }
            }
        }

    }
}

void TileFactory::filter_map1(vector<vector<char>>& map)
{
    for (int i = 0; i < template_W; i++)
    {
        for (int j = 0; j < template_H; j++)
        {
            if (map[i][j] == ' ')
            {
                if (has_blocks_on_both_sides(map, i, j))
                {
                    map[i][j] = 'B'; // Replace the empty block with earth if there are blocks on both sides
                }
            }
        }
    }
}

bool TileFactory::has_blocks_on_both_sides(vector<vector<char>>& map, int i, int j)
{
    if ((i > 0 && map[i - 1][j] != ' ') && (i < template_W - 1 && map[i + 1][j] != ' '))
    {
        return true; //emptiness in one block vertically
    }

    if ((j - 1 > 0 && map[i][j - 1] != ' ') && (j < template_H - 1 && map[i][j + 1] != ' '))
    {
        return true; //voids in one block horizontally
    }

    return false;
}

int TileFactory::count_empty_neighbors(vector<vector<char>>& map, int i, int j)
{
    int emptyNeighbors = 0;
    if (i > 0 && map[i - 1][j] == ' ') emptyNeighbors++;
    if (i > 0 && j > 0 && map[i - 1][j - 1] == ' ') emptyNeighbors++;
    if (i > 0 && j + 1 < template_H && map[i - 1][j + 1] == ' ')emptyNeighbors++;
    if (i + 1 < template_W && j > 0 && map[i + 1][j - 1] == ' ')emptyNeighbors++;
    if (i + 1 < template_W && j + 1 < template_H && map[i + 1][j + 1] == ' ')emptyNeighbors++;
    if (i + 1 < template_W && map[i + 1][j] == ' ') emptyNeighbors++;
    if (j > 0 && map[i][j - 1] == ' ') emptyNeighbors++;
    if (j + 1 < template_H && map[i][j + 1] == ' ') emptyNeighbors++;

    return emptyNeighbors;
}

void TileFactory::artist_method(vector<vector<char>>& map)
{
    for (int i = 0; i < template_W - 1; i++)
    {
        for (int j = 0; j < template_H - 1; j++)
        {
            if (map[i][j] != ' ' && map[i][j] != 'w' && map[i][j] != 'W')
            {
                bool hasTop = (i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == 'W'));
                bool hasBottom = (i < template_W - 1 && map[i + 1][j] == ' ');
                bool hasLeft = (j > 0 && map[i][j - 1] == ' ');
                bool hasRight = (j < template_H - 1 && map[i][j + 1] == ' ');

                if (!hasTop && !hasLeft && !hasRight)
                {
                    map[i][j] = 'B';
                }
                else if (hasTop && hasBottom && hasLeft && hasRight)
                {
                    map[i][j] = 'A'; // Ñîñåäè ñïðàâà, ñëåâà è ñâåðõó 
                }
                else if (hasTop && hasRight)
                {
                    map[i][j] = 'P'; // Ñîñåäè ñâåðõó è ñïðàâà 
                }
                else if (hasTop && hasLeft)
                {
                    map[i][j] = 'L'; // Ñîñåäè ñâåðõó è ñëåâà 
                }
                else if (hasTop)
                {
                    map[i][j] = 'A'; // Ñîñåä ñâåðõó 
                }
                else if (hasBottom)
                {
                    map[i][j] = 'B'; // Ñîñåä ñíèçó 
                }
                else if (hasLeft)
                {
                    map[i][j] = 'C'; // Ñîñåä ñëåâà 
                }
                else if (hasRight)
                {
                    map[i][j] = 'D'; // Ñîñåä ñïðàâà
                }
            }
        }
    }
}

//fix bug with soaring water
void TileFactory::fill_lakes_with_ground(vector<vector<char>>& map)
{
    for (int i = 0; i < template_W - 1; i++)
    {
        for (int j = 0; j < template_H; j++)
        {
            if (map[i][j] == 'W' || map[i][j] == 'w')
            {
                if (map[i + 1][j] == ' ')
                {
                    map[i + 1][j] = 'B';
                }
            }
        }
    }
}