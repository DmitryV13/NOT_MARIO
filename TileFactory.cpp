#include "stdafx.h"
#include "TileFactory.h"

sf::IntRect TileFactory::initRect_tile(char tile_C)
{
	if (tile_C == 'A') { return sf::IntRect(66, 2, 60, 60); }
	if (tile_C == 'B') { return sf::IntRect(2, 2, 60, 60); }
	if (tile_C == 'C') { return sf::IntRect(2, 66, 60, 60); }
	if (tile_C == 'c') { return sf::IntRect(2, 130, 60, 60); }
	if (tile_C == 'D') { return sf::IntRect(194, 2, 60, 60); }
	if (tile_C == 'U') { return sf::IntRect(130, 2, 60, 60); }
	if (tile_C == 'L') { return sf::IntRect(258, 2, 60, 60); }
	if (tile_C == 'P') { return sf::IntRect(322, 2, 60, 60); }
	if (tile_C == 'Q') { return sf::IntRect(514, 2, 60, 60); }
}


TileFactory::TileFactory()
{
	char template_1[n][m];
	for (int i = 0; i < n/2; ++i) {
		for (int j = 0; j < m; ++j) {
			template_1[i][j] = ' ';
		}
	}

	// Çàïîëíÿåì îñòàâøèåñÿ 20 ñòğîê ñèìâîëàìè 'B'
	for (int i = n/2; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			template_1[i][j] = 'B';
		}
	}


	

	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			template_1[i][j] = 'N';
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
	}*/
	filter_map(template_1);
	filter_map(template_1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << template_1[i][j];
		}
		std::cout << std::endl;
	}
	filter_map1(template_1);
	artist_method(template_1);
	fill_lakes_with_ground(template_1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << template_1[i][j];
		}
		std::cout << std::endl;
	}
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
	Tile tile_U(initRect_tile('U'), 'U', 'U');
	Tile tile_L(initRect_tile('L'), 'L', 'L');
	Tile tile_P(initRect_tile('P'), 'P', 'P');
	Tile tile_Q(initRect_tile('Q'), 'Q', 'Q');

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (template_1[i][j] == 'A') { tile_map_inFactory[i][j] = tile_A; }
			if (template_1[i][j] == 'B') { tile_map_inFactory[i][j] = tile_B; }
			if (template_1[i][j] == 'C') { tile_map_inFactory[i][j] = tile_C; }
			if (template_1[i][j] == 'c') { tile_map_inFactory[i][j] = tile_c; }
			if (template_1[i][j] == 'U') { tile_map_inFactory[i][j] = tile_U; }
			if (template_1[i][j] == 'D') { tile_map_inFactory[i][j] = tile_D; }
			if (template_1[i][j] == 'L') { tile_map_inFactory[i][j] = tile_L; }
			if (template_1[i][j] == 'P') { tile_map_inFactory[i][j] = tile_P; }
			if (template_1[i][j] == 'Q') { tile_map_inFactory[i][j] = tile_Q; }
		}
	}
}

bool TileFactory::getPosPlayer(int i, int j)
{
	return tile_map_inFactory[i][j].give_player_info();
}


void TileFactory::map_generation(char template_2[n][m])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int i = rand() % 10 + 15, j = 0;
	start_of_map_generation_(template_2, i, j, gen);
}


void TileFactory::start_of_map_generation_(char map[n][m], int& i, int& j, std::mt19937 gen)
{
	std::uniform_int_distribution<int> cofShift(3, 5);

	int min = 1;
	int max = 5;
	std::uniform_int_distribution<int> distribution(min, max);
	int choice = distribution(gen);
	bool wormhole_b = true;
	int coutn = 5;
	int SHIFT;
	while (j < m)
	{
		SHIFT = cofShift(gen);
		int choice = distribution(gen);
		if (choice == 1 && i > 35)
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
}

void TileFactory::flatland(char (*map)[m], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int count = 0;
	int bool_tap = 0;
	for (int top = 0; top < shift; top++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == 'N')map[down][right] = 'B';
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
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

void TileFactory::mountainous_terrain(char (*map)[m], int& i, int& j, int& shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int bool_tap = distribution(gen);


	for (int STEP = 0; STEP < shift; STEP++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == 'N')map[down][right] = 'B';
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (map[up][right] == 'N')map[up][right] = ' ';
			}
			i += bool_tap;
		}
		j = right;
		for (; right < j + shift / 2 && right < m; right++)
		{
			for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == 'N')map[down][right] = 'B';
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (map[up][right] == 'N')map[up][right] = ' ';
			}
		}
		j = right;
		if (i >= 10 && i <= 25) bool_tap = distribution(gen);
		else if (i >= 25) bool_tap = -1;
		else bool_tap = 1;
	}
}

void TileFactory::water_bodies(char (*map)[m], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	int bool_tap = 1;
	int stat_i = i;

	for (int STEP = 0; STEP < 2; STEP++)
	{
		int right = j;
		for (; right < j + shift && right < m; right++)
		{
			for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ

			{
				if (up == stat_i)map[up][right] = 'C';
				if (up > stat_i) map[up][right] = 'c'; //ÁËÎÊ ÂÎÄÛ
				if (map[up][right] == 'N')map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
			}
			i += bool_tap;
		}
		j = right;
		for (; right < j + shift && right < m; right++)
		{
			for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
			{
				if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
			}
			for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ââåğõ
			{
				if (up == stat_i)map[up][right] = 'C';
				if (up > stat_i) map[up][right] = 'c'; //ÁËÎÊ ÂÎÄÛ
				if (map[up][right] == 'N')map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
			}
		}
		j = right;
		bool_tap = -1;
	}
}

void TileFactory::tunnel(char (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
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
		for (int down = i; down < n; down++) // ÇÀÏÎËÍÈÌ ÂÍÈÇ ÂÑÅ ÏÓÑÒÎÒÛ
		{
			if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
		}
		count_emptiness = emptiness(gen);
		count_block = emptiness(gen);

		for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ
		{
			map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
		}
		i += distribution(gen);
	}
	j = right;
}

void TileFactory::wormhole(char (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
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
			if (map[down][right] == 'N')map[down][right] = 'B'; //ÁËÎÊ ÄËß ÇÅÌËÈ
		}
		for (; top < i + 5 && top < n; top++)
		{
			map[top][right] = ' ';
		}
		for (int up = i - 1; up >= 0; up--) // ÇÀÏÎËÍÈÌ ÂÑÅ ââåğõ

		{
			if (map[up][right] == 'N')map[up][right] = ' '; //ÁËÎÊ ïóñòîòû
		}
	}

	if (j > m / 2)
	{
		std::uniform_int_distribution<int> stp_d(3, 4);
		int stp = stp_d(gen);
		right = j;
		for (; right > j - shift * 4 && right >= 0; right--)
		{
			top = i + 1;
			for (; top < i + 7 && top < n - 1; top++)
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
		for (; right < j + shift * 4 && right < m; right++)
		{
			top = i + 1;
			for (; top < i + 7 && top < n - 1; top++)
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

void TileFactory::cavern(char (*map)[200], int& i, int& j, int shift, std::mt19937 gen)
{
	std::uniform_int_distribution<int> distribution(-1, 1);
	std::uniform_int_distribution<int> cavern_rand(26, 35);
	std::uniform_int_distribution<int> cavern_rand_step(4, 6);
	int right = 0;
	int top = cavern_rand(gen);
	int step = cavern_rand_step(gen);
	i = top;
	for (; right < m; right++)
	{
		step = cavern_rand_step(gen);
		for (; top < i + step && top < n - 1; top++)
		{
			map[top][right] = ' ';
		}
		top = i;
		if (top > 35) top += -1;
		else top += distribution(gen);
		i = top;
	}
}


//stripping blocks 
void TileFactory::filter_map(char map[n][m])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] != ' ')
			{
				int emptyNeighbors = count_empty_neighbors(map, i, j);


				if (emptyNeighbors > 4)
				{
					map[i][j] = ' ';
				}
			}
		}
	}
}


void TileFactory::filter_map1(char map[n][m])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
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

bool TileFactory::has_blocks_on_both_sides(char map[n][m], int i, int j)
{
	if ((i > 0 && map[i - 1][j] != ' ') && (i < n - 1 && map[i + 1][j] != ' '))
	{
		return true; //emptiness in one block vertically
	}

	if ((j > 0 && map[i][j - 1] != ' ') && (j < m - 1 && map[i][j + 1] != ' '))
	{
		return true; //voids in one block horizontally
	}

	return false;
}

int TileFactory::count_empty_neighbors(char map[n][m], int i, int j)
{
	int emptyNeighbors = 0;
	if (i > 0 && map[i - 1][j] == ' ') emptyNeighbors++;
	if (i > 0 && j > 0 && map[i - 1][j - 1] == ' ') emptyNeighbors++;
	if (i > 0 && j < m && map[i - 1][j + 1] == ' ')emptyNeighbors++;
	if (i < n && j > 0 && map[i + 1][j - 1] == ' ')emptyNeighbors++;
	if (i < n && j < m && map[i + 1][j + 1] == ' ')emptyNeighbors++;
	if (i < n && map[i + 1][j] == ' ') emptyNeighbors++;
	if (j > 0 && map[i][j - 1] == ' ') emptyNeighbors++;
	if (j < m && map[i][j + 1] == ' ') emptyNeighbors++;

	return emptyNeighbors;
}

void TileFactory::artist_method(char map[n][m])
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m - 1; j++)
		{
			if (map[i][j] != ' ' && map[i][j] != 'c' && map[i][j] != 'C')
			{
				bool hasTop = (i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == 'C'));
				bool hasBottom = (i < n - 1 && map[i + 1][j] == ' ');
				bool hasLeft = (j > 0 && map[i][j - 1] == ' ');
				bool hasRight = (j < m - 1 && map[i][j + 1] == ' ');

				if (!hasTop && !hasLeft && !hasRight)
				{
					map[i][j] = 'B';
				}
				else if (hasTop && hasBottom && hasLeft && hasRight)
				{
					map[i][j] = 'A'; // Ñîñåäè ñïğàâà, ñëåâà è ñâåğõó 
				}
				else if (hasTop && hasRight)
				{
					map[i][j] = 'P'; // Ñîñåäè ñâåğõó è ñïğàâà 
				}
				else if (hasTop && hasLeft)
				{
					map[i][j] = 'L'; // Ñîñåäè ñâåğõó è ñëåâà 
				}
				else if (hasTop)
				{
					map[i][j] = 'A'; // Ñîñåä ñâåğõó 
				}
				else if (hasBottom)
				{
					map[i][j] = 'Q'; // Ñîñåä ñíèçó 
				}
				else if (hasLeft)
				{
					map[i][j] = 'U'; // Ñîñåä ñëåâà 
				}
				else if (hasRight)
				{
					map[i][j] = 'D'; // Ñîñåä ñïğàâà
				}
			}
		}
	}
}

//fix bug with soaring water
void TileFactory::fill_lakes_with_ground(char map[n][m])
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 'C' || map[i][j] == 'c')
			{
				if (map[i + 1][j] == ' ')
				{
					map[i + 1][j] = 'B';
				}
			}
		}
	}
}
