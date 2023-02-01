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

namespace Core
{
	int Map::grid_row = 0;
	int Map::grid_col = 0;

	//int Map::gGrids[GRID_ROW][GRID_COL];
	int width, height;
	unsigned int SceneManager::amt_of_win_conditions;

	Map::Map()
	{
	}

	Map::~Map()
	{
		//this does deleting of textures
		/*SceneManager::destroyTile();
		SceneManager::destroyGoal1();
		SceneManager::destroyGoal2();
		SceneManager::destroyCover1();
		SceneManager::destroyIngr();
		SceneManager::destroyIngr();*/
	}

	int** Map::gGrids;

	void Map::initMap(std::string Filename)
	{
		//Open File using ifstream
		std::ifstream fin(Filename);
		if (!fin)
		{
			std::cout << "Unable to open tilemap file!";
			return;
		}
		/*store the row and col of the tile*/
		fin >> grid_row;
		fin >> grid_col;

		gGrids = new int* [grid_row];

		for (int i = 0; i < grid_row; i++)
		{
			gGrids[i] = new int[grid_col];
		}

		char ch;

		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				fin >> ch;
				gGrids[r][c] = ch;
			}
		}

		print_map_to_console();

		fin.close();
	}

	void Map::ResetMap()
	{
		for (int i = 0; i < grid_row; i++)
		{
			for (int j = 0; j < grid_col; j++)
			{
				gGrids[i][j] = 0;
			}
		}

		/*SceneManager::destroyTile();
		SceneManager::destroyIngr();*/
	}

	int Map::LoadMap()
	{
		glfwGetWindowSize(Window::window_ptr, &width, &height);
		
		tile_width = width / grid_row;
		tile_height = height / grid_col;
		
		/*Testing whether is loaded correctly*/
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				//print_map_to_console();
				/*Load texture depending on the grid*/
				if (gGrids[r][c] == static_cast<char>(grid_number::player))
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

				if(gGrids[r][c] == static_cast<char>(grid_number::rice))
				{
					Sprite* rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				if(gGrids[r][c] == static_cast<char>(grid_number::nori))
				{
					Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::nori, std::move(nori));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				if(gGrids[r][c] == static_cast<char>(grid_number::inari))
				{
					Sprite* inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::inari, inari);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				if (gGrids[r][c] == static_cast<char>(grid_number::box1))
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::box1, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c ));
					SceneManager::amt_of_win_conditions++;
				}

				if (gGrids[r][c] == static_cast<char>(grid_number::box2))
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::box2, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
				}

				if (gGrids[r][c] == static_cast<char>(grid_number::boxcover))
				{
					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				if (gGrids[r][c] == static_cast<char>(grid_number::sinkhole))
				{
					Sprite* sinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, sinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				if (gGrids[r][c] == static_cast<char>(grid_number::filledsinkhole))
				{
					Sprite* filledsinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, filledsinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
				}

				//buttload of walls
				if (gGrids[r][c] == static_cast<char>(wall_type::bottomleftwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::bottomrightwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomrightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::bottomwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall8.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middlebottomlefttopwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlebottomlefttopwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middleleftbottomrightwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftbottomrightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middleleftwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middlelefttoprightwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middlerightwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlerightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middletopbottomwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middletopbottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middletoprightbottomwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middletoprightbottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::middlewall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlewall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::topleftwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::topleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}

				if (gGrids[r][c] == static_cast<char>(wall_type::toprightwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::toprightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
				}
				
			}
			std::cout << std::endl;
		}

		return 1;
	}

	bool Map::isWin()
	{
		int win_check{ 0 };

		for (auto check : SceneManager::win_condition)
		{
			if (gGrids[check.first][check.second] == static_cast<int>(grid_number::win))
			{
				win_check++;
			}

			if (win_check == SceneManager::amt_of_win_conditions)
			{
				SceneManager::win_condition.clear();

				win_check = 0;
				
				return true;
			}
		}

		return false;
	}


	bool Map::isStuck()
	{
		// if player's grid index is 50, means its STUCK or put all ingr into goals
		if(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole) &&
			!isWin())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Map::collision_check_left()
	{
		grid_number check{};
		
		//Store what kind of ingredient is player pushing
		if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
		{
			check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
		}
		
		if(!isStuck())
		{
			/*check right neighbour, (wall)(ingredient)(player)*/
			if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items) &&
				gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first)&&
				gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
			{
				std::cout << "Wall on left" << std::endl;
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) ||
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
			{
				std::cout << "Wall on left" << std::endl;
				Window::player->stop();
			}
			/*check with covered box*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
			{
				Window::player->stop();
			}

			/*check ingredient*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(check))
			{
				/*check for ingredient & box*/
				if ((SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.x + 1 &&
					SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.y) ||
					(SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.x + 1 &&
						SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.y))
				{
					SceneManager::ingredientcontainer[check]->transformation.Position.x--;
					Window::player->player_grid_pos.x--;
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					Window::player->move_left();

					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::win);
					SceneManager::win_condition.push_back({ Window::player->player_grid_pos.x, Window::player->player_grid_pos.y });

					std::cout << "win = 1" << std::endl;
					Window::questProgress += 1;
					std::cout << "progress is " << Window::questProgress << std::endl;

					SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.x = SceneManager::ingredientcontainer[check]->transformation.Position.x;
					SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.y = SceneManager::ingredientcontainer[check]->transformation.Position.y;
					
					print_map_to_console();
				}
				
				SceneManager::ingredientcontainer[check]->transformation.Position.x--;
				Window::player->player_grid_pos.x--;
				gGrids[static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.x)][static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.y)]
					= static_cast<int>(check);

				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				Window::player->move_left();

				print_map_to_console();
			}
			
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
			{
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.x = Window::player->player_grid_pos.x - 1;
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.y = Window::player->player_grid_pos.y;

				Window::player->move_left();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);

				print_map_to_console();
			}
			else
			{
				Window::player->move_left();
				Window::player->player_grid_pos.x--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = 0;
				print_map_to_console();
			}
		}
	}
	void Map::collision_check_right()
	{
		grid_number check{};

		//Store what kind of ingredient is player pushing
		if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
		{
			check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
		}
		
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) ||
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items) &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
			{
				std::cout << "Wall on riight" << std::endl;
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
			{
				std::cout << "Wall on right" << std::endl;
				Window::player->stop();
			}
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 3 &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == 4 ||
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == 4 &&
				gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == 3)
			{
				Window::player->stop();
			}

			/*check with pod 1/2*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
			{
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if ((SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.x - 1 &&
				SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.y) ||
				(SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.x - 1 &&
					SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.y))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.x++;
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				Window::player->move_right();

				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::win);
				SceneManager::win_condition.push_back({ Window::player->player_grid_pos.x, Window::player->player_grid_pos.y });

				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.x = SceneManager::ingredientcontainer[check]->transformation.Position.x;
				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.y = SceneManager::ingredientcontainer[check]->transformation.Position.y;

				print_map_to_console();
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(check))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.x++;
				Window::player->player_grid_pos.x++;
				gGrids[static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.x)][static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.y)] =
					static_cast<int>(check);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				Window::player->move_right();

				print_map_to_console();
			}

			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
			{
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.x = Window::player->player_grid_pos.x;
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.y = Window::player->player_grid_pos.y + 1;
				Window::player->move_right();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);

				print_map_to_console();
			}
			else
			{
				Window::player->move_right();
				Window::player->player_grid_pos.x++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = 0;
				print_map_to_console();

			}
		}
	}
	void Map::collision_check_down()
	{
		grid_number check{};

		//Store what kind of ingredient is player pushing
		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::items))
		{
			check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
		}
		
		if(isStuck() == 0)
		{
			/*check down neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(wall_type::first) ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::items) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(wall_type::last))
			{
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(wall_type::last))
			{
				Window::player->stop();
			}
			/*check with pod 1/2*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::boxcover))
			{
				Window::player->stop();
			}
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == 4 ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == 4 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == 3)
			{
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if ((SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.x &&
				SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.y - 1) ||
				(SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.x &&
					SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.y - 1))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.y++;
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				Window::player->move_down();

				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::win);
				SceneManager::win_condition.push_back({ Window::player->player_grid_pos.x, Window::player->player_grid_pos.y });

				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.x = SceneManager::ingredientcontainer[check]->transformation.Position.x;
				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.y = SceneManager::ingredientcontainer[check]->transformation.Position.y;

				print_map_to_console();
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(check))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.y++;
				Window::player->player_grid_pos.y++;
				gGrids[static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.x)][static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.y)] =
					static_cast<int>(check);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::space);
				Window::player->move_down();

				print_map_to_console();
			}
			
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::sinkhole))
			{
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.x = Window::player->player_grid_pos.x;
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.y = Window::player->player_grid_pos.y + 1;
				Window::player->move_down();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);

				print_map_to_console();
			}
			else
			{
				Window::player->move_down();
				Window::player->player_grid_pos.y++;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = 0;
				print_map_to_console();

			}
		}
	}
	
	void Map::collision_check_up()
	{
		grid_number check{};

		//Store what kind of ingredient is player pushing
		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::items))
		{
			check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
		}
		
		if(isStuck() == 0)
		{
			/*check right neighbour, (wall)(ingredient1/2)(player)*/
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] >= static_cast<int>(wall_type::first) ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::items) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(wall_type::last))
			{
				Window::player->stop();
			}
			/*check wall*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(wall_type::last))
			{
				Window::player->stop();
			}
			/*check with pod 1/2*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::boxcover))
			{
				Window::player->stop();
			}
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 3 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 4 ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == 4 &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == 3)
			{
				Window::player->stop();
			}
			/*check for ingredient1 & pod 1*/
			else if ((SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.x &&
				SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box1]->transformation.Position.y + 1) ||
				(SceneManager::ingredientcontainer[check]->transformation.Position.x == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.x &&
					SceneManager::ingredientcontainer[check]->transformation.Position.y == SceneManager::ingredientcontainer[grid_number::box2]->transformation.Position.y + 1))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.y--;
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::space);
				Window::player->move_up();

				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::win);
				SceneManager::win_condition.push_back({ Window::player->player_grid_pos.x, Window::player->player_grid_pos.y });

				std::cout << "win = 1" << std::endl;
				Window::questProgress += 1;
				std::cout << "progress is " << Window::questProgress << std::endl;

				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.x = SceneManager::ingredientcontainer[check]->transformation.Position.x;
				SceneManager::ingredientcontainer[grid_number::boxcover]->transformation.Position.y = SceneManager::ingredientcontainer[check]->transformation.Position.y;

				print_map_to_console();
			}

			/*check ingr1*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(check))
			{
				SceneManager::ingredientcontainer[check]->transformation.Position.y--;
				Window::player->player_grid_pos.y--;
				gGrids[static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.x)][static_cast<int>(SceneManager::ingredientcontainer[check]->transformation.Position.y)] =
					static_cast<int>(check);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				Window::player->move_up();

				print_map_to_console();
			}
			
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::sinkhole))
			{
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.x = Window::player->player_grid_pos.x;
				SceneManager::ingredientcontainer[grid_number::sinkhole]->transformation.Position.y = Window::player->player_grid_pos.y - 1;
				Window::player->move_up();
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 51;
				print_map_to_console();
			}
			else
			{
				Window::player->move_up();
				Window::player->player_grid_pos.y--;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = 2;
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = 0;
				print_map_to_console();

			}
		}
	}

	void Map::print_map_to_console()
	{
		std::cout << "**************************** MAP LAYOUT ************************************" << std::endl;

		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				std::cout << std::setw(4) << gGrids[r][c] << std::setw(4);

			}
			std::cout << std::endl;
		}
		std::cout << "****************************************************************************" << std::endl;
	}

	void Map::DrawMap()
	{
		SceneManager::drawTile();
		SceneManager::drawIngr();
		
		/*for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				if (gGrids[r][c] == static_cast<char>(wall_type::bottomleftwall))
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_3.jpg");
					
					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, tile);
					SceneManager::drawTile();
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
				if (gGrids[r][c] == 50)
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_2.jpg");

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, tile);
					SceneManager::drawGoal();
				}
				if (gGrids[r][c] == static_cast<char>(wall_type::middletopbottomwall))
				{
					SceneManager::loadGoal1(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawGoal1();
				}
				if (gGrids[r][c] == static_cast<char>(wall_type::middletoprightbottomwall))
				{
					SceneManager::loadGoal2(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					SceneManager::drawGoal2();
				}
			}
		}*/
	}
}