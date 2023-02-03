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

		SceneManager::destroyTile();
		SceneManager::destroyIngr();
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
				switch (gGrids[r][c])
				{
				case static_cast<int>(grid_number::player):
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
					break;
				}
					

				case static_cast<int>(grid_number::rice):
				{
					Sprite* rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					
					break;
				}
					

				case static_cast<int>(grid_number::nori):
				{
					Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::nori, std::move(nori));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
				case static_cast<int>(grid_number::inari):
				{
					Sprite* inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::inari, inari);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					

				case static_cast<int>(grid_number::box1):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::box1, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;

				}
					

				case static_cast<int>(grid_number::box2):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::box2, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
					

				case static_cast<int>(grid_number::boxcover):
				{
					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}

				case static_cast<int>(grid_number::sinkhole):
				{
					Sprite* sinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, sinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					
				case static_cast<int>(grid_number::filledsinkhole):
				{
					Sprite* filledsinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, filledsinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}

				//Temporary placeholder for food in sinkhole
				case static_cast<int>(grid_number::temp):
				{
					Sprite* foodinsinkhole = new Sprite("../textures/doge.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::temp, foodinsinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					
				case static_cast<int>(wall_type::bottomleftwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					
				case static_cast<int>(wall_type::bottomrightwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomrightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::bottomwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall8.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::bottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middlebottomlefttopwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlebottomlefttopwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middleleftbottomrightwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftbottomrightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middleleftwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middlelefttoprightwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middleleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					
					
				case static_cast<int>(wall_type::middlerightwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlerightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middletopbottomwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middletopbottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

				case static_cast<int>(wall_type::middletoprightbottomwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middletoprightbottomwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					
				//most common wall
				case static_cast<int>(wall_type::middlewall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::middlewall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;

				}
					

				case static_cast<int>(wall_type::topleftwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::topleftwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}
					

					
				case static_cast<int>(wall_type::toprightwall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::toprightwall, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}

				default:
					assert("Texture type not found\n");
					break;
				}
			}
		}

		std::cout << "ingredientcontainer contains:" << std::endl;
		for (auto& x : SceneManager::ingredientcontainer)
		{
			std::cout << static_cast<char>(x.first) << ": " << x.second << std::endl;
		}

		print_map_to_console();

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
		//Check if left tile is a wall or ingredient
		if ((gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items)) ||
			(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) &&
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last)))
		{
			if (!isStuck())
			{
				//check if left tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
				{
					std::cout << "left ingredient\n";
					
					//check if tile on the left of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
					{
						std::cout << "left ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the left of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
					{
						//Set grid
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::temp); // Food stuck in sinkhole
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);


						std::cout << "left ingredient sinkhole\n";
						Window::player->move_left();
					}
					//check if tile on the left of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
					{
						std::cout << "left ingredient ingredient\n";
						Window::player->stop();
					}
					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::box1) ||
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::box2))
					{
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

						std::cout << "left ingredient box\n";
						Window::player->move_left();
					}
					//Otherwise, it is a space
					else
					{
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y];
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						
						std::cout << "left ingredient space\n";
						Window::player->move_left();
					}
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
					std::cout << "Cover on left\n";
					Window::player->stop();
				}
				/*check for sinkhole*/
				else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
				{
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					
					std::cout << "left sinkhole\n";
					Window::player->move_left();
				}
			}
			else
			{
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "normal left" << std::endl;
				Window::player->move_left();
			}
		}
		//Just move
		else
		{
			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

			std::cout << "normal left" << std::endl;
			Window::player->move_left();
		}
	}

	void Map::collision_check_right()
	{		
		//Check if right tile is a wall or ingredient
		if ((gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items)) ||
			(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last)))
		{
			if (!isStuck())
			{
				//check if right tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
				{
					std::cout << "right ingredient\n";

					//check if tile on the right of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
					{
						std::cout << "right ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the right of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
					{
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::temp); // Food stuck in sinkhole
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

						std::cout << "right ingredient sinkhole\n";
						Window::player->move_right();
					}
					//check if tile on the right of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::items))
					{
						std::cout << "right ingredient ingredient\n";
						Window::player->stop();
					}
					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::box1) ||
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::box2))
					{
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

						std::cout << "right ingredient box\n";
						Window::player->move_right();
					}
					//Otherwise, it is a space
					else
					{
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y];
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

						std::cout << "right ingredient space\n";
						Window::player->move_right();
					}
				}
				/*check wall*/
				else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::first) ||
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::last))
				{
					std::cout << "Wall on right" << std::endl;
					Window::player->stop();
				}
				/*check with covered box*/
				else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
				{
					std::cout << "Cover on right\n";
					Window::player->stop();
				}
				/*check for sinkhole*/
				else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
				{
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

					std::cout << "right sinkhole\n";
					Window::player->move_right();
				}
			}
		}
		//Just move
		else
		{
			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

			std::cout << "normal right" << std::endl;
			Window::player->move_right();
		}
	}
	void Map::collision_check_down()
	{
		//if the player is not stuck
		if (isStuck() == 0)
		{
			//check (x, y-1)
			//Step 1: if player is colliding w ingredient or wall 
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::items) ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(wall_type::last))
			{
				//Step 1A: if it is a wall
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(wall_type::last))
				{
					//do nothing
					Window::player->stop();

				}
				//Step 1B: it is an ingredient, store its value then  go to step 2 to check (x, y-2)
				else
				{
					//Store what kind of ingredient is player pushing
					grid_number check{};
					check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
					//Step 2A: if it is a wall
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(wall_type::last))
					{
						//do nothing
						std::cout << "wall detected down of player" << std::endl;
						Window::player->stop();
					}
					//Step 2B: if it is an empty space
					else
					{


						//step 3: check if (x,y+2) is a (A) blank space or (B) box plate or (C) sinkhole
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(grid_number::space))
						{
							//set (x,y+2) to ingredient
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(check);
							//set (x,y+1) to player
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);
							//set (x,y) to blank
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
							//move the player forward
							Window::player->move_down();
							Window::player->player_grid_pos.y++;
							//move ingredient forward 
							//iterate through vector and find ingredient
							//auto iter = std::find(SceneManager::ingredientcontainer.begin(), SceneManager::ingredientcontainer.end(), check);

							/*if (iter != SceneManager::ingredientcontainer.end())
							{
								i
							}*/
						}
					}
				}
			}
			else //it is a blank space or a sinkhole to check w the player
			{
				//if it is a sinkhole
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::sinkhole))
				{
					//player moves anyway
					std::cout << "player stepped in sinkhole!" << std::endl;
					//set (x,y+1) to player in sinkhole
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::filledsinkhole);
					//set (x,y) to blank
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					//move the player forward
					Window::player->move_down();
					Window::player->player_grid_pos.y++;

					//is it a sinkhole
				}
				else //it is a blank space
				{
					//set (x,y+1) to player
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);
					//set (x,y) to blank
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					//move the player forward
					Window::player->move_down();
					Window::player->player_grid_pos.y++;

				}

			}
		}

		
	}
	
	void Map::collision_check_up()
	{
		//if the player is not stuck
		if (isStuck() == 0)
		{
			//check (x, y-1)
			//Step 1: if player is colliding w ingredient or wall 
			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::items) ||
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(wall_type::first) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(wall_type::last))
			{
				//Step 1A: if it is a wall
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(wall_type::last))
				{
					//do nothing
					Window::player->stop();

				}
				//Step 1B: it is an ingredient, store its value then  go to step 2 to check (x, y-2)
				else
				{
					//Store what kind of ingredient is player pushing
					grid_number check{};
					check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
					//Step 2A: if it is a wall
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] >= static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(wall_type::last))
					{
						//do nothing
						std::cout << "wall detected up of player" << std::endl;
						Window::player->stop();
					}
					//Step 2B: if it is an empty space
					else
					{
						

						//step 3: check if (x,y-2) is a (A) blank space or (B) box plate or (C) sinkhole
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(grid_number::space))
						{
							std::cout << "pushing ingredient in front" << std::endl;
							Window::player->player_grid_pos.y--;
							auto& yMinusTwoCell = gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2];
							//set (x,y-1) to player
							auto& yMinusOneCell = gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1];
							//set (x,y) to blank
							auto& yCell = gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y];

							//set (x,y-2) to ingredient
							yMinusTwoCell = static_cast<int>(check);
							//set (x,y-1) to player
							yMinusOneCell = static_cast<int>(grid_number::player);
							//set (x,y) to blank
							yCell = static_cast<int>(grid_number::space);
							//move the player forward
							Window::player->move_up();
							
							//move ingredient forward 
							//iterate through vector and find ingredient
							//auto iter = std::find(SceneManager::ingredientcontainer.begin(), SceneManager::ingredientcontainer.end(), check);
							/*for (auto& ingredient : SceneManager::ingredientcontainer)
							{
								if (ingredient.first == check)
								{
									ingredient.second->transformation.Position.y + 500;

								}
							}*/
							
						}
					}
				}
			}
			else //it is a blank space or a sinkhole to check w the player
			{
				//if it is a sinkhole
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::sinkhole))
				{
					//player moves anyway
					std::cout << "player stepped in sinkhole!" << std::endl;
					//set (x,y-1) to player in sinkhole
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::filledsinkhole);
					//set (x,y) to blank
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					//move the player forward
					Window::player->move_up();
					Window::player->player_grid_pos.y--;

					//is it a sinkhole
				}
				else //it is a blank space
				{
					//set (x,y-1) to player
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);
					//set (x,y) to blank
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					//move the player forward
					Window::player->move_up();
					Window::player->player_grid_pos.y--;

				}
				
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
				std::cout << std::setw(4) << static_cast<char>(gGrids[r][c]) << std::setw(4);
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