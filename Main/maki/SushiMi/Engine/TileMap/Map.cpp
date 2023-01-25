#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>


int Core::Map::grid_row = 0;
int Core::Map::grid_col = 0;

int Core::Map::gGrids[GRID_ROW][GRID_COL];

namespace Core
{
	Map::Map()
	{
	}

	Map::~Map()
	{
	}

	int Map::initMap(std::string Filename)
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

	void Map::DrawMap()
	{
	}
}