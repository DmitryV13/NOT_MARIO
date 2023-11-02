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
	if (tile_C == 'O') { return sf::IntRect(514, 2, 60, 60); }
	if (tile_C == 'W') { return sf::IntRect(2, 130, 60, 60); }
}


TileFactory::TileFactory()
{
	std::string template_1[n][m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			template_1[i][j] = "NaN";
		}
	}


	map_generation(template_1);

	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << template_1[i][j];
		}
		std::cout << std::endl;
	}
	filterMap(template_1);
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
	Tile tile_O(initRect_tile('O'), 'O');
	Tile tile_W(initRect_tile('W'), 'W');

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (template_1[i][j] == "B") { tile_map_inFactory[i][j] = tile_B; }
			if (template_1[i][j] == "C") { tile_map_inFactory[i][j] = tile_C; }
			if (template_1[i][j] == "D") { tile_map_inFactory[i][j] = tile_D; }
			if (template_1[i][j] == "L") { tile_map_inFactory[i][j] = tile_L; }
			if (template_1[i][j] == "A") { tile_map_inFactory[i][j] = tile_A; }
			if (template_1[i][j] == "O") { tile_map_inFactory[i][j] = tile_O; }
			if (template_1[i][j] == "W") { tile_map_inFactory[i][j] = tile_W; }
			if (template_1[i][j] == "P") { tile_map_inFactory[i][j] = tile_P; }
		}
	}
}

bool TileFactory::getPosPlayer(int i, int j)
{
	return tile_map_inFactory[i][j].give_player_info();
}


void TileFactory::map_generation(std::string template_2[n][m])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int i = rand() % 10 + 15, j = 0;

	afill(template_2, i, j, gen);
}


void TileFactory::afill(std::string map[n][m], int& i, int& j, std::mt19937 gen)
{
	std::uniform_int_distribution<int> cofShift(3, 5);

	int min = 1;
	int max = 5;
	std::uniform_int_distribution<int> distribution(min, max);
	int choice = distribution(gen);
	bool wormhole_b = true;
	int coutn = 5;
	int SHIFT;
	while (j != m)
	{
		SHIFT = cofShift(gen);
		int choice = distribution(gen);
		if (choice == 1 && i > 30)
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
	/*	else if (choice == 6)
			soaring_islands(map, i, j, SHIFT, gen);*/
	}
	cavern(map, i, j, SHIFT, gen);
	
}

void TileFactory::flatland(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);

	int bool_tap = 0;
	for (int top = 0; top < shift; top++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			if (bool_tap == 1)map[i][right] = "B"; //áëîê ñ òğàâîé ñâåğõó è ñëåâà
			else if (bool_tap == -1)map[i][right] = "B"; //ñïğàâà
			else
				map[i][right] = "B"; //ÁËÎÊ ÄËß ÒĞÀÂÛ Ñ ÂÅĞÕÍÅÉ ÑÒÎĞÎÍÛ

			for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
			}
		}
		j = right;
		bool_tap = distribution(gen);
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

void TileFactory::mountainous_terrain(std::string (*map)[200], int& i, int& j, int& shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int bool_tap = distribution(gen);


	for (int STEP = 0; STEP < shift; STEP++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			if (bool_tap == 1)map[i][right] = "B"; //áëîê ñ òğàâîé ñâåğõó è ñëåâà
			else if (bool_tap == -1)map[i][right] = "B"; //ñïğàâà
			else map[i][right] = "B"; //ÁËÎÊ ÄËß ÒĞÀÂÛ Ñ ÂÅĞÕÍÅÉ ÑÒÎĞÎÍÛ

			for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
			}
			i += bool_tap;
		}
		j = right;
		for (; right < j + shift / 2 && right < m; right++)
		{
			map[i][right] = "B"; // ÁËÎÊ ÒĞÀÂÀ ÑÂÅĞÕÓ
			for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
			}
		}
		j = right;
		if (i >= 10 && i <= 25) bool_tap = distribution(gen);
		else if (i >= 25) bool_tap = -1;
		else bool_tap = 1;
	}
}

void TileFactory::water_bodies(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int bool_tap = 1;
	int stat_i = i;

	for (int STEP = 0; STEP < 2; STEP++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			if (bool_tap == 1)map[i][right] = "P"; //áëîê ñ òğàâîé ñâåğõó è ñëåâà
			else if (bool_tap == -1)map[i][right] = "L"; //ñïğàâà
			else map[i][right] = "A"; //ÁËÎÊ ÄËß ÒĞÀÂÛ Ñ ÂÅĞÕÍÅÉ ÑÒÎĞÎÍÛ

			for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ

			{
				if (up > stat_i) map[up][right] = "W"; //ÁËÎÊ ÂÎÄÛ
				if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
			}
			i += bool_tap;
		}
		j = right;
		for (; right < j + shift && right < m; right++)
		{
			map[i][right] = "B"; // ÁËÎÊ ÒĞÀÂÀ ÑÂÅĞÕÓ
			for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (up > stat_i) map[up][right] = "W"; //ÁËÎÊ ÂÎÄÛ
				if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
			}
		}
		j = right;
		bool_tap = -1;
	}
}

void TileFactory::tunnel(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	std::uniform_int_distribution<int> emptiness(3, 5);
	int bool_tap = 1;
	int stat_i = i;
	i += bool_tap;
	int count_emptiness = 0;
	int count_block = 0;

	int right = j;

	for (; right < j + shift * 3 && right < m; right++)
	{
		if (bool_tap == 1)map[i][right] = "B"; //áëîê ñ òğàâîé ñâåğõó è ñëåâà
		else if (bool_tap == -1)map[i][right] = "B"; //ñïğàâà
		else map[i][right] = "A"; //ÁËÎÊ ÄËß ÒĞÀÂÛ Ñ ÂÅĞÕÍÅÉ ÑÒÎĞÎÍÛ

		for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
		{
			if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
		}
		count_emptiness = emptiness(gen);
		count_block = emptiness(gen);

		for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ

		{
			if (count_emptiness-- > 0) map[up][right] = " "; //ÁËÎÊ ïóñòîòû çàäíèé ôîí
			else if (count_block-- > 0) map[up][right] = "B"; //áëîå çåìëè ñâåğõó
			else if (count_block-- == -1)map[up][right] = "A"; //ÁËÎÊ ÑÂÅĞÕÓ
			else if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
		}
		i += distribution(gen);
	}
	j = right;
}

void TileFactory::wormhole(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int bool_tap = 1;
	int stat_i = i;
	int stat_j = j;

	if (i > 30)return;
	int right = j;
	int top = 0;
	int count = shift + 3;


	for (; right < j + 4 && right < m; right++)
	{
		top = i;

		for (int down = i + 1; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
		{
			if (map[down][right] == "NaN")map[down][right] = "B"; //ÁËÎÊ ÄËß ÇÅÌËÈ
		}
		for (; top < i + 5 && top < n; top++)
		{
			if (j == right )map[top][right] = "C";
			if (j + 3 == right)map[top][right] = "A";
				//áëîêè äëÿ ÷åğâàòî÷èíû íó èëè êàìíè òóïî, íó èëè çåìëÿ
			else if (top == i + 4) map[top][right] = "A";
			else map[top][right] = " "; //áëîêè ôîíà ïåøåğû èëè ÷åğâàòî÷èíû
		}
		for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ

		{
			if (map[up][right] == "NaN")map[up][right] = " "; //ÁËÎÊ ïóñòîòû
		}
	}

	if (j > m / 2) {
		std::uniform_int_distribution<int> stp_d(3, 4);
		int stp = stp_d(gen);
		right = j;
		for (; right > j - shift * 4; right--)
		{
			top = i + 1;
			for (; top < i + 7 && top < n - 1; top++)
			{
				if (top == i + 1)map[top][right] = "A"; //ÁËÎÊ ÊĞÀÅÂ Â ÏÅÙÅĞÊÅ
				else if (top == i + 6)map[top][right] = "A";
				else map[top][right] = " "; //áëîå ñòåíû, çàäíåãî ôîíà
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
		for (; right < j + shift * 4; right++) // Èçìåíèëñÿ çíàê ">" íà "<"
		{
			top = i + 1;
			for (; top < i + 7 && top < n - 1; top++)
			{
				if (top == i + 1) map[top][right] = "B"; // ÁËÎÊ ÊĞÀÅÂ Â ÏÅÙÅĞÊÅ
				else if (top == i + 6) map[top][right] = "A";
				else map[top][right] = " "; // Áëîêè ñòåíû, çàäíåãî ôîíà
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

void TileFactory::cavern(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{

	std::uniform_int_distribution<int> distribution(-1, 1);
	std::uniform_int_distribution<int> cavern_rand(26, 35);
	std::uniform_int_distribution<int> cavern_rand_step(4, 6);
	int right = 0;
	int top = cavern_rand(gen);
	int step = cavern_rand_step(gen);
	i = top;
	for(;right < m; right++)
	{
		step = cavern_rand_step(gen);
		for(;top < i+step && top < n-1; top++)
		{
			if(top == i)map[top][right] = "O";
			else if(top == i + step )map[top][right] = "O";
			else map[top][right] = " ";
		}
		top = i;
		if (top > 35) top += -1;
		else top+=distribution(gen);
		i = top;
	}



}

void TileFactory::soaring_islands(std::string (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
}

void TileFactory::filterMap(std::string map[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] != " ")
            {
                int emptyNeighbors = countEmptyNeighbors(map, i, j);

              
                if (emptyNeighbors > 4)
                {
                    map[i][j] = " ";
                }
            }
        }
    }
}

int TileFactory::countEmptyNeighbors(std::string map[n][m], int i, int j)
{
    int emptyNeighbors = 0;

    if (i > 0 && map[i - 1][j] == " ") emptyNeighbors++; // Ñâåğõó
	if (i > 0 && j > 0 && map[i - 1][j - 1] == " ") emptyNeighbors++;
	if (i > 0 && j < m && map[i - 1][j + 1] == " ")emptyNeighbors++;
	if (i < n && j>0 && map[i + 1][j - 1] == " ")emptyNeighbors++;
	if (i < n && j < m && map[i + 1][j + 1] == " ")emptyNeighbors++;
    if (i < n  && map[i + 1][j] == " ") emptyNeighbors++; // Ñíèçó
    if (j > 0 && map[i][j - 1] == " ") emptyNeighbors++; // Ñëåâà
    if (j < m  && map[i][j + 1] == " ") emptyNeighbors++; // Ñïğàâà

    return emptyNeighbors;
}
