#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "../../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"


int Core::Map::grid_row = 0;
int Core::Map::grid_col = 0;

int Core::Map::gGrids[GRID_ROW][GRID_COL];
int width, height;

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

		glfwGetWindowSize(Window::window_ptr, &width, &height);
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
		tile_width = width / grid_row;
		tile_height = height / grid_col;
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
			for (int c = 0; c < grid_col; c++)
			{
				std::cout << gGrids[r][c] << "\t";
				if (gGrids[r][c] == 2)
				{
					Window::player->playerpos.x = r / static_cast<float>(grid_row) * width;
					Window::player->playerpos.y = c/ static_cast<float>(grid_col) * height;
					Window::player->sp->transformation.Position.x = r / static_cast<float>(grid_row) * width;
					Window::player->sp->transformation.Position.y = c / static_cast<float>(grid_col) * height;
				}
			}
			std::cout << std::endl;
		}


		return 1;
	}

	void Map::DrawMap()
	{
	}
}