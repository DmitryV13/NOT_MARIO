
#include "stdafx.h"
#include "TileFactory.h"
#include <vector>

TileFactory::TileFactory (float temp_W, float temp_H) : generation_template(template_W, std::vector<char>(template_H)), template_W(temp_H), template_H(temp_H)
{
    generation_map(generation_template);
    for (int i = 0; i < 40; i++) 
    {
        for (int j = 0; j < 200; j++) 
        {
          std::cout << generation_template[i][j];
        }
        std::cout << std::endl;
    }
}


//Функция генерация Карты!!!
void TileFactory::generation_map(std::vector<std::vector<char>> &map) 
{
    //Генерация поверхности.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_real_distribution<double> dist_wather_width(5, 20);
    std::uniform_real_distribution<double> dist_wather_deep(2, 5);

    double random_number;
    int random_width;
    int random_deep;
    double probability = 0.30;
    int helper = 0;
    int helper_2 = 0;
    int i = 20;

    //Цикл прохода по столбцам строки.
    for (int j = 0; j < 200; j++) 
    {
        random_number = dist(gen);
        //Вставляется нужная буква на уровень ниже, при этом исключается случий при котором мы после поднятия на 1 уровень сразу же спускаемя.
        if (random_number <= probability / 2 && i < 30 && j >= 3) 
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
            
            helper = i+1;
            helper_2 = helper;
            while (helper <= 39) 
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
            helper = i-1;
            while (helper >= 0) 
            {
                map[helper][j] = ' ';
                helper--;
            }
            continue;
        }
        //Вставляется необходимая буква на уровень выше.
        if (random_number > probability / 2 && random_number <= probability && i > 8 && j >=3) 
        {
            i--;
            map[i][j] = 'L';
            helper = i + 1;
            helper_2 = helper;
            while (helper <= 39) 
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
            helper = i-1;
            while (helper >= 0) 
            {
                map[helper][j] = ' ';
                helper--;
            }
            continue;
        }
        // Условия пропускает ту строку которая позволит нам делать одну из следующий операций 2 или 3 блока вверх и вниз соответственно. Шанс еще меньше чем у предыдущих вставок.
        if (random_number > probability && random_number <= 0.4 && i <= 30 && i >= 10 && j >= 3) 
        {
            //Вставка на 2 буквы вверх
            if (random_number <= 0.335) 
            { 
                i = i - 2;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                helper = i + 2;
                helper_2 = helper;
                while (helper <= 39) 
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
            //Вставка на 2 буквы вниз. При этом учитываем, что вниз мы идем только если до этого шли хотя бы две итерации на одном и том же уровне. 
            if(random_number > 0.335 && random_number <= 0.370) {
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
                    map[i - 1][j - 1] = ' ';
                }
                else {}
                helper = i + 1;
                helper_2 = helper;
                while (helper <= 39) 
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
            //Вставка на 3 буквы вверх
            if (random_number > 0.370 && random_number <= 0.385) 
            {
                i = i - 3;
                map[i][j] = 'L';
                map[i + 1][j] = 'C';
                map[i + 2][j] = 'C';
                helper = i + 3;
                helper_2 = helper;
                while (helper <= 39) {
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
            //Вставка на 3 буквы вниз. При этом учитываем, что вниз мы идем только если до этого шли хотя бы две итерации на одном и том же уровне.
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
                    map[i - 1][j - 1] = 'P';
                }
                else if (map[i - 2][j - 2] == ' ') 
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = 'P';
                }
                else if (map[i - 3][j - 2] == ' ') 
                {
                    map[i - 3][j - 1] = ' ';
                    map[i - 2][j - 1] = 'P';
                }
                else{}
                helper = i + 1;
                helper_2 = helper;
                while (helper <= 39) 
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
        // Генерируем рандомый водоем.
        if (random_number > 0.4 && random_number <= 0.420 && j <= 180 && j >= 3 ) 
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
                while (helper <= 39) 
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
            while (helper <= 39) 
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
        //Вставляется буква на том же уровне если ничего из выше перечисленного не выполнилось.
        if(i < 39 && i > 1)
        { 
            map[i][j] = 'A';
            helper = i + 1;
            helper_2 = helper;
            while (helper <= 39) 
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


    //Генерация пещеры.
    //Установка рандомных координат начала работы, установка высоты и вероятности сдвига.
     probability = 0.70;
     std::uniform_real_distribution<float> dist_j(20, 180);    
     int h = 5;
     int l = dist_j(gen);

     //Цикл который спускает нашу "лопату" до опеределенной координаты высоты с неопределенным сдвигом по горизонтали.
     for (int ch = h; ch < 35; ch++) 
     {
         random_number = dist(gen);
         //Сдвиг вправо.
         if (random_number <= probability / 2 && l <= 180) 
         {
             l++;
             for (int i = ch + 1; i >= ch - 1; i--) 
             {
                 for (int j = l - 1; j <= l + 1; j++) 
                 {
                     if (map[i][j] != 'W' && map[i][j] != 'w') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                     ch--;
                 }
             }
             continue;
         }
         //Сдвиг влево.
         if (random_number > probability / 2 && random_number <= probability && l >= 20) 
         {
             l--;
             for (int i = ch + 1; i >= ch - 1; i--) 
             {
                 for (int j = l - 1; j <= l + 1; j++) 
                 {
                     if (map[i][j] != 'W' && map[i][j] != 'w') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                     ch--;
                 }
             }
             continue;
         }
         //Если сдвига нет то просто копаем вперед.
         if(true)
         {
             for (int i = ch + 1; i >= ch - 1; i--) 
             {
                 for (int j = l - 1; j <= l + 1; j++) 
                 {
                     if (map[i][j] != 'W' && map[i][j] != 'w') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                     ch--;
                 }
             }
             continue;
         }
     }

     //Установка новой вероятности для сдвига по вертикали при компке по горизонтали
     probability = 0.70;
     h = 33;

     //Цикл который двигает лопату по горизонтали с неопределенным сдвигом по вертикали.
     for (int ch = l; ch >= 10; ch--) 
     {
         random_number = dist(gen);
         //Сдвиг вверх
         if (random_number <= probability / 2 && h >= 25) 
         {
             h = h - 1;
             for (int i = h - 2; i <= h + 2; i++) 
             {
                 for (int j = ch - 2; j <= ch + 2; j++) 
                 {
                     if (map[i][j] == 'G') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                 }
             }
             continue;
         }
         //Сдвиг вниз
         if (random_number > probability / 2 && random_number <= probability && h <= 35) 
         {
             h = h + 1;
             for (int i = h - 2; i <= h + 2; i++) 
             {
                 for (int j = ch - 2; j <= ch + 2; j++) 
                 {
                     if (map[i][j] == 'G') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                 }
             }
             continue;
         }
         //Если сдвига нет то просто копаем в лево.
         if (true) 
         {
             for (int i = h - 2; i <= h + 2; i++) 
             {
                 for (int j = ch - 2; j <= ch + 2; j++) 
                 {
                     if (map[i][j] == 'G') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }            
                 }
             }
             continue;
         }
     }

     //Тот же самый алгоритм только сдвиг идет в право от точки в которуб лопата спустилась.
     h = 33;
     for (int ch = l; ch <= 190; ch++) 
     {
         random_number = dist(gen);
         //Сдвиг вверх.
         if (random_number <= probability / 2 && h >= 25) 
         {
            h = h - 1;
            for (int i = h - 2; i <= h + 2; i++) 
            {
                for (int j = ch - 2; j <= ch + 2; j++) 
                {
                    if (map[i][j] == 'G') 
                    {
                        map[i][j] = ' ';
                        continue;
                    }
                }
            }
             continue;
         }
         //Сдвиг вниз.
         if (random_number > probability / 2 && random_number <= probability && h <= 35) 
         {
             h = h + 1;
             for (int i = h - 2; i <= h + 2; i++) 
             {
                 for (int j = ch - 2; j <= ch + 2; j++) 
                 {
                     if (map[i][j] == 'G') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                 }
             }
             continue;
         }
         //Если сдвига нет то просто копаем в право.
         if (true) 
         {
             for (int i = h - 2; i <= h + 2; i++) 
             {
                 for (int j = ch - 2; j <= ch + 2; j++) 
                 {
                     if (map[i][j] == 'G') 
                     {
                         map[i][j] = ' ';
                         continue;
                     }
                 }
             }
             continue;
         }
     }


    //Генерация островов.
  std::uniform_real_distribution<float> dist_quantity(40, 90);
  std::uniform_real_distribution<double> dist_island_width(3, 15);
  std::uniform_real_distribution<double> dist_island_deep(1, 3);
  std::uniform_real_distribution<float> dist_h(3, 20);
  std::uniform_real_distribution<float> dist_l(5, 180);
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
                      else { map[h][l] = 'A';}
  
                      ch = 0;
                      while (ch <= random_deep) 
                      {
                          ch++;
                          if (flag == 0) { map[h + ch][l] = 'C'; }
                          else if (flag == random_width) { map[h + ch][l] = 'D'; }
                          else { map[h + ch][l] = 'B';}
  
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



