
#include "stdafx.h"
#include "TileFactory.h"

TileFactory::TileFactory() {
    //����������� ������� �����, �� ������� ��������� ����� �������.
    
    //  std::string template_1[40] = {
//"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            AA   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            AAA",
//"A   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           AA   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           AAA",
//"A   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           AA   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           AAA",
//"A   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           AA   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           AAA",
//"A   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             AA   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             AAA",
//"A   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            AA   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            AAA",
//"A   FFF     FFF      FFFFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    AA   FFF     FFF      FFFFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    AAA",
//"A                                                                                                 AA                                                                                                 AAA",
//"A                   FFF                                                                           AA                   FFF                                                                           AAA",
//"A                FFF                                                                              AA                FFF                                                                              AAA",
//"AJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAA",
//"AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//"AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIAAA",
//; 
    //std::string template_2[40] = {};
    //std::string template_3[40] = {};
    //std::string template_4[40] = {};
    //std::string template_5[40] = {};

    //�������� ������������� ������� ����� � �� ����� � ������� ��� �����������.
    std::string generation_template[40][201];
    generation_map(generation_template);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            std::cout << generation_template[i][j];
        }
        std::cout << std::endl;
    }

    //��������� ������������ �����
    build_generation_map(generation_template);
 
}

//������� ������������ ������ � ������������ ��� ��������� �������� ������.
sf::IntRect TileFactory::initRect_tile(char tile_C) {
    if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
    if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60);  }
    if (tile_C == 'C') { return sf::IntRect(130, 2, 60, 60);}
    if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60);}
    if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60);}
    if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60);}
}

//������� ��������� �����!!!
void TileFactory::generation_map(std::string map[40][201]) {
    //��������� �����������.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double random_number;
    double probability = 0.30;
    int helper = 0;
    int i = 20;
    //���� ������� �� �������� ������.
    for (int j = 0; j < 200; j++) {
        random_number = dist(gen);
        //����������� ������ ����� �� ������� ����, ��� ���� ����������� ������ ��� ������� �� ����� �������� �� 1 ������� ����� �� ���������.
        if (random_number <= probability / 2 && i < 37) {
            i++;
            map[i][j] = "A";
            
            if (map[i - 1][j - 2] == " ") {
                if (map[i][j - 2] != " ") {
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "A";
                }
                else {
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "L";
                }
            }
            else map[i - 1][j - 1] = "P";
            
            helper = i+1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i-1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;
            }
            continue;
        }
        //����������� ����������� ����� �� ������� ����.
        if (random_number > probability / 2 && random_number <= probability && i > 5) {
            i--;
            map[i][j] = "L";
            helper = i+1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i-1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;
            }
            continue;
        }
        // ������� ���������� �� ������ ������� �������� ��� ������ ���� �� ��������� �������� 2 ��� 3 ����� ����� � ���� ��������������. ���� ��� ������ ��� � ���������� �������.
        if (random_number > probability && random_number <= 0.4 && i <= 34 && i >= 8) {


            //������� �� 2 ����� �����
            if (random_number <= 0.335) { 
                i = i - 2;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                helper = i + 2;
                while (helper <= 39) {
                    map[helper][j] = "B";
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0) {
                    map[helper][j] = " ";
                    helper--;
                }
                continue;
            }
            //������� �� 2 ����� ����. ��� ���� ���������, ��� ���� �� ���� ������ ���� �� ����� ��� ���� �� ��� �������� �� ����� � ��� �� ������. 
            if(random_number > 0.335 && random_number <= 0.370) {
                i = i + 2;
                map[i][j] = 'A';
                map[i - 2][j - 1] = 'P';
                map[i - 1][j - 1] = 'D';
                if (map[i][j - 2] == " ") {
                    map[i - 2][j - 1] = " ";
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "L";
                }
                else if (map[i - 1][j - 2] == " ") {
                    map[i - 2][j - 1] = " ";
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "A";
                }
                else if (map[i - 2][j - 2] == " ") {
                    map[i - 2][j - 1] = " ";
                    map[i - 1][j - 1] = "P";
                }
                else {}

                helper = i + 1;
                while (helper <= 39) {
                    map[helper][j] = "B";
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0) {
                    map[helper][j] = " ";
                    helper--;
                }
                continue;
            }
            //������� �� 3 ����� �����
            if (random_number > 0.370 && random_number <= 0.385) {
                i = i - 3;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                map[i + 2][j] = 'C';
                helper = i + 3;
                while (helper <= 39) {
                    map[helper][j] = "B";
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0) {
                    map[helper][j] = " ";
                    helper--;
                }
                continue;
            }
            //������� �� 3 ����� ����. ��� ���� ���������, ��� ���� �� ���� ������ ���� �� ����� ��� ���� �� ��� �������� �� ����� � ��� �� ������.
            if (random_number > 0.385 && random_number <= 0.4) {
                i = i + 3;
                map[i][j] = "A";
                map[i - 3][j - 1] = "P";
                map[i - 2][j - 1] = "D";
                map[i - 1][j - 1] = "D";
                if (map[i][j - 2] == " ") {
                    map[i - 3][j - 1] = " ";
                    map[i - 2][j - 1] = " ";
                    map[i - 1][j - 1] = " ";
                    map[i][j - 1] = "A";
                }
                else if (map[i - 1][j - 2] == " ") {
                    map[i - 3][j - 1] = " ";
                    map[i - 2][j - 1] = " ";
                    map[i - 1][j - 1] = "P";
                }
                else if (map[i - 2][j - 2] == " ") {
                    map[i - 3][j - 1] = " ";
                    map[i - 2][j - 1] = "P";
                }
                else if (map[i - 3][j - 2] == " ") {
                    map[i - 3][j - 1] = " ";
                    map[i - 2][j - 1] = "P";
                }else{}

                helper = i + 1;
                while (helper <= 39) {
                    map[helper][j] = "B";
                    helper++;
                }
                helper = i - 1;
                while (helper >= 0) {
                    map[helper][j] = " ";

                    helper--;
                }
                continue;
            }
        }
        //����������� ����� �� ��� �� ������ ���� ������ �� ���� �������������� �� �����������.
        if(i < 39 && i > 4){ 
            map[i][j] = "A";
            helper = i + 1;
            while (helper <= 39) {
                map[helper][j] = "B";
                helper++;
            }
            helper = i - 1;
            while (helper >= 0) {
                map[helper][j] = " ";
                helper--;

            }
            continue;
        }
    }
     //��������� ������.
    //��������� ��������� ��������� ������ ������, ��������� ������ � ����������� ������.
     probability = 0.70;
     std::uniform_real_distribution<float> dist_j(20, 180);    
     int h = 5;
     int l = dist_j(gen);
     //���� ������� �������� ���� "������" �� ������������� ���������� ������ � �������������� ������� �� �����������.
     for (int ch = h; ch < 35; ch++) {
         random_number = dist(gen);
         //����� ������.
         if (random_number <= probability / 2 && l <= 180) {
             l++;
             for (int i = ch - 1; i <= ch + 1; i++) {
                 for (int j = l - 1; j <= l + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //����� �����.
         if (random_number > probability / 2 && random_number <= probability && l >= 20) {
             l--;
             for (int i = ch - 1; i <= ch + 1; i++) {
                 for (int j = l - 1; j <= l + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //���� ������ ��� �� ������ ������ ������.
         if(true){
             for (int i = ch - 1; i <= ch + 1; i++) {
                 for (int j = l - 1; j <= l + 1; j++) {
                     map[i][j] = " ";                
                 }
             }
             continue;
         }
     }
     //��������� ����� ����������� ��� ������ �� ��������� ��� ������ �� �����������
     probability = 0.70;
     h = 34;
     //���� ������� ������� ������ �� ����������� � �������������� ������� �� ���������.
     for (int ch = l; ch >= 20; ch--) {
         random_number = dist(gen);
         //����� �����
         if (random_number <= probability / 2 && h >= 27) {
             h = h - 1;
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //����� ����
         if (random_number > probability / 2 && random_number <= probability && h <= 36) {
             h = h + 1;
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //���� ������ ��� �� ������ ������ � ����.
         if (true) {
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
     }
     //��� �� ����� �������� ������ ����� ���� � ����� �� ����� � ������� ������ ����������.
     h = 34;
     for (int ch = l; ch <= 180; ch = ch+1) {
         random_number = dist(gen);
         //����� �����.
         if (random_number <= probability / 2 && h >= 27) {
             h = h - 1;
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //����� ����.

         if (random_number > probability / 2 && random_number <= probability && h <= 36) {
             h = h + 1;
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
         //���� ������ ��� �� ������ ������ � �����.
         if (true) {
             for (int i = h - 1; i <= h + 1; i++) {
                 for (int j = ch - 1; j <= ch + 1; j++) {
                     map[i][j] = " ";
                 }
             }
             continue;
         }
     }
}

//������� �������� ����� �� ������ ������������� �������.
void TileFactory::build_generation_map(std::string map[40][201]){
    //�������� ������
    Tile tile_A(initRect_tile('A'), 'A', 'A');
    Tile tile_B(initRect_tile('B'), 'B', 'B');
    Tile tile_C(initRect_tile('C'), 'C', 'C');
    Tile tile_D(initRect_tile('D'), 'D', 'D');
    Tile tile_L(initRect_tile('L'), 'L', 'L');
    Tile tile_P(initRect_tile('P'), 'P', 'P');
    //�������� ����� �� ������.
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 200; j++) {
            if (map[i][j] == "A") { tile_map_inFactory[i][j] = tile_A; }
            if (map[i][j] == "B") { tile_map_inFactory[i][j] = tile_B; }
            if (map[i][j] == "C") { tile_map_inFactory[i][j] = tile_C; }
            if (map[i][j] == "D") { tile_map_inFactory[i][j] = tile_D; }
            if (map[i][j] == "L") { tile_map_inFactory[i][j] = tile_L; }
            if (map[i][j] == "P") { tile_map_inFactory[i][j] = tile_P; }
        }
    }
}

