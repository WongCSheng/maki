#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "../../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Headers/SceneManager.h"


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
		SceneManager::tile = new Sprite("../textures/Tiles/Ingredients/Ingredients0_cucumber.png");
		SceneManager::obj = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");
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
		for(int c = 0; c < grid_col; c++)
		{
			for(int r = 0; r < grid_row; r++)
			{
				fin >> gGrids[r][c];
			}
		}
		/*Testing whether is loaded correctly*/
		for(int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				std::cout << gGrids[r][c];
				if (gGrids[r][c] == 2)
				{
					Window::player->playerpos.x = r / static_cast<float>(grid_row) * width;
					Window::player->playerpos.y = c / static_cast<float>(grid_col) * height;
					Window::player->sp->transformation.Position.x = r / static_cast<float>(grid_row) * width;
					Window::player->sp->transformation.Position.y = c / static_cast<float>(grid_col) * height;
					/*save player index in grid*/
					Window::player->player_grid_pos.x = r;
					Window::player->player_grid_pos.y = c;
				}
				if(gGrids[r][c] == 3)
				{
					Window::obj->obj_Grid_pos.x = r;
					Window::obj->obj_Grid_pos.y = c;
				}
			}
			std::cout << std::endl;
		}


		return 1;
	}

	void Map::collision_check_right()
	{
		/*check right neighbour*/
		if(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3 && 
			gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == 1)
		{
			std::cout << "Wall on right" << std::endl;
			Window::player->stop();
		}
		/*check wall*/
		else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 1)
		{
			std::cout << "Wall on right" << std::endl;
			Window::player->stop();
		}
		else if(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3)
		{
			Window::obj->obj_Grid_pos.x++;
			Window::player->player_grid_pos.x++;
			gGrids[Window::obj->obj_Grid_pos.x][Window::obj->obj_Grid_pos.y] = 3;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
			Window::player->move_right();
			SceneManager::loadTile(Window::obj->obj_Grid_pos.x / static_cast<float>(grid_row) * width, Window::obj->obj_Grid_pos.y / static_cast<float>(grid_col) * height);
			std::cout << "Push object" << std::endl;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			Window::player->move_right();
			Window::player->player_grid_pos.x ++;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
		
	}

	void Map::collision_check_left()
	{
		/*check right neighbour*/
		if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 3 &&
			gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == 1)
		{
			std::cout << "Wall on left" << std::endl;
			Window::player->stop();
		}
		/*check wall*/
		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 1)
		{
			std::cout << "Wall on left" << std::endl;
			Window::player->stop();
		}
		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 3)
		{
			Window::obj->obj_Grid_pos.x--;
			Window::player->player_grid_pos.x--;
			gGrids[Window::obj->obj_Grid_pos.x][Window::obj->obj_Grid_pos.y] = 3;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
			Window::player->move_left();
			SceneManager::loadTile(Window::obj->obj_Grid_pos.x / static_cast<float>(grid_row) * width, Window::obj->obj_Grid_pos.y / static_cast<float>(grid_col) * height);
			std::cout << "Push object" << std::endl;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			Window::player->move_left();
			Window::player->player_grid_pos.x--;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}

	}

	void Map::collision_check_up()
	{
		/*check up neighbour*/
		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3 &&
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 1)
		{
			std::cout << "Wall on top" << std::endl;
			Window::player->stop();
		}
		/*check wall*/
		else if(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 1)
		{
			std::cout << "Wall on top" << std::endl;
			Window::player->stop();
		}
		/*check object*/
		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3)
		{
			Window::obj->obj_Grid_pos.y--;
			Window::player->player_grid_pos.y--;
			gGrids[Window::obj->obj_Grid_pos.x][Window::obj->obj_Grid_pos.y] = 3;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
			Window::player->move_up();
			SceneManager::loadTile(Window::obj->obj_Grid_pos.x / static_cast<float>(grid_row) * width, Window::obj->obj_Grid_pos.y / static_cast<float>(grid_col) * height);
			std::cout << "Push object" << std::endl;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			Window::player->move_up();
			Window::player->player_grid_pos.y --;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
	}

	void Map::collision_check_down()
	{
		/*check up neighbour*/
		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3 &&
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == 1)
		{
			std::cout << "Wall on bottom" << std::endl;
			Window::player->stop();
		}
		/*check wall*/
		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 1)
		{
			std::cout << "Wall on bottom" << std::endl;
			Window::player->stop();
		}
		/*check object*/
		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3)
		{
			Window::obj->obj_Grid_pos.y++;
			Window::player->player_grid_pos.y++;
			gGrids[Window::obj->obj_Grid_pos.x][Window::obj->obj_Grid_pos.y] = 3;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
			Window::player->move_down();
			SceneManager::loadObj(Window::obj->obj_Grid_pos.x / static_cast<float>(grid_row) * width, Window::obj->obj_Grid_pos.y / static_cast<float>(grid_col) * height);
			SceneManager::drawObj();
			std::cout << "Push object" << std::endl;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			Window::player->move_down();
			Window::player->player_grid_pos.y++;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
			for (int c = 0; c < grid_col; c++)
			{
				for (int r = 0; r < grid_row; r++)
				{
					std::cout << gGrids[r][c];
				}
				std::cout << std::endl;
			}
		}
	}

	void Map::DrawMap()
	{
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				if (gGrids[r][c] == 1)
				{
					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawTile();
				}
				if (gGrids[r][c] == 3)
				{
					SceneManager::loadObj(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawObj();
				}
			}
		}
	}
}