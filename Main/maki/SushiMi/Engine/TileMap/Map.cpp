#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

/*set a static grid first*/
#define GRID_COL 30
#define GRID_ROW 30

int grid_row;
int grid_col;

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
		std::ifstream fin(Filename);
		if(!fin)
		{
			std::cout << "Unable to open tilemap file!";
			return 0;
		}
		/*store the row and col of the tile*/
		fin >> grid_row;
		fin >> grid_col;
		for(int r = 0; r < grid_row; r++)
		{
			for(int c = 0; c < grid_col; c++)
			{
				fin >> gGrids[r][c];
			}
		}
		/*Testing whether is loaded correctly*/
		for(int r = 0; r < grid_row; r++)
		{
			for(int c = 0; c < grid_col; c++)
			{
				std::cout << gGrids[r][c] << "\t";
			}
			std::cout << std::endl;
		}
		return 1;
	}

	void Core::Map::DrawMap()
	{
	}
}