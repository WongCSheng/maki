#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "../../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Headers/SceneManager.h"

/*
 * What each grid number means:
 * 0 - free space
 * 1 - wall
 * 2 - Player
 * 3 - ingredient
 * 4 - sinkhole
 * 9 - Goal
 */

int Core::Map::grid_row = 0;
int Core::Map::grid_col = 0;

int Core::Map::gGrids[GRID_ROW][GRID_COL];
int width, height;
int win = 0;
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
		SceneManager::tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2.jpg");
		

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
				/*Load texture depending on the grid*/
				if (gGrids[r][c] == 2)
				{
					Window::player->playerpos.x = r / static_cast<float>(grid_row) * width;
					Window::player->playerpos.y = c / static_cast<float>(grid_col) * height;
					Window::player->playerpos_restart.x = Window::player->playerpos.x;
					Window::player->playerpos_restart.y = Window::player->playerpos.y;
					Window::player->sp->transformation.Position.x = r / static_cast<float>(grid_row) * width;
					Window::player->sp->transformation.Position.y = c / static_cast<float>(grid_col) * height;
					/*save player index in grid*/
					Window::player->player_grid_pos.x = r;
					Window::player->player_grid_pos.y = c;
					/*save initial index for restart purposes*/
					Window::player->player_initial_grid_pos.x = r;
					Window::player->player_initial_grid_pos.y = c;
				}
				if(gGrids[r][c] == 3)
				{
					SceneManager::ingredient = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");
					Window::ingredient->ingredient_Grid_pos.x = r;
					Window::ingredient->ingredient_Grid_pos.y = c;
				}
				if(gGrids[r][c] == 9)
				{
					SceneManager::goal = new Sprite("../textures/Tiles/Pods/PodCover_3.png");
					Window::goal->goal_Grid_pos.x = r;
					Window::goal->goal_Grid_pos.y = c;
				}
				if(gGrids[r][c] == 4)
				{
					SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
					Window::trap->trap_Grid_pos.x = r;
					Window::trap->trap_Grid_pos.y = c;
				}
			}
			std::cout << std::endl;
		}


		return 1;
	}

	bool Map::isStuck()
	{
		// if player's grid index is 99, means its STUCK
		if(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == 99 || 
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == 100)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void Map::collision_check_right()
	{
		if(isStuck() == 0)
		{
			/*check right neighbour*/
			if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3 &&
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
			/*check for ingredient & pod*/
			else if (Window::ingredient->ingredient_Grid_pos.x == Window::goal->goal_Grid_pos.x - 1 &&
				Window::ingredient->ingredient_Grid_pos.y == Window::goal->goal_Grid_pos.y)
			{
				Window::ingredient->ingredient_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				SceneManager::destroyGoal();
				SceneManager::goal = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
				Window::goal->goal_Grid_pos.x = Window::ingredient->ingredient_Grid_pos.x;
				Window::goal->goal_Grid_pos.y = Window::ingredient->ingredient_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check object*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3)
			{
				Window::ingredient->ingredient_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::ingredient->ingredient_Grid_pos.x][Window::ingredient->ingredient_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 4)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x+1;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y;
				Window::player->move_right();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 99;
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
				Window::player->player_grid_pos.x++;
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
	}

	void Map::collision_check_left()
	{
		if(isStuck() == 0)
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
			/*check for ingredient & pod*/
			else if (Window::ingredient->ingredient_Grid_pos.x == Window::goal->goal_Grid_pos.x + 1 &&
				Window::ingredient->ingredient_Grid_pos.y == Window::goal->goal_Grid_pos.y)
			{
				Window::ingredient->ingredient_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 99;
				SceneManager::destroyGoal();
				SceneManager::goal = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
				Window::goal->goal_Grid_pos.x = Window::ingredient->ingredient_Grid_pos.x;
				Window::goal->goal_Grid_pos.y = Window::ingredient->ingredient_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check object*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 3)
			{
				Window::ingredient->ingredient_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::ingredient->ingredient_Grid_pos.x][Window::ingredient->ingredient_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 4)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x - 1;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y;
				Window::player->move_left();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 99;
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

	
	}

	void Map::collision_check_up()
	{
		if(isStuck() == 0)
		{
			/*check up neighbour*/
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 1)
			{
				std::cout << "Wall on top" << std::endl;
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 1)
			{
				std::cout << "Wall on top" << std::endl;
				Window::player->stop();
			}
			/*check for ingredient & pod*/
			else if (Window::ingredient->ingredient_Grid_pos.x == Window::goal->goal_Grid_pos.x &&
				Window::ingredient->ingredient_Grid_pos.y == Window::goal->goal_Grid_pos.y + 1)
			{
				Window::ingredient->ingredient_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				SceneManager::destroyGoal();
				SceneManager::goal = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
				Window::goal->goal_Grid_pos.x = Window::ingredient->ingredient_Grid_pos.x;
				Window::goal->goal_Grid_pos.y = Window::ingredient->ingredient_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check object*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3)
			{
				Window::ingredient->ingredient_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::ingredient->ingredient_Grid_pos.x][Window::ingredient->ingredient_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 4)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y - 1;
				Window::player->move_up();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 99;
			}
			/*check for obj & pod*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 9)
			{
				Window::player->move_up();
				SceneManager::destroyGoal();
				SceneManager::goal = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
				Window::goal->goal_Grid_pos.x = Window::player->player_grid_pos.x;
				Window::goal->goal_Grid_pos.y = Window::player->player_grid_pos.y - 1;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
			}
			else
			{
				Window::player->move_up();
				Window::player->player_grid_pos.y--;
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

	}

	void Map::collision_check_down()
	{
		if(isStuck() == 0)
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
			/*check for ingredient & pod*/
			else if (Window::ingredient->ingredient_Grid_pos.x == Window::goal->goal_Grid_pos.x &&
				Window::ingredient->ingredient_Grid_pos.y == Window::goal->goal_Grid_pos.y - 1)
			{
				Window::ingredient->ingredient_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				SceneManager::destroyGoal();
				SceneManager::goal = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
				Window::goal->goal_Grid_pos.x = Window::ingredient->ingredient_Grid_pos.x;
				Window::goal->goal_Grid_pos.y = Window::ingredient->ingredient_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check object*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3)
			{
				Window::ingredient->ingredient_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::ingredient->ingredient_Grid_pos.x][Window::ingredient->ingredient_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr(Window::ingredient->ingredient_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient->ingredient_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::drawIngr();
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
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 4)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y + 1;
				Window::player->move_down();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 99;
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
					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawIngr();
				}
				if (gGrids[r][c] == 4)
				{
					SceneManager::loadTrap(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawTrap();
				}
				if (gGrids[r][c] == 9)
				{
					SceneManager::loadGoal(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawGoal();
				}
			}
		}
	}
}