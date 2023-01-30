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
 * 4 - ingredient 2
 * 50 - sinkhole
 * 9 - Goal1
 * 10- Goal2
 * If player go to sinkhole, grid change to 50. When reset, need reset sinkhole back
 * If player complete a goal, set grid of goal to 100.
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
		//this does deleting of textures
		SceneManager::destroyTile();
		SceneManager::destroyGoal1();
		SceneManager::destroyGoal2();
		SceneManager::destroyCover1();
		SceneManager::destroyIngr();
		SceneManager::destroyIngr();
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
					SceneManager::ingredient1 = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");
					Window::ingredient1->ingredient1_Grid_pos.x = r;
					Window::ingredient1->ingredient1_Grid_pos.y = c;
					SceneManager::ingredient1->ingredient1_initial_pos.x = r;
					SceneManager::ingredient1->ingredient1_initial_pos.y = c;
				}
				if(gGrids[r][c] == 4)
				{
					SceneManager::ingredient2 = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
					Window::ingredient2->ingredient2_Grid_pos.x = r;
					Window::ingredient2->ingredient2_Grid_pos.y = c;
					SceneManager::ingredient2->ingredient2_initial_pos.x = r;
					SceneManager::ingredient2->ingredient2_initial_pos.y = c;
				}
				if(gGrids[r][c] == 9)
				{
					SceneManager::goal1 = new Sprite("../textures/Tiles/Pods/Pod0_6.png");
					Window::goal1->goal1_Grid_pos.x = r;
					Window::goal1->goal1_Grid_pos.y = c;
					Window::numQuests += 1;

				}
				if(gGrids[r][c] == 10)
				{
					SceneManager::goal2 = new Sprite("../textures/Tiles/Pods/Pod0_4.png");
					Window::goal2->goal2_Grid_pos.x = r;
					Window::goal2->goal2_Grid_pos.y = c;
					Window::numQuests += 1;
				}
				if(gGrids[r][c] == 50)
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

	bool Map::isWin()
	{
		if(gGrids[Window::goal1->goal1_Grid_pos.x][Window::goal1->goal1_Grid_pos.y] == 100 &&
		gGrids[Window::goal2->goal2_Grid_pos.x][Window::goal2->goal2_Grid_pos.y] == 100)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}


	bool Map::isStuck()
	{
		// if player's grid index is 50, means its STUCK or put all ingr into goals
		if(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == 51 || 
			isWin() == TRUE)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void Map::collision_check_left()
	{
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 3 &&
				gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == 1 ||
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 4 &&
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
			/*check for ingredient1 & pod 1*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal1->goal1_Grid_pos.x + 1 &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal1->goal1_Grid_pos.y)
			{
				Window::ingredient1->ingredient1_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;


				//SceneManager::destroyGoal1();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient1 & pod 2*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal2->goal2_Grid_pos.x + 1 &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal2->goal2_Grid_pos.y)
			{
				Window::ingredient1->ingredient1_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100; //win condition
				std::cout << "win = 2" << std::endl;
				Window::questProgress += 1;
				//std::cout << "winvalue is " << isWin() << std::endl;
				std::cout << "progress is " << Window::questProgress << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check for ingredient2 & pod 1*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal1->goal1_Grid_pos.x + 1 &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal1->goal1_Grid_pos.y)
			{
				Window::ingredient2->ingredient2_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 3" << std::endl;
				Window::questProgress += 1;

				std::cout << "progress is " << Window::questProgress << std::endl;


				//SceneManager::destroyGoal1();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient2 & pod 2*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal2->goal2_Grid_pos.x + 1 &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal2->goal2_Grid_pos.y)
			{
				Window::ingredient2->ingredient2_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 4" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;



				//SceneManager::destroyGoal2(); //dont destroy here!!
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 3)
			{
				Window::ingredient1->ingredient1_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::ingredient1->ingredient1_Grid_pos.x][Window::ingredient1->ingredient1_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check ingr2*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 4)
			{
				Window::ingredient2->ingredient2_Grid_pos.x--;
				Window::player->player_grid_pos.x--;
				gGrids[Window::ingredient2->ingredient2_Grid_pos.x][Window::ingredient2->ingredient2_Grid_pos.y] = 4;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_left();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == 50)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x-1;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y;
				Window::player->move_left();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 51;
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
	}
	void Map::collision_check_right()
	{
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3 &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == 1 ||
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 4 &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == 1)
			{
				std::cout << "Wall on left" << std::endl;
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 1)
			{
				std::cout << "Wall on left" << std::endl;
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal1->goal1_Grid_pos.x - 1 &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal1->goal1_Grid_pos.y)
			{
				Window::ingredient1->ingredient1_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;


				//SceneManager::destroyGoal1();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient1 & pod 2*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal2->goal2_Grid_pos.x - 1 &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal2->goal2_Grid_pos.y)
			{
				Window::ingredient1->ingredient1_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 2" << std::endl;
				Window::questProgress += 1;

				std::cout << "progress is " << Window::questProgress << std::endl;
				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();
				Window::goal2->goal2_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check for ingredient2 & pod 1*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal1->goal1_Grid_pos.x - 1 &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal1->goal1_Grid_pos.y)
			{
				Window::ingredient2->ingredient2_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 3" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient2 & pod 2*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal2->goal2_Grid_pos.x - 1 &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal2->goal2_Grid_pos.y)
			{
				Window::ingredient2->ingredient2_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 4" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3)
			{
				Window::ingredient1->ingredient1_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::ingredient1->ingredient1_Grid_pos.x][Window::ingredient1->ingredient1_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check ingr2*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 4)
			{
				Window::ingredient2->ingredient2_Grid_pos.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::ingredient2->ingredient2_Grid_pos.x][Window::ingredient2->ingredient2_Grid_pos.y] = 4;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 50)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x + 1;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y;
				Window::player->move_right();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 51;
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
	void Map::collision_check_down()
	{
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == 1 ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 4 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == 1)
			{
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 1)
			{
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal1->goal1_Grid_pos.x &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal1->goal1_Grid_pos.y - 1)
			{
				Window::ingredient1->ingredient1_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient1 & pod 2*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal2->goal2_Grid_pos.x &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal2->goal2_Grid_pos.y - 1)
			{
				Window::ingredient1->ingredient1_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 2" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check for ingredient2 & pod 1*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal1->goal1_Grid_pos.x &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal1->goal1_Grid_pos.y - 1)
			{
				Window::ingredient2->ingredient2_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 3" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient2 & pod 2*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal2->goal2_Grid_pos.x &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal2->goal2_Grid_pos.y - 1)
			{
				Window::ingredient2->ingredient2_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 4" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3)
			{
				Window::ingredient1->ingredient1_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::ingredient1->ingredient1_Grid_pos.x][Window::ingredient1->ingredient1_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check ingr2*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 4)
			{
				Window::ingredient2->ingredient2_Grid_pos.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::ingredient2->ingredient2_Grid_pos.x][Window::ingredient2->ingredient2_Grid_pos.y] = 4;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 50)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y + 1;
				Window::player->move_down();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 51;
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
	}
	void Map::collision_check_up()
	{
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 1 ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 4 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 1)
			{
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 1)
			{
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal1->goal1_Grid_pos.x &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal1->goal1_Grid_pos.y + 1)
			{
				Window::ingredient1->ingredient1_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient1 & pod 2*/
			else if (Window::ingredient1->ingredient1_Grid_pos.x == Window::goal2->goal2_Grid_pos.x &&
				Window::ingredient1->ingredient1_Grid_pos.y == Window::goal2->goal2_Grid_pos.y + 1)
			{
				Window::ingredient1->ingredient1_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 2" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient1->ingredient1_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient1->ingredient1_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check for ingredient2 & pod 1*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal1->goal1_Grid_pos.x &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal1->goal1_Grid_pos.y + 1)
			{
				Window::ingredient2->ingredient2_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 3" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal1->goal1_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal1->goal1_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check for ingredient2 & pod 2*/
			else if (Window::ingredient2->ingredient2_Grid_pos.x == Window::goal2->goal2_Grid_pos.x &&
				Window::ingredient2->ingredient2_Grid_pos.y == Window::goal2->goal2_Grid_pos.y + 1)
			{
				Window::ingredient2->ingredient2_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 100;
				std::cout << "win = 4" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				//std::cout << "winvalue is " << isWin() << std::endl;


				//SceneManager::destroyGoal2();
				SceneManager::loadCover1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				SceneManager::cover1->draw();

				Window::goal2->goal2_Grid_pos.x = Window::ingredient2->ingredient2_Grid_pos.x;
				Window::goal2->goal2_Grid_pos.y = Window::ingredient2->ingredient2_Grid_pos.y;
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3)
			{
				Window::ingredient1->ingredient1_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::ingredient1->ingredient1_Grid_pos.x][Window::ingredient1->ingredient1_Grid_pos.y] = 3;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr1(Window::ingredient1->ingredient1_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient1->ingredient1_Grid_pos.y / static_cast<float>(grid_col) * height);
				
				for (int c = 0; c < grid_col; c++)
				{
					for (int r = 0; r < grid_row; r++)
					{
						std::cout << gGrids[r][c];
					}
					std::cout << std::endl;
				}
			}
			/*check ingr2*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 4)
			{
				Window::ingredient2->ingredient2_Grid_pos.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::ingredient2->ingredient2_Grid_pos.x][Window::ingredient2->ingredient2_Grid_pos.y] = 4;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();
				SceneManager::loadIngr2(Window::ingredient2->ingredient2_Grid_pos.x / static_cast<float>(grid_row) * width, Window::ingredient2->ingredient2_Grid_pos.y / static_cast<float>(grid_col) * height);
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
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 50)
			{
				SceneManager::destroyTrap();
				SceneManager::trap = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
				Window::trap->trap_Grid_pos.x = Window::player->player_grid_pos.x;
				Window::trap->trap_Grid_pos.y = Window::player->player_grid_pos.y - 1;
				Window::player->move_up();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 51;
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
				if (gGrids[r][c] == 50)
				{
					SceneManager::loadTrap(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawTrap();
				}
				if (gGrids[r][c] == 9)
				{
					SceneManager::loadGoal1(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::loadCover1(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawGoal1();
				}
				if (gGrids[r][c] == 10)
				{
					SceneManager::loadGoal2(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::loadCover1(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);

					SceneManager::drawGoal2();
				}
				if (gGrids[r][c] == 3)
				{
					SceneManager::loadIngr1(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawIngr1();
				}
				if (gGrids[r][c] == 4)
				{
					SceneManager::loadIngr2(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawIngr2();
				}
				
			}
		}
	}
	
}