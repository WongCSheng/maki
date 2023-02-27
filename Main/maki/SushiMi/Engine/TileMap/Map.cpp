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

	//int Map::gGrids[GRID_ROW][GRID_COL];
    static inline int width, height;
	unsigned int SceneManager::amt_of_win_conditions, win_amt;
	std::vector<std::pair<grid_number, wall_type>> levelWinConditions;
	int Map::CorrectCombination{}; //redeclaration

	int** Map::gGrids;

	wall_type ex_box;

	Sprite* soya;
	Sprite* rice;
	Sprite* salmon;
	Sprite* wasabi;
	Sprite* tea;

	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < grid_row; i++)
		{
			delete gGrids[i];
		}
		delete gGrids;

		SceneManager::destroyTile();
		SceneManager::destroyIngr();
		SceneManager::destroyInsideSinkHole();
	}

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

	void Map::saveEditedMap(std::string Filename)
	{
		std::ofstream fout(Filename);
		fout << grid_row << " " << grid_col << std::endl;

		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				fout << static_cast<char>(gGrids[r][c]) << " ";
			}
			fout << std::endl;
		}
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
		SceneManager::destroyInsideSinkHole();

		if (Window::timetodeletegrid)
		{
			for (int i = 0; i < grid_row; i++)
			{
				delete gGrids[i];
			}
			delete gGrids;
		}

		win_amt = 0;
		SceneManager::amt_of_win_conditions = 0;
	}


	int Map::LoadMap()
	{
		glfwGetWindowSize(Window::window_ptr, &width, &height);
		
		tile_width = static_cast<float>(width / grid_row);
		tile_height = static_cast<float>(height / grid_col);
		SceneManager::setTileDimension(static_cast<unsigned int>(tile_width), static_cast<unsigned int>(tile_height));
	
		CorrectCombination = 0;

		/*Testing whether is loaded correctly*/
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				int grid_to_coord_x = static_cast<int>(r / static_cast<float>(grid_row) * width);
				int grid_to_coord_y = static_cast<int>(c / static_cast<float>(grid_col) * height);
				switch (gGrids[r][c])
				{
				case static_cast<int>(grid_number::player):
				{
					Window::player->playerpos.x = static_cast<float>(grid_to_coord_x);
					Window::player->playerpos.y = static_cast<float>(grid_to_coord_y);
					Window::player->playerpos_restart.x = static_cast<int>(Window::player->playerpos.x);
					Window::player->playerpos_restart.y = static_cast<int>(Window::player->playerpos.y);
//#ifndef EDITOR
					Window::player->sp->transformation.Position.x = r / static_cast<float>(grid_row) * width;
					Window::player->sp->transformation.Position.y = c / static_cast<float>(grid_col) * height;
//#endif
					/*save player index in grid*/
					Window::player->player_grid_pos.x = r;
					Window::player->player_grid_pos.y = c;
					/*save initial index for restart purposes*/
					Window::player->player_initial_grid_pos.x = r;
					Window::player->player_initial_grid_pos.y = c;
					break;
				}
					
				// Ingredients are: avocado, cucumber,corn,inari,octopus,rice,roes,salmon,tamago,tofu,tuna,nori,soya,wasabi,		

				
				case static_cast<int>(grid_number::avocado):
				{
					Sprite* avocado = new Sprite("../textures/Tiles/Ingredients/Ingredients0_avocado.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::avocado, avocado);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				case static_cast<int>(grid_number::cucumber):
				{
					Sprite* cucumber = new Sprite("../textures/Tiles/Ingredients/Ingredients0_cucumber.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::cucumber, cucumber);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				case static_cast<int>(grid_number::corn):
				{
					Sprite* corn = new Sprite("../textures/Tiles/Ingredients/Ingredients0_ew_corn.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::corn, corn);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}

				case static_cast<int>(grid_number::inari):
				{
					Sprite* inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::inari, inari);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				case static_cast<int>(grid_number::octopus):
				{
					Sprite* octopus = new Sprite("../textures/Tiles/Ingredients/Ingredients0_octopus.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::octopus, octopus);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				case static_cast<int>(grid_number::rice):
				{
					/*Soya if you want to test out the animation
					Sprite* rice = new Sprite("../textures/spritesheet/soyaspritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));
					rice->Add_animation("../textures/spritesheet/soya.txt");
					rice->curr_anim = Idle;
					*/

					rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, rice);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;

					//old rice
					/*Sprite* rice = new Sprite("../textures/spritesheet/ricespritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, std::move(rice));
					rice->Add_animation("../textures/spritesheet/Run.txt");
					rice->curr_anim = Idle;
					rice->isSpriteSheet = 1;
					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);*/
					break;
				}
				//roes
				case static_cast<int>(grid_number::roes):
				{
					Sprite* roes = new Sprite("../textures/Tiles/Ingredients/Ingredients0_roes.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::roes, roes);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//salmon
				case static_cast<int>(grid_number::salmon):
				{
					salmon = new Sprite("../textures/spritesheet/salmonspritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::salmon, salmon);
					salmon->status = 1;
					salmon->isSpriteSheet = 1;
					/*add salmon sprites*/
					salmon->Add_animation("../textures/spritesheet/salmon_normal.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_soy.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_wasabi.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_both.txt");
					salmon->curr_anim = AnimationType::Idle;
					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//tamago
				case static_cast<int>(grid_number::tamago):
				{
					Sprite* tamago = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tamago.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tamago, tamago);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//tofu
				case static_cast<int>(grid_number::tofu):
				{
					Sprite* tofu = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tofu.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tofu, tofu);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//tuna
				case static_cast<int>(grid_number::tuna):
				{
					Sprite* tuna = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tuna, tuna);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//nori
				case static_cast<int>(grid_number::nori):
				{
					Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::nori, std::move(nori));

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				//soya
				case static_cast<int>(grid_number::soya):
				{

					soya = new Sprite("../textures/spritesheet/soyaspritesheet.png");
					soya->isSpriteSheet = 1;
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::soya, soya);
					//animate soy sauce
					soya->Add_animation("../textures/spritesheet/soya_Idle.txt");
					soya->Add_animation("../textures/spritesheet/soya_Pour.txt");
					soya->curr_anim = AnimationType::Idle;
					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					
					break;
				}
				//wasabi
				case static_cast<int>(grid_number::wasabi):
				{
					wasabi = new Sprite("../textures/spritesheet/wasabispritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::wasabi, wasabi);
					//animate soy sauce
					wasabi->isSpriteSheet = 1;
					wasabi->Add_animation("../textures/spritesheet/wasabi_Idle.txt");
					wasabi->Add_animation("../textures/spritesheet/wasabi_Pour.txt");
					wasabi->curr_anim = AnimationType::Idle;
					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					SceneManager::loadIngr_initPos(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;
				}
				// Ingredients that have boxes are: avocado, cucumber,corn,inari,octopus,rice,roes,salmon,tamago,tofu,tuna,nori	
				case static_cast<int>(wall_type::avocado_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Avocado.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::avocado_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					levelWinConditions.push_back(std::pair(grid_number::avocado, wall_type::avocado_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//cucumber
				case static_cast<int>(wall_type::cucumber_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Cucumber.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::cucumber_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::cucumber, wall_type::cucumber_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//corn
				case static_cast<int>(wall_type::corn_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Corn.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::corn_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::corn, wall_type::corn_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//octopus
				case static_cast<int>(wall_type::octopus_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Octopus.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::octopus_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::octopus, wall_type::octopus_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//roes
				case static_cast<int>(wall_type::roes_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Roes.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::roes_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::roes, wall_type::roes_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//salmon
				case static_cast<int>(wall_type::salmon_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Salmon.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::salmon_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::salmon , wall_type::salmon_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//tamago
				case static_cast<int>(wall_type::tamago_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tamago.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tamago_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::tamago, wall_type::tamago_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//tofu
				case static_cast<int>(wall_type::tofu_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tofu.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tofu_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::tofu, wall_type::tofu_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//tuna
				case static_cast<int>(wall_type::tuna_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tuna.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tuna_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::tuna, wall_type::tuna_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
				//tea
				case static_cast<int>(wall_type::tea):
				{
					tea = new Sprite("../textures/spritesheet/teaspritesheet.png");
					tea->isSpriteSheet = 1;
					tea->Add_animation("../textures/spritesheet/tea_Idle.txt");
					tea->Add_animation("../textures/spritesheet/tea_Pour.txt");
					tea->curr_anim = AnimationType::Idle;
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tea, tea);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					break;
				}
				//nori
				case static_cast<int>(wall_type::nori_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Nori.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::nori_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::nori, wall_type::nori_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}

				case static_cast<int>(wall_type::rice_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::rice_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::rice, wall_type::rice_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;

				}
					

				case static_cast<int>(wall_type::inari_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Inari.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::inari_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.push_back(std::pair(grid_number::inari, wall_type::inari_box));

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}

				case static_cast<int>(grid_number::boxcover):
				{
					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					break;
				}

				case static_cast<int>(wall_type::sinkhole):
				{
					Sprite* sinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::sinkhole, sinkhole);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					break;
				}
					
				case static_cast<int>(wall_type::filledsinkhole):
				{
					Sprite* filledsinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::filledsinkhole, filledsinkhole);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					break;
				}
				case static_cast<int>(grid_number::ground0):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_0.jpg");

					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground0, tile);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					break;
				}
				case static_cast<int>(grid_number::ground1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_1.jpg");

					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground1, tile);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					break;
				}
				case static_cast<int>(grid_number::ground2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_2.jpg");

					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::ground2, tile);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					break;
				}
				//sinkhole_gunkan
				case static_cast<int>(wall_type::sinkhole_gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Sinkhole.png");

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::sinkhole_gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					break;
				}
				case static_cast<int>(wall_type::Wall0):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall0_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					


				case static_cast<int>(wall_type::Wall2_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					

				case static_cast<int>(wall_type::Wall2_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall2_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					
				case static_cast<int>(wall_type::Wall3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall3_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_1, tile);
					//tile->Add_animation()
					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall3_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_2, tile);
					//tile->Add_animation()
					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}


				case static_cast<int>(wall_type::Wall3_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					
				case static_cast<int>(wall_type::Wall4_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall4_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall4_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall4_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					

					
				case static_cast<int>(wall_type::Wall5):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
					
					
				//most common wall
				case static_cast<int>(wall_type::Wall5_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}
					
				case static_cast<int>(wall_type::Wall5_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall5_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}
				
				case static_cast<int>(wall_type::Wall5_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}
				case static_cast<int>(wall_type::Wall6):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall6_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall6_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall6_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall6_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}
				//wall 7
				case static_cast<int>(wall_type::Wall7):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall7_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall7_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall7_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}

				case static_cast<int>(wall_type::Wall7_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;

				}
				//wall 8
				case static_cast<int>(wall_type::Wall8):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall8.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall8, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//wall 9
				case static_cast<int>(wall_type::Wall9):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_1.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_2.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_3.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_4.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_5):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_5.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_5, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_6):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_6.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_6, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall9_7):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9_7.jpg");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9_7, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::WaterWall):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_FishingVillage/Fishing_Wall.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::WaterWall, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall0_Gunkan,		//j
				case static_cast<int>(wall_type::Wall0_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall0.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall1_Gunkan,		//k
				case static_cast<int>(wall_type::Wall1_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall1_1_Gunkan,		//l
				case static_cast<int>(wall_type::Wall1_1_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall1_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1_1_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall2_Gunkan,		//m
				case static_cast<int>(wall_type::Wall2_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall2.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall2_1_Gunkan,		//n
				case static_cast<int>(wall_type::Wall2_1_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall2_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2_1_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall3_Gunkan,		//o
				case static_cast<int>(wall_type::Wall3_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Wall3_1_Gunkan,		//p
				case static_cast<int>(wall_type::Wall3_1_Gunkan):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_GunkanVillage/Wall3_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_1_Gunkan, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				
				/*case static_cast<int>(wall_type::Water):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Wall_FishingVillage/Fishing_Wall.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Water, tile);

					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}*/
				//	Wall3_1_Gunkan,		//p
				case static_cast<int>(wall_type::WoodenPlatform):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_FishingVillage/Fishing_Ground.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::WoodenPlatform, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				default:
					assert("Texture type not found\n");
					break;
				}
			}

		}
		//scale the player according to map size
		Player::sp->transformation.Scale = glm::vec2(SceneManager::getTileWidth(), SceneManager::getTileHeight());


		print_map_to_console();

		return 1;
	}

	bool Map::isWin()
	{
		////checking through all loaded box for the current level
		//for (auto& box : SceneManager::tilecontainer)
		//{
		//	//checking through all loaded ingredient for the current level
		//	for (auto& ingredient : SceneManager::ingredientcontainer)
		//	{
		//		//convert coordinates back into row and column (dont know why need to plus 1)
		//		int ingredientRow = static_cast<int>(ingredient.second->transformation.Position.x * (static_cast<float>(grid_row) / width)) + 1;
		//		int ingredientCol = static_cast<int>(ingredient.second->transformation.Position.y * (static_cast<float>(grid_col) / height)) + 1;
		//		std::pair<int, int> ingredientCoordinates(ingredientRow, ingredientCol);

		//		int BoxRow = static_cast<int>(box.second->transformation.Position.x * (static_cast<float>(grid_row) / width) + 1);
		//		int BoxCol = static_cast<int>(box.second->transformation.Position.y * (static_cast<float>(grid_col) / height) + 1);
		//		std::pair<int, int> boxCoordinates(BoxRow, BoxCol);
		//		//checking through level win condition (check if ingredient land on box position)
		//		if (ingredientCoordinates == boxCoordinates)
		//		{
		//			//ingredient row and col matches box row and col
		//		    std::pair<grid_number, wall_type> checkCondition(ingredient.first, box.first);
		//			for (auto& y : levelWinConditions)//suggest to change to map
		//			{
		//				//check whether is correct ingredient to box
		//				if (checkCondition == y)
		//					std::cout << "correct ingredient on box\n";
		//			}
		//		}
		//	}
		//}
		return ((win_amt == SceneManager::amt_of_win_conditions) ? true : false);
	}


	bool Map::isStuck()
	{
		// if player's grid index is 50, means its STUCK or put all ingr into goals
		if((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole_gunkan)) &&
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
		if (!isStuck())
		{
			//Check if left tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items)) ||
				(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
			{
				//check if left tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items))
				{
					std::cout << "left ingredient\n";
					
					//check if tile on the left of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
					{
						std::cout << "left ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the left of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole_gunkan))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

						//Set grid
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::temp);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x -= tile_width;

								SceneManager::in_sinkhole.push_back(ingredient);
								SceneManager::ingredientcontainer.erase(SceneManager::ingredientcontainer.begin() + it);
								break;
							}
							it++;
						}

						std::cout << "left ingredient sinkhole\n";
						Window::player->move_left();
					}
					//check if tile on the left of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items))
					{
						std::cout << "left ingredient ingredient\n";
						Window::player->stop();
					}

					/*------------------------------Salmon and soya/Wasabi/Tea Checks HERE----------------------------------------------------------------------------------------*/
					//check if tile on the left of salmon is soya
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::soya) &&
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x -= tile_width;
								break;
							}
						}
						/*
						Sprite* rice_soy = new Sprite("../textures/Rice/RiceSoy.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::RiceSoy, rice_soy);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x) - (1 * static_cast<int>(tile_width) + 5), static_cast<int>(Window::player->playerpos.y),
							static_cast<int>(Window::player->playerpos.x) - 1, static_cast<int>(Window::player->playerpos.y), combine);
							*/
						soya->timer = 0;
						SceneManager::activateSoya(soya);

						/*change salmon sprite to with soya*/
						salmon->status = 1;
						salmon->curr_anim = AnimationType::Run;
						/*
						Sprite* rice_soy = new Sprite("../textures/Rice/RiceSoy.png");
						
						std::pair<Rice, Sprite*> combine = std::make_pair(Rice::riceSoya, rice_soy);
						SceneManager::loadRice(static_cast<int>(Window::player->playerpos.x) - (2 * static_cast<int>(tile_width) + 5), static_cast<int>(Window::player->playerpos.y),
							static_cast<int>(Window::player->playerpos.x) - 2, static_cast<int>(Window::player->playerpos.y), combine);
						*/
						Window::player->move_left();
						std::cout << "soya dripped\n";
					}

					//check if tile on left of salmon is Wasabi
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::wasabi) &&
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::wasabi);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x -= tile_width;
								break;
							}
						}
						wasabi->timer = 0;
						SceneManager::activateWasabi(wasabi);

						/*change salmon sprite to with wasabi*/
						salmon->status = 2;
						salmon->curr_anim = AnimationType::Jump;

						Window::player->move_left();
						std::cout << "Wasabi dripped\n";
					}

					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) &&
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);

						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x) - (2 * static_cast<int>(tile_width) + 5), static_cast<int>(Window::player->playerpos.y), 
							static_cast<int>(Window::player->playerpos.x) - 2, static_cast<int>(Window::player->playerpos.y), combine);

						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x -= tile_width + 5;
								break;
							}
						}

						win_amt++;

						std::cout << "left ingredient box\n";
						Window::player->move_left();
					}
					//check if it's a covered box
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
					{
						std::cout << "left ingredient box\n";
						Window::player->stop();
					}
					//Otherwise, it is a space
					else
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(check);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						
						//check if current grid is rice_box
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x -= tile_width;
								break;
							}
						}
						
						std::cout << "left ingredient space\n";
						Window::player->move_left();
					}
				}
				/*check wall*/
				else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
				{
					std::cout << "Wall on left" << std::endl;
					Window::player->stop();
				}
			}
			/*check with covered box*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
			{
				std::cout << "Cover on left\n";
				Window::player->stop();
			}
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole_gunkan))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "left sinkhole\n";
				Window::player->move_left();
			}
			else
			{
				//Check if left tile is box
				if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box)&& gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
					Window::player->move_left();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}
				//Check if current tile is insidebox
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_left();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
				}
				else
				{
					Window::player->move_left();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}

				std::cout << "normal left" << std::endl;
			}
		}
	}

	void Map::collision_check_right()
	{
		if (!isStuck())
		{
			//Check if right tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items)) ||
				(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
			{
				//check if right tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items))
				{
					std::cout << "right ingredient\n";

					//check if tile on the right of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
					{
						std::cout << "right ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the right of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole_gunkan))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

						//Set grid
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::temp);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x += tile_width;

								SceneManager::in_sinkhole.push_back(ingredient);
								SceneManager::ingredientcontainer.erase(SceneManager::ingredientcontainer.begin() + it);
								break;
							}
							it++;
						}

						std::cout << "right ingredient sinkhole\n";
						Window::player->move_right();
					}
					//check if tile on the right of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] < static_cast<int>(grid_number::items))
					{
						std::cout << "right ingredient ingredient\n";
						Window::player->stop();
					}

					//check if tile on the right of salmon is soya
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::soya) &&
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x += tile_width;
								break;
							}
						}
						soya->timer = 0;
						SceneManager::activateSoya(soya);

						/*change salmon sprite to with soya*/
						salmon->status = 1;
						salmon->curr_anim = AnimationType::Run;
						Window::player->move_right();
						std::cout << "soya dripped\n";
					}

					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) &&
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x) + (2 * static_cast<int>(tile_width)), static_cast<int>(Window::player->playerpos.y), static_cast<int>(Window::player->player_grid_pos.x) + 2, static_cast<int>(Window::player->player_grid_pos.y), combine);

						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x += tile_width;
								break;
							}
						}

						win_amt++;

						std::cout << "right ingredient box\n";
						Window::player->move_right();
					}
					//check if it's a covered box
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
					{
						std::cout << "right ingredient box\n";
						Window::player->stop();
					}
					//Otherwise, it is a space
					else
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(check);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						//check if current grid is box
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.x += tile_width;
								break;
							}
						}

						std::cout << "right ingredient space\n";
						Window::player->move_right();
					}
				}
				/*check wall*/
				else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
				{
					std::cout << "Wall on right" << std::endl;
					Window::player->stop();
				}
			}
			/*check with covered box*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::boxcover))
			{
				std::cout << "Cover on right\n";
				Window::player->stop();
			}
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::sinkhole_gunkan))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "right sinkhole\n";
				Window::player->move_right();
			}
			//Just move
			else
			{
				//Check if right tile is a box
				if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) && gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}
				//Check if current tile is insidebox
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
				}
				//Check if current tile is inbox2
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::inbox2))
				{
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::inari_box);
				}
				else
				{
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}

				std::cout << "normal right" << std::endl;
			}
		}
	}

	void Map::collision_check_down()
	{
		if (!isStuck())
		{
			//Check if below tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(grid_number::items)) ||
				(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last)))
			{
				//check if below tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(grid_number::items))
				{
					std::cout << "down ingredient\n";

					//check if tile below of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] > static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] < static_cast<int>(wall_type::last))
					{
						std::cout << "down ingredient wall\n";
						Window::player->stop();
					}
					//check if tile below of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(wall_type::sinkhole_gunkan))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(wall_type::temp);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y += tile_height;

								SceneManager::in_sinkhole.push_back(ingredient);
								SceneManager::ingredientcontainer.erase(SceneManager::ingredientcontainer.begin() + it);
								break;
							}
							it++;
						}

						std::cout << "down ingredient sinkhole\n";
						Window::player->move_down();
					}
					//check if tile below of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(grid_number::items))
					{
						std::cout << "down ingredient ingredient\n";
						Window::player->stop();
					}

					//check if tile on the bottom of salmon is soya
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(grid_number::soya) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y += tile_height;
								break;
							}
						}
						soya->timer = 0;
						SceneManager::activateSoya(soya);

						/*change salmon sprite to with soya*/
						salmon->status = 1;
						salmon->curr_anim = AnimationType::Run;
						Window::player->move_down();
						std::cout << "soya dripped\n";
					}

					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(wall_type::rice_box) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::boxcover);
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x), static_cast<int>(Window::player->playerpos.y) + (2 * static_cast<int>(tile_height)), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y + 2, combine);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y += tile_height;
								break;
							}
						}

						win_amt++;

						std::cout << "down ingredient box\n";
						Window::player->move_down();
					}
					//check if it's a covered box
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(grid_number::boxcover))
					{
						std::cout << "down ingredient box\n";
						Window::player->stop();
					}
					//Otherwise, it is a space
					else
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(check);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);

						//check if current grid is rice_box
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						////check if current grid is inari_box
						//else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::inbox2))
						//{
						//	gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::inari_box);
						//}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y += tile_height;
								break;
							}
						}

						std::cout << "down ingredient space\n";
						Window::player->move_down();
					}
				}
				/*check wall*/
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) ||
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last))
				{
					std::cout << "Wall on down" << std::endl;
					Window::player->stop();
				}
			}
			/*check with covered box*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::boxcover))
			{
				std::cout << "Cover on down\n";
				Window::player->stop();
			}
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(wall_type::sinkhole_gunkan))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "down sinkhole\n";
				Window::player->move_down();
			}
			//Just move
			else
			{
				//Check if up tile is a box
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(wall_type::rice_box) && gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
					Window::player->move_down();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::space);
				}
				//Check if current tile is insidebox
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_down();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ex_box);
				}
				else
				{
					Window::player->move_down();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::space);
				}

				std::cout << "normal down" << std::endl;
			}
		}
	}
	
	void Map::collision_check_up()
	{
		if (!isStuck())
		{
			//Check if above tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(grid_number::items)) ||
				(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last)))
			{
				//check if above tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(grid_number::items))
				{
					std::cout << "up ingredient\n";

					//check if tile above of ingredient is a wall
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] > static_cast<int>(wall_type::first) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] < static_cast<int>(wall_type::last))
					{
						std::cout << "up ingredient wall\n";
						Window::player->stop();
					}
					//check if tile above of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(wall_type::sinkhole_gunkan))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(wall_type::temp);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y -= tile_height;

								SceneManager::in_sinkhole.push_back(ingredient);
								SceneManager::ingredientcontainer.erase(SceneManager::ingredientcontainer.begin() + it);
								break;
							}
							it++;
						}

						std::cout << "up ingredient sinkhole\n";
						Window::player->move_up();
					}
					//check if tile above of ingredient is another food
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] > static_cast<int>(grid_number::ingredients) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] < static_cast<int>(grid_number::items))
					{
						std::cout << "up ingredient ingredient\n";
						Window::player->stop();
					}

					//check if tile on the top of salmon is soya
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(grid_number::soya) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y -= tile_height;
								break;
							}
						}
						soya->timer = 0;
						SceneManager::activateSoya(soya);

						/*change salmon sprite to with soya*/
						salmon->status = 1;
						salmon->curr_anim = AnimationType::Run;
						Window::player->move_up();
						std::cout << "soya dripped\n";
					}

					//check if it's a box
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] >= static_cast<int>(wall_type::rice_box) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::boxcover);
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x), static_cast<int>(Window::player->playerpos.y) - (2 * static_cast<int>(tile_height)), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y - 2, combine);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);

						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y -= tile_height;
								break;
							}
						}

						win_amt++;

						std::cout << "up ingredient box\n";
						Window::player->move_up();
					}
					//check if it's a covered box
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(grid_number::boxcover))
					{
						std::cout << "up ingredient box\n";
						Window::player->stop();
					}
					//Otherwise, it is a space
					else
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(check);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);

						//check if current grid is rice_box
						if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.first == check)
							{
								ingredient.second->transformation.Position.y -= tile_height;
								break;
							}
						}

						std::cout << "up ingredient space\n";
						Window::player->move_up();
					}
				}
				/*check wall*/
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) ||
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last))
				{
					std::cout << "Wall on up" << std::endl;
					Window::player->stop();
				}
			}
			/*check with covered box*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::boxcover))
			{
				std::cout << "Cover on up\n";
				Window::player->stop();
			}
			/*check for sinkhole*/
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(wall_type::sinkhole) || gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(wall_type::sinkhole_gunkan))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "up sinkhole\n";
				Window::player->move_up();
			}
			//Just move
			else
			{
				//Check if up tile is any box
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(wall_type::rice_box)&& gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(wall_type::tuna_box))
				{
					//save the value of the box stepped on
					ex_box = static_cast<wall_type>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
					
					Window::player->move_up();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::space);
				}
				//Check if current tile is insidebox
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_up();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ex_box);
				}
				else
				{
					Window::player->move_up();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::space);
				}

				std::cout << "normal up" << std::endl;
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

		std::cout << "Goals: " << SceneManager::amt_of_win_conditions << std::endl;
		std::cout << "Current goals: " << win_amt << std::endl;

		std::cout << "****************************************************************************" << std::endl;
	}

	void Map::DrawMap()
	{
		SceneManager::drawTile();
		SceneManager::drawInsideSinkHole();
		SceneManager::drawIngr();
		//SceneManager::drawRice();
	}
	/********************************************
	 Return the value inside a cell that you click
	********************************************/
	int Map::GetValue(int col_x, int row_y)
	{
		//if you are accessing out of the given grid
		if (col_x > grid_col -1 || row_y > grid_row -1)
		{
			return 0; //if you are pressing out of this grid, return 0 as tile value 
		}
		return gGrids[col_x][row_y];
	}
	/********************************************
	 Set the value inside a cell that you click
	********************************************/
	void Map::SetValue(int col_x, int row_y, int value)
	{
		gGrids[col_x][row_y] = value;
		//Window::loaded = false;
		//print_map_to_console(); //debugging
	}


	/**************************************************************
	 Helper function to convert enum in sceneManager.h to string
	**************************************************************/
	std::string Map::EnumToString(grid_number ingredient)
	{
		switch (ingredient)
		{
		case(grid_number::avocado):
			return ("Avocado");
			break;

		case(grid_number::corn):
			return ("Corn");
			break;

		case(grid_number::cucumber):
			return ("Cucumber");
			break;

		case(grid_number::inari):
			return ("Inari");
			break;

		case(grid_number::nori):
			return ("Nori");
			break;

		case(grid_number::octopus):
			return ("Octopus");
			break;

		case(grid_number::rice):
			return ("Rice");
			break;

		case(grid_number::roes):
			return ("Roes");
			break;

		case(grid_number::salmon):
			return ("Salmon");
			break;

		case(grid_number::tamago):
			return ("Tamago");
			break;

		case(grid_number::tofu):
			return ("Tofu");
			break;

		case(grid_number::tuna):
			return ("Tuna");
			break;

		case(grid_number::wasabi):
			return ("Wasabi");
			break;

		case(grid_number::soya):
			return ("Soya");
			break;
		case(static_cast<grid_number>(wall_type::tea)):
			return ("Tea");
			break;
		}
	}
}