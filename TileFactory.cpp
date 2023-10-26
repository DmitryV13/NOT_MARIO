#include "stdafx.h"
#include "TileFactory.h"

sf::IntRect TileFactory::initRect_tile(char tile_C)
{
	if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
	if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60); }
	if (tile_C == 'C') { return sf::IntRect(130, 2, 60, 60); }
	if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60); }
	if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60); }
	if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60); }
}


//TileFactory::TileFactory() {
//    std::string template_1[20] = {
//  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAF",
//  "F                                                                                                 F",
//  "F                                                                                                 F",
//  "F                                                                                                 F",
//  "F                                                                                                 F",
//  "F                                                                                                 F",
//  "F                                                                                                 F",
//  "F   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            F",
//  "F   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           F",
//  "F   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           F",
//  "F   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           F",
//  "F   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             F",
//  "F   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            F",
//  "F   FFF     FFF        FFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    F",
//  "F                                                        F                                        F",
//  "FF                  FFF                                FFF                                        F",
//  "F F              FFFFFFF            F          F     FFFFF                                        F",
//  "FJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//  "FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIF",
//    };


TileFactory::TileFactory()
{
	/* std::string template_1[20] = {
   "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAF",
   "F                                                                                                 F",
   "F                                                                                                 F",
   "F                                                                                                 F",
   "F                                                                                                 F",
   "F                                                                                                 F",
   "F                                                                                                 F",
   "F   FFF     FFF      FFFFF     FFFFFFFFFFF          FFF     FFF       FFF      FFFFFFF            F",
   "F   FFFF    FFF     FFFFFFF    FFFFFFFFFFF          FFFF   FFFF      FFFFF     FFFFFFFF           F",
   "F   FFFFF   FFF    FF     FF       FFF              FFFFF FFFFF     FFF FFF    FFF   FF           F",
   "F   FFFFFFFFFFF   FFF     FFF      FFF      FFFFF   FFF FFF FFF    FFF   FFF   FFFFFFFF           F",
   "F   FFF   FFFFF    FF     FF       FFF              FFF     FFF    FFFFFFFFF   FFFFFF             F",
   "F   FFF    FFFF     FFFFFFF        FFF              FFF     FFF   FFF     FFF  FFF FFF            F",
   "F   FFF     FFF        FFF         FFF              FFF     FFF   FFF     FFF  FFF  FFF  F F F    F",
   "F                                                        F                                        F",
   "FF                  FFF                                FFF                                        F",
   "F F              FFFFFFF            F          F     FFFFF                                        F",
   "FJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
   "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
   "FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIF", };*/
	std::string template_1[n][m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == 0 || j == 0)
			{
				template_1[i][j] = " ";
			}
			else
			{
				template_1[i][j] = "B";
			}
		}
	}


	map_generation(template_1);

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < m; j++)
		{
			template_1[i][j] = " ";
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << template_1[i][j];
		}
		std::cout << std::endl;
	}

	
	Tile tile_B(initRect_tile('B'), 'B');
	Tile tile_C(initRect_tile('C'), 'C');
	Tile tile_D(initRect_tile('D'), 'D');
	Tile tile_L(initRect_tile('L'), 'L');
	Tile tile_A(initRect_tile('A'), 'A');
	Tile tile_P(initRect_tile('P'), 'P');

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (template_1[i][j] == "B") { tile_map_inFactory[i][j] = tile_B; }
			if (template_1[i][j] == "C") { tile_map_inFactory[i][j] = tile_C; }
			if (template_1[i][j] == "D") { tile_map_inFactory[i][j] = tile_D; }
			if (template_1[i][j] == "L") { tile_map_inFactory[i][j] = tile_L; }
			if (template_1[i][j] == "L") { tile_map_inFactory[i][j] = tile_L; }
			if (template_1[i][j] == "A") { tile_map_inFactory[i][j] = tile_A; }
		
			if (template_1[i][j] == "P") { tile_map_inFactory[i][j] = tile_P; }
		}
	}
}

bool TileFactory::getPosPlayer(int i, int j)
{
	return tile_map_inFactory[i][j].give_player_info();
}

/*for(int f = 0; f < 10;f++)
	{
		int i = rand() % 11 + f ;

	afill(template_2, i, 1);
	}*/
void TileFactory::map_generation(std::string template_2[n][m])
{
	int i = rand() % 20 + 5, j = 1;
	
	afill(template_2, i, j);
}

void TileFactory::down(std::string (*map)[200], int &i, int &j)
{
	int step = rand() % 10 + 1;
	for (int k = j; k < step+j && k<m-2; k++)
	{
		for (int g = i++; g < i + 2  && g < 38; g++)
		{
			map[g][k] = " ";
			if (g == i + 1) {
				map[g + 1][k] = "B";
			}
		}
	}
	if(j+step < m-1)j += step;
	
}

void TileFactory::up(std::string(* map)[200], int &i, int &j)
{
	int step = rand() % 10 + 1;
	for (int k = j; k < step+j && k < m - 2; k++)
	{
		map[i+2][k] = "B";
		for (int g = --i+2; g > i - 2 && g > 5; g--)
		{
			map[g][k] = " ";
		}
	}
	if (j + step < m - 1)j += step;
}

void TileFactory::directly(std::string(* map)[200], int &i, int &j)
{
	int step = rand() % 10 + 1;
	for (int k = j; k < step+j && k < m - 2; k++)
	{
		for (int g = i + 4; g > i - 1 && g > 5; g--)
		{
			if (g == i + 4) {
				map[g+1][k] = "B";
			}
				map[g][k] = " ";

		}
	}

	if (j + step < m - 1)j += step;
}

void TileFactory::zigzag(std::string(* map)[200], int &i, int &j, int area)
{
	
	if (i == 20) i += area;
	int p = i;
		while (p < n/2)
		{
			down(map, i, j);
			p = i;
		}
		while (p > n / 2)
		{
			up(map, i, j);
			p = i;
		}
		
}

void TileFactory::river(std::string(* map)[200], int& i, int& j)
{
	int step = rand() % 10 + 1;
	if (i > 5) up(map, i, j);
	directly(map, i, j);
	//down
	for (int k = j; k < step + j && k < m - 2; k++)
	{
		for (int g = 5 + i++; g > i - 2  && g < 38 && g > 5; g--)
		{
			map[g][k] = " ";
			
		}
	}
	j += step;
	//right
	for (int k = j; k < 2*step + j && k < m - 2; k++)
	{
		for (int g = i + 4; g > i - 1 && g > 5 && g < 38; g--)
		{
			if (g == i + 4) {
				map[g + 1][k] = "B";
			}
			map[g][k] = " ";

		}
	}
	j += step*2;
	//up
	for (int k = j; k < step + j && k < m - 2; k++)
	{
		
		for (int g = 4 + i-- ; g  > i - 1  && g < 38  && g > 5; g--)
		{
			map[g][k] = " ";
		}
	}
	j += step;


	//fill water
	for(int p = i + step+5; p > i+5; p--)
	{
		for(int y =  j - step*4; y < j; y ++)
		{
			if (map[p][y] == " ") map[p][y] = "B";
		}
	}

	directly(map, i, j);

}

void TileFactory::afill(std::string map[n][m], int &i, int &j)
{
	if (j > m - 20)
		return;
	 
	int choiñå = rand() % 4;
	if (choiñå == 0 && i > 35) down(map, i, j);
	else if (choiñå == 1 && i < 5) up(map, i, j);
	else if (choiñå == 2 ) directly(map, i, j);
	else if (choiñå == 3 && i < 35 && i > 4) river(map, i, j);
	//else if (choiñå == 5 && i > 10) gap(map, i, j);
	//else if (choice == 6) hole(map, i, j);
	else zigzag(map, i, j, (i > 20) ? -1 : 1);

	afill(map, i, j);

	/*int d;
	int tmp_i = i;
	if (rand() % 2 && i < 15 || i < 5)
	{
		d = i + rand() % 3 + 2;
		for (int k = i; k < d && k < n; k++)
		{
			map[k][j] = " ";
		}
		i = rand() % (d - i) + i;
	}

	else if(i > 5)
	{
		d = i - rand() % 1 - 2;
		for (int k = i; k > d+1 && k>0; k--)
		{
			map[k][j] = " ";
		}
		i = rand() % (i - d) + d;
	}else
	{
		d = i + rand() % 2 + 2;
		for (int k = i; k < d+3 && k < n; k++)
		{
			map[k][j] = " ";
		}
		i = rand() % (d - i) + i;
	}

	



	afill(map, i, j + 1);*/
	/*if (i <15 &&(tmp_i+3 == i) ) 
		afill(map, i-4, j + 1);
	if ( i > 5  &&( tmp_i - 3 == i))
		afill(map, i+4, j + 1);*/
}
