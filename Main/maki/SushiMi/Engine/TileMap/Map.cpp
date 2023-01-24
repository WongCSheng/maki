#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

/*set a static grid first*/
#define GRID_COL 30
#define GRID_ROW 30

#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define MAKI 3
#define GOAL 4

int grid_row = 30;
int grid_col = 30;

int gGrids[GRID_ROW][GRID_COL];

namespace Core
{
	Core::Map::Map()
	{
	}

	Core::Map::~Map()
	{
	}

	int Core::Map::initMap(const char* Filename)
	{
		//Open File using ifstream
		std::fstream fin(Filename);
		if(!fin)
		{
			std::cout << "Unable to open csv file!";
			return 0;
		}

		return 0;
	}

	void Core::Map::DrawMap()
	{
	}
}