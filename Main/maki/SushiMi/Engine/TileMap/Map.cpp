/*
File:		Map.cpp
@author		louishetong.wang@digipen.edu 40%
co-Author:  thea.sea@digipen.edu 15%
co-Author:  Aurelia (fei.x@digipen.edu) 15%
co-Author:  w.chongsheng@digipen.edu  20%

Description:
*/

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "../../src/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Headers/SceneManager.h"
#include <Engine/Font/Font.h>
#include "../Audio/AudioEngine.h"

namespace Core
{

	//int Map::gGrids[GRID_ROW][GRID_COL];
	static inline int width, height;
	unsigned int SceneManager::amt_of_win_conditions, win_amt;
	/*std::vector<std::pair<grid_number, wall_type>> levelWinConditions;*/
	int Map::CorrectCombination{}; //redeclaration

	int** Map::gGrids;
	int** Map::aGrids;
	int** Map::wGrids;
	int** Map::RestartGrids;

	wall_type ex_box;
	grid_number next_grid;
	grid_number curr_grid;

	std::map<std::string, Sprite*> Map::loadedIngredients;		//  all loaded ingredients for the level
	std::map< std::string, Sprite*> Map::loadedBoxes;			//	all loaded boxes for the level

	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < max_grid_cols_x; i++)
		{
			delete gGrids[i];
			delete aGrids[i];
			delete wGrids[i];
			delete RestartGrids[i];
		}
		delete gGrids;
		delete aGrids;
		delete wGrids;
		delete RestartGrids;

		SceneManager::destroyTile();
		SceneManager::destroyIngr();
		SceneManager::destroyInsideSinkHole();
		SceneManager::destroyTop();
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
		fin >> max_grid_cols_x;
		fin >> max_grid_rows_y;

		gGrids = new int* [max_grid_cols_x];
		aGrids = new int* [max_grid_cols_x];
		wGrids = new int* [max_grid_cols_x];
		RestartGrids = new int* [max_grid_cols_x];

		for (int i = 0; i < max_grid_cols_x; i++)
		{
			gGrids[i] = new int[max_grid_rows_y];
			aGrids[i] = new int[max_grid_rows_y];
			wGrids[i] = new int[max_grid_rows_y];
			RestartGrids[i] = new int[max_grid_rows_y];
		}

		char ch;

		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				fin >> ch;

				if (ch >= '!' && ch <= '8')
				{
					gGrids[r][c] = ch;
					RestartGrids[r][c] = ch;
				}
				else
				{
					aGrids[r][c] = ch;
				}
			}
		}

		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				fin >> ch;
				wGrids[r][c] = ch;
			}
		}

		fin.close();
	}

	void Map::saveEditedMap(std::string Filename)
	{
		std::ofstream fout(Filename);
		fout << max_grid_cols_x << " " << max_grid_rows_y << std::endl;

		//print out gGrids and aGrids 1st layer first
		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				if (static_cast<char>(gGrids[r][c]) >= '!' && static_cast<char>(gGrids[r][c]) <= '8')
				{
					fout << static_cast<char>(gGrids[r][c]) << " ";
				}
				else
				{
					fout << static_cast<char>(aGrids[r][c]) << " ";

				}
			}
			fout << std::endl;
		}

		/*for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				fout << static_cast<char>(aGrids[r][c]) << " ";
			}
			fout << std::endl;
		}*/
		fout << std::endl;

		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				fout << static_cast<char>(wGrids[r][c]) << " ";
			}
			fout << std::endl;
		}
	}

	void Map::ResetMap()
	{
		for (int i = 0; i < max_grid_cols_x; i++)
		{
			for (int j = 0; j < max_grid_rows_y; j++)
			{
				gGrids[i][j] = 0;
				aGrids[i][j] = 0;
				wGrids[i][j] = 0;
				RestartGrids[i][j] = 0;
			}
		}

		SceneManager::destroyTile();
		SceneManager::destroyIngr();
		SceneManager::destroyInsideSinkHole();
		SceneManager::destroyTop();

		for (int i = 0; i < max_grid_cols_x; i++)
		{
			delete gGrids[i];
			delete aGrids[i];
			delete wGrids[i];
			delete RestartGrids[i];
		}
		delete gGrids;
		delete aGrids;
		delete wGrids;
		delete RestartGrids;

		win_amt = 0;
		SceneManager::amt_of_win_conditions = 0;
	}

	void Map::RestartMap()
	{
		for (int i = 0; i < max_grid_cols_x; i++)
		{
			for (int j = 0; j < max_grid_rows_y; j++)
			{
				gGrids[i][j] = RestartGrids[i][j];
			}
		}

		std::vector<Basket>::iterator it = SceneManager::ingredientcontainer.begin();

		for (it; it != SceneManager::ingredientcontainer.end();)
		{
			it->Restart();

			if (it->nametag == grid_number::boxcover)
			{
				delete it->spr;
				it = SceneManager::ingredientcontainer.erase(it);
			}
			else
			{
				it++;
			}
		}

		it = SceneManager::in_sinkhole.begin();

		for (it; it != SceneManager::in_sinkhole.end();)
		{
			it->Restart();

			if (it->nametag != grid_number::sinkhole)
			{
				SceneManager::ingredientcontainer.push_back(*it);

				it = SceneManager::in_sinkhole.erase(it);
			}
			else
			{
				it++;
			}
		}

		Window::player->restart();
		SceneManager::FcurrentAlpha = 1.f;
		SceneManager::timer = 0.0f;
		win_amt = 0;
	}


	int Map::LoadMap()
	{
		glfwGetWindowSize(Window::window_ptr, &width, &height);
		windowDim = { width, height };
		tile_width = static_cast<float>(width / max_grid_cols_x);
		tile_height = static_cast<float>(height / max_grid_rows_y);
		SceneManager::setTileDimension(static_cast<unsigned int>(tile_width), static_cast<unsigned int>(tile_height));

		CorrectCombination = 0;
		levelWinConditions.clear();

		/*Testing whether is loaded correctly*/
		LoadAMap();
		LoadGMap();
		LoadWMap();
		//scale the player according to map size
		Player::sp->transformation.Scale = glm::vec2(SceneManager::getTileWidth(), SceneManager::getTileHeight());


		print_map_to_console();

		return 1;
	}

	void Map::LoadAMap()
	{
		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				int grid_to_coord_x = static_cast<int>(r / static_cast<float>(max_grid_cols_x) * width);
				int grid_to_coord_y = static_cast<int>(c / static_cast<float>(max_grid_rows_y) * height);
				switch (aGrids[r][c])
				{
					//RicePlant1
				case static_cast<int>(animated::RicePlant1):
				{
					Sprite* riceplant = new Sprite("../textures/spritesheet/AnimatedTop/RicePlant1.png");
					std::pair<animated, Sprite*> combine = std::make_pair(animated::RicePlant1, std::move(riceplant));
					riceplant->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					riceplant->curr_anim = AnimationType::Idle;
					riceplant->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine);
					break;

				}
				//RicePlant2
				case static_cast<int>(animated::RicePlant2):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RicePlant2.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RicePlant2, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//RicePlant3
				case static_cast<int>(animated::RicePlant3):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RicePlant3.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RicePlant3, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;
				}
				//RicePlant4
				case static_cast<int>(animated::RicePlant4):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RicePlant4.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RicePlant4, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;
				}
				//RicePlant5
				case static_cast<int>(animated::RicePlant5):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RicePlant5.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RicePlant5, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;
				}
				//RiceWater1
				case static_cast<int>(animated::RiceWater1):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RiceWater1.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RiceWater1, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/RiceWater.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;
				}
				//RiceWater2
				case static_cast<int>(animated::RiceWater2):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/RiceWater2.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RiceWater2, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/RiceWater.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;
				}
				/*RicePlant3,RicePlant4,RicePlant5,	RiceWater1,	RiceWater2,GunkanSign_Right,GunkanSign_Left,GunkanCorn,GunkanCarrot,,GunkanCrow_Right,FishingBoat,FishingLog,	FishingSotong,FishingNoot,FishingCrab,*/
				//GunkanSign_Right
				case static_cast<int>(animated::GunkanSign_Right):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/GunkanSign_Right.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::GunkanSign_Right, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//GunkanCrow_Left
				case static_cast<int>(animated::GunkanCrow_Left):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/GunkanCrow_Left.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::GunkanCrow_Left, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//GunkanCorn
				case static_cast<int>(animated::GunkanCorn):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/GunkanCorn.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::GunkanCorn, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//GunkanCarrot
				case static_cast<int>(animated::GunkanCarrot):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/GunkanCarrot.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::GunkanCarrot, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//RicePlain_TopG2_1
				case static_cast<int>(animated::RicePlain_TopG2_1):
				{
					Sprite* rice1 = new Sprite("../textures/Tiles/Top/RicePlain_TopG2_1.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::RicePlain_TopG2_1, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//FishingBoat
				case static_cast<int>(animated::FishingBoat):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/FishingBoat.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::FishingBoat, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//FishingLog
				case static_cast<int>(animated::FishingLog):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/FishingLog.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::FishingLog, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/NineFrames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//FishingSotong
				case static_cast<int>(animated::FishingSotong):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/FishingSotong.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::FishingSotong, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/25Frames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//FishingNoot
				case static_cast<int>(animated::FishingNoot):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/FishingNoot.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::FishingNoot, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/25Frames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				//FishingCrab
				case static_cast<int>(animated::FishingCrab):
				{
					Sprite* rice1 = new Sprite("../textures/spritesheet/AnimatedTop/FishingCrab.png");
					std::pair<animated, Sprite*> combine1 = std::make_pair(animated::FishingCrab, std::move(rice1));
					rice1->Add_animation("../textures/spritesheet/AnimatedTop/25Frames.txt");
					rice1->curr_anim = AnimationType::Idle;
					rice1->isSpriteSheet = 1;
					SceneManager::loadTopAnimation(grid_to_coord_x, grid_to_coord_y, combine1);
					break;

				}
				}

			}
		}
	}

	void Map::LoadGMap()
	{
		/*Testing whether is loaded correctly*/
		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				int grid_to_coord_x = static_cast<int>(r / static_cast<float>(max_grid_cols_x) * width);
				int grid_to_coord_y = static_cast<int>(c / static_cast<float>(max_grid_rows_y) * height);
				switch (gGrids[r][c])
				{
				case static_cast<int>(grid_number::player):
				{
					Window::player->playerpos.x = static_cast<float>(grid_to_coord_x);
					Window::player->playerpos.y = static_cast<float>(grid_to_coord_y);
					Window::player->playerpos_restart.x = Window::player->playerpos.x;
					Window::player->playerpos_restart.y = Window::player->playerpos.y;
					//#ifndef EDITOR
					Window::player->sp->transformation.Position.x = r / static_cast<float>(max_grid_cols_x) * width;
					Window::player->sp->transformation.Position.y = c / static_cast<float>(max_grid_rows_y) * height;
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
					/*Sprite* avocado = new Sprite("../textures/Tiles/Ingredients/Ingredients0_avocado.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::avocado, avocado);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					break;*/

					Sprite* avocado = new Sprite("../textures/spritesheet/avocadospritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::avocado, avocado);
					avocado->status = 0;
					avocado->isSpriteSheet = 1;
					/*add avocado sprites*/
					avocado->Add_animation("../textures/spritesheet/avocado_normal.txt");
					avocado->Add_animation("../textures/spritesheet/avocado_soy.txt");
					avocado->Add_animation("../textures/spritesheet/avocado_wasabi.txt");
					avocado->Add_animation("../textures/spritesheet/avocado_both.txt");
					avocado->curr_anim = AnimationType::Idle;
					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					std::string String = IngredientToString(grid_number::avocado);
					loadedIngredients.insert({ String ,avocado });
					break;
				}
				case static_cast<int>(grid_number::cucumber):
				{
					Sprite* cucumber = new Sprite("../textures/Tiles/Ingredients/Ingredients0_cucumber.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::cucumber, cucumber);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					std::string String = IngredientToString(grid_number::cucumber);
					loadedIngredients.insert({ String ,cucumber });
					break;
				}
				case static_cast<int>(grid_number::corn):
				{
					Sprite* corn = nullptr;
					if (maki_city != 1)
					{
						corn = new Sprite("../textures/Tiles/Ingredients/Ingredients0_ew_corn.png");

					}
					else
					{
						corn = new Sprite("../textures/Tiles/Maki_City/City_Ingredients/MakiCity_Corn.png");

					}

					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::corn, corn);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::corn);
					loadedIngredients.insert({ String ,corn });
					break;
				}

				case static_cast<int>(grid_number::inari):
				{
					Sprite* inari = nullptr;
					if (maki_city != 1)
					{
						inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");

					}
					else
					{
						inari = new Sprite("../textures/Tiles/Maki_City/City_Ingredients/MakiCity_Inari.png");

					}

					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::inari, inari);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::inari);
					loadedIngredients.insert({ String ,inari });
					break;
				}
				case static_cast<int>(grid_number::octopus):
				{
					Sprite* octopus = new Sprite("../textures/Tiles/Ingredients/Ingredients0_octopus.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::octopus, octopus);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::octopus);
					loadedIngredients.insert({ String ,octopus });
					break;
				}
				case static_cast<int>(grid_number::rice):
				{
					rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::rice, rice);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::rice);
					loadedIngredients.insert({ String ,rice });
					break;
				}
				//roes
				case static_cast<int>(grid_number::roes):
				{
					Sprite* roes = nullptr;
					if (maki_city != 1)
					{
						roes = new Sprite("../textures/Tiles/Ingredients/Ingredients0_roes.png");

					}
					else
					{
						roes = new Sprite("../textures/Tiles/Maki_City/City_Ingredients/MakiCity_Roes.png");

					}
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::roes, roes);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::roes);
					loadedIngredients.insert({ String ,roes });
					break;
				}
				//salmon
				case static_cast<int>(grid_number::salmon):
				{
					salmon = new Sprite("../textures/spritesheet/salmonspritesheet.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::salmon, salmon);
					salmon->status = 0;
					salmon->isSpriteSheet = 1;
					/*add salmon sprites*/
					salmon->Add_animation("../textures/spritesheet/salmon_normal.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_soy.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_wasabi.txt");
					salmon->Add_animation("../textures/spritesheet/salmon_both.txt");
					salmon->curr_anim = AnimationType::Idle;
					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::salmon);
					loadedIngredients.insert({ String ,salmon });
					break;
				}
				//tamago
				case static_cast<int>(grid_number::tamago):
				{
					Sprite* tamago = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tamago.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tamago, tamago);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::tamago);
					loadedIngredients.insert({ String ,tamago });
					break;
				}
				//tofu
				case static_cast<int>(grid_number::tofu):
				{
					Sprite* tofu = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tofu.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tofu, tofu);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::tofu);
					loadedIngredients.insert({ String ,tofu });
					break;
				}
				//tuna
				case static_cast<int>(grid_number::tuna):
				{
					Sprite* tuna = nullptr;
					if (maki_city != 1)
					{
						tuna = new Sprite("../textures/Tiles/Ingredients/Ingredients0_tuna.png");

					}
					else
					{
						tuna = new Sprite("../textures/Tiles/Maki_City/City_Ingredients/MakiCity_Tuna.png");

					}
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tuna, tuna);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::tuna);
					loadedIngredients.insert({ String ,tuna });
					break;
				}
				//nori
				case static_cast<int>(grid_number::nori):
				{
					Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::nori, std::move(nori));

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::nori);
					loadedIngredients.insert({ String ,nori });
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

					std::string String = IngredientToString(grid_number::soya);
					loadedIngredients.insert({ String ,soya });
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

					std::string String = IngredientToString(grid_number::wasabi);
					loadedIngredients.insert({ String ,wasabi });
					break;
				}
				//tea
				case static_cast<int>(grid_number::tea):
				{
					tea = new Sprite("../textures/spritesheet/teaspritesheet.png");
					tea->isSpriteSheet = 1;
					tea->Add_animation("../textures/spritesheet/tea_Idle.txt");
					tea->Add_animation("../textures/spritesheet/tea_Pour.txt");
					tea->curr_anim = AnimationType::Idle;
					std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::tea, tea);

					SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);

					std::string String = IngredientToString(grid_number::tea);
					loadedIngredients.insert({ String ,tea });
					break;
				}
				//sinkhole
				case static_cast<int>(grid_number::sinkhole):
				{
					if (Map::maki_city != 1)
					{
						Sprite* sinkhole = new Sprite("../textures/Tiles/Ground_GunkanVillage/Sinkhole.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::sinkhole, sinkhole);
						SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					}
					else
					{
						Sprite* sinkhole = new Sprite("../textures/Tiles/Maki_City/City_Sinkhole/Sinkhole_City_Empty.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::sinkhole, sinkhole);
						SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					}

					break;
				}
				//filled sinkhole
				case static_cast<int>(grid_number::filledsinkhole):
				{
					if (Map::maki_city != 1)
					{
						Sprite* filledsinkhole = new Sprite("../textures/Tiles/Ground_GunkanVillage/Sinkhole_Filled.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::filledsinkhole, filledsinkhole);
						SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					}
					else
					{
						Sprite* filledsinkhole = new Sprite("../textures/Tiles/Maki_City/City_Sinkhole/Sinkhole_City_Filled.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::filledsinkhole, filledsinkhole);
						SceneManager::loadIngr(grid_to_coord_x, grid_to_coord_y, r, c, combine);
					}

					break;
				}
				}
			}
		}
	}

	void Map::LoadWMap()
	{
		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				int grid_to_coord_x = static_cast<int>(r / static_cast<float>(max_grid_cols_x) * width);
				int grid_to_coord_y = static_cast<int>(c / static_cast<float>(max_grid_rows_y) * height);

				switch (wGrids[r][c])
				{

					// Ingredients that have boxes are: avocado, cucumber,corn,inari,octopus,rice,roes,salmon,tamago,tofu,tuna,nori	
				case static_cast<int>(wall_type::avocado_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Avocado.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::avocado_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::avocado, wall_type::avocado_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::avocado_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::avocado_box);
					loadedBoxes.insert({ String ,box});
					break;
				}
				//cucumber
				case static_cast<int>(wall_type::cucumber_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Cucumber.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::cucumber_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::cucumber, wall_type::cucumber_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::cucumber_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::cucumber_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//corn
				case static_cast<int>(wall_type::corn_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Corn.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::corn_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::corn, wall_type::corn_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::corn_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::corn_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//octopus
				case static_cast<int>(wall_type::octopus_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Octopus.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::octopus_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::octopus, wall_type::octopus_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::octopus_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::octopus_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//roes
				case static_cast<int>(wall_type::roes_box):
				{
					Sprite* box = nullptr;
					if (maki_city != 1)
					{
						box = new Sprite("../textures/Tiles/Pods/Pod_Roes.png");

					}
					else
					{
						box = new Sprite("../textures/Tiles/Maki_City/City_Pods/City_Restaurant_5.png");
					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::roes_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::roes, wall_type::roes_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::roes_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::roes_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//salmon
				case static_cast<int>(wall_type::salmon_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Salmon.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::salmon_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::salmon, wall_type::salmon_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::salmon_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::salmon_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//tamago
				case static_cast<int>(wall_type::tamago_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tamago.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tamago_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::tamago, wall_type::tamago_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::tamago_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::tamago_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//tofu
				case static_cast<int>(wall_type::tofu_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tofu.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tofu_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::tofu, wall_type::tofu_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::tofu_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::tofu_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//tuna
				case static_cast<int>(wall_type::tuna_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Tuna.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::tuna_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::tuna, wall_type::tuna_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::tuna_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::tuna_box);
					loadedBoxes.insert({ String ,box });
					break;
				}
				//nori
				case static_cast<int>(wall_type::nori_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Nori.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::nori_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::nori, wall_type::nori_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::nori_box },box });


					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::nori_box);
					loadedBoxes.insert({ String ,box });
					break;
				}

				case static_cast<int>(wall_type::rice_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::rice_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::rice, wall_type::rice_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::rice_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::rice_box);
					loadedBoxes.insert({ String ,box });
					break;

				}


				case static_cast<int>(wall_type::inari_box):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Inari.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::inari_box, box);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);


					levelWinConditions.emplace(std::pair(std::pair(grid_number::inari, wall_type::inari_box), box));
					SceneManager::boxcontainer.push_back({ {wall_type::inari_box },box });

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;

					std::string String = PodToString(wall_type::inari_box);
					loadedBoxes.insert({ String ,box });
					break;
				}

				case static_cast<int>(wall_type::ground1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_1.jpg");

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::ground1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::ground2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_2.jpg");

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::ground2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//no_longer_used
				case static_cast<int>(wall_type::no_longer_used):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Sinkhole.png");

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::no_longer_used, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall0):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_2.1.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall0_1):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall0_1.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_2.2.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall0_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall1):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall1.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.8.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall2):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.2.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}



				case static_cast<int>(wall_type::Wall2_1):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1)
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall2_1.jpg");

					}
					else
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.9.png");
					}
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
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.5.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall3_1):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_1.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_2.3.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_1, tile);
					//tile->Add_animation()
					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall3_2):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_2.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_2.4.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_2, tile);
					//tile->Add_animation()
					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}


				case static_cast<int>(wall_type::Wall3_3):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall3_3.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_2.5.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall3_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				case static_cast<int>(wall_type::Wall4):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall4.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.1.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				case static_cast<int>(wall_type::Wall5):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall5.jpg");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_Empty.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall5, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}



				case static_cast<int>(wall_type::Wall6):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall6.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.3.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall6, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				//wall 7
				case static_cast<int>(wall_type::Wall7):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall7.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.7.png");

					}
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall7, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				//wall 8
				case static_cast<int>(wall_type::Wall8):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall8.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.4.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall8, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//wall 9
				case static_cast<int>(wall_type::Wall9):
				{
					Sprite* tile = nullptr;
					if (maki_city != 1) //if it is not maki city
					{
						tile = new Sprite("../textures/Tiles/Wall/RicePlain_Wall9.png");

					}
					else //it is maki city
					{
						tile = new Sprite("../textures/Tiles/Maki_City/Wall/City_Road_1.6.png");

					}

					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Wall9, tile);

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
				//	Gunkan_Ground_1_1,		//l
				case static_cast<int>(wall_type::Gunkan_Ground_1_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_1_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_1_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_1_2,		//m
				case static_cast<int>(wall_type::Gunkan_Ground_1_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_1_2.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_1_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_1_3,		//n
				case static_cast<int>(wall_type::Gunkan_Ground_1_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_1_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_1_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_1_4,		//o
				case static_cast<int>(wall_type::Gunkan_Ground_1_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_1_4.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_1_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_2_1,		//p
				case static_cast<int>(wall_type::Gunkan_Ground_2_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_2_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_2_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				//	Gunkan_Ground_2_2,		
				case static_cast<int>(wall_type::Gunkan_Ground_2_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_2_2.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_2_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}

				//	Gunkan_Ground_2_3,	
				case static_cast<int>(wall_type::Gunkan_Ground_2_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_2_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_2_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_3_1,	
				case static_cast<int>(wall_type::Gunkan_Ground_3_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_3_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_3_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_3_2,	
				case static_cast<int>(wall_type::Gunkan_Ground_3_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_3_2.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_3_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_3_3,	
				case static_cast<int>(wall_type::Gunkan_Ground_3_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_3_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_3_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_6_1,	
				case static_cast<int>(wall_type::Gunkan_Ground_6_1):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_6_1.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_6_1, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_6_2,	
				case static_cast<int>(wall_type::Gunkan_Ground_6_2):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_6_2.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_6_2, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_6_3,	
				case static_cast<int>(wall_type::Gunkan_Ground_6_3):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_6_3.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_6_3, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Gunkan_Ground_6_4,	
				case static_cast<int>(wall_type::Gunkan_Ground_6_4):
				{
					Sprite* tile = new Sprite("../textures/Tiles/Ground_GunkanVillage/Gunkan_Ground_6_4.png");
					std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Gunkan_Ground_6_4, tile);

					SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);

					break;
				}
				//	Ground Top 1,	
				case static_cast<int>(wall_type::Ground_Top_1):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_1.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_1, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_1.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_1, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_1.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_1, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_1.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_1, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 2,	
				case static_cast<int>(wall_type::Ground_Top_2):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_2.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_2, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_2.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_2, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_2.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_2, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_2.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_2, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 3,	
				case static_cast<int>(wall_type::Ground_Top_3):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_3.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_3, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_3.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_3, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_3.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_3, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_3.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_3, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 4,	
				case static_cast<int>(wall_type::Ground_Top_4):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_4.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_4, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_4.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_4, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_4.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_4, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_4.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_4, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 5,	
				case static_cast<int>(wall_type::Ground_Top_5):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_5.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_5, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_5.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_5, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_5.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_5, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_5.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_5, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 6,	
				case static_cast<int>(wall_type::Ground_Top_6):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_6.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_6, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_6.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_6, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_6.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_6, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_6.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_6, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 7,	
				case static_cast<int>(wall_type::Ground_Top_7):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_7.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_7, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_7.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_7, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_7.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_7, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_7.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_7, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 8,	
				case static_cast<int>(wall_type::Ground_Top_8):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_8.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_8, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_8.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_8, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_8.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_8, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_8.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_8, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 9,	
				case static_cast<int>(wall_type::Ground_Top_9):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_9.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_9, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_9.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_9, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_9.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_9, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_9.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_9, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 10,	
				case static_cast<int>(wall_type::Ground_Top_10):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_10.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_10, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 2)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Village_top/Village_Top_Ground_10.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_10, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 3)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/Fishing_top/Fishing_Ground_Top_10.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_10, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_10.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_10, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}
				//	Ground Top 11,	
				case static_cast<int>(wall_type::Ground_Top_11):
				{
					if (Map::region == 1)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/RicePlain_top/RicePlain_Top_Ground_11.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_11, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					else if (Map::region == 4)
					{
						Sprite* tile = new Sprite("../textures/StaticTop/City_top/City_Ground_Top_11.png");
						std::pair<wall_type, Sprite*> combine = std::make_pair(wall_type::Ground_Top_11, tile);

						SceneManager::loadTile(grid_to_coord_x, grid_to_coord_y, combine);
					}
					break;
				}

				default:
					assert("Texture type not found\n");
					break;
				}
			}
		}
	}

	bool Map::isWin()
	{
		return ((win_amt == SceneManager::amt_of_win_conditions) ? true : false);
	}


	bool Map::isStuck()
	{
		// if player's grid index is 50, means its STUCK or put all ingr into goals
		if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole)))
		{
			Window::player->isStuck();
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
			next_grid = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
			//Check if left tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori)) ||
				(wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
					wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
			{
				//check if left tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori))
				{
					std::cout << "left ingredient\n";

					//check if tile on the left of ingredient is a wall
					if (wGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
						wGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
					{
						std::cout << "left ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the left of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

						//Set grid
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x -= tile_width;
								ingredient.spr->transformation.Scale = glm::vec2(tile_width - 10.f, tile_height - 10.f);
								ingredient.spr->transformation.Translating({ 5.f, 5.f });

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
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori))
					{
						std::cout << "left ingredient ingredient\n";
						AudioManager.PlayVoice("Oof_1.wav");
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x -= tile_width;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y
								&& inx == Window::player->player_grid_pos.x - 2)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateSoya(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}
						if (salmon->status == 0)
						{
							/*change salmon sprite to with soya*/
							salmon->status = 1;
							salmon->curr_anim = AnimationType::Run;
						}
						else if (salmon->status == 2)
						{
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}
						Window::player->move_left();
						std::cout << "soya dripped\n";
					}

					//check if tile on left of salmon is Wasabi
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::wasabi) &&
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x -= tile_width;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y
								&& inx == Window::player->player_grid_pos.x - 2)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateWasabi(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}

						/*check salmon status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with wasabi*/
							salmon->status = 2;
							salmon->curr_anim = AnimationType::Jump;
						}
						else if (salmon->status == 1)
						{
							/*if has soya on it, change to both*/
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}

						Window::player->move_left();
						std::cout << "Wasabi dripped\n";
					}
					//check if tile on left of salmon is tea
					else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::tea) &&
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						/*If salmon has either wasabi/soya/both on it*/
						if (salmon->status != 0)
						{
							// set grid
							grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
							gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
							gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
							if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
							{
								wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
							}
							else
							{
								gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
							}
							for (auto ingredient : SceneManager::ingredientcontainer)
							{
								if (ingredient.nametag == check)
								{
									ingredient.spr->transformation.Position.x -= tile_width;
									break;
								}
							}
							for (auto ingredient : SceneManager::ingredientcontainer)
							{

								auto& ing_transform = ingredient.spr->transformation.grid_pos;
								auto [inx, iny] = ing_transform;
								if (iny == Window::player->player_grid_pos.y
									&& inx == Window::player->player_grid_pos.x - 2)
								{
									ingredient.spr->timer = 0;
									SceneManager::activateTea(ingredient.spr);
									ingredient.spr->animeMe = true;
									break;
								}
							}

							/*change salmon sprite to nothing*/
							if (salmon->status != 0)
							{
								salmon->status = 0;
							}
							salmon->curr_anim = AnimationType::Idle;

							Window::player->move_left();
							std::cout << "tea dripped\n";
						}
					}

					//check if it's a box
					else if (wGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) &&
						wGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);
						AudioManager.PlaySFX("Closing container.wav");
						AudioManager.SetAudioVolume(1.f);
						AudioManager.PlayVoice("YES_1.wav");
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x) - (2 * static_cast<int>(tile_width) + 5), static_cast<int>(Window::player->playerpos.y),
							static_cast<int>(Window::player->playerpos.x) - 2, static_cast<int>(Window::player->playerpos.y), combine);
						boxcover->target_pos = boxcover->transformation.Position.y;
						boxcover->curr_pos = boxcover->transformation.Position.y - 20;

						SceneManager::set_target_pos(boxcover);
						SceneManager::set_curr_pos(boxcover);
						boxcover->animeMe = true;
						gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto& ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x -= tile_width + 5;
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x -= tile_width;
								break;
							}
						}

						std::cout << "left ingredient space\n";
						Window::player->move_left();
					}
				}
				/*check wall*/
				else if (wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
					wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
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
			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "left sinkhole\n";
				Window::player->move_left();
				Window::player->current_anim = AnimationType::Jump;
				Window::player->sp->transformation.Scaling(0.1f);
				Window::player->stop();
				AudioManager.PlayVoice("Sad_1.wav");
			}
			else
			{
				//Check if left tile is box
				if (wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) && wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
					Window::player->move_left();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}
				/*soya/tea/wasabi with player*/
				else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::tea) &&
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::wasabi))
				{
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::player))
					{
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					}
					else
					{
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
					}
					ex_box = static_cast<wall_type>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);
					Window::player->move_left();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
				}
				//Check if current tile is insidebox
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_left();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
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
		Window::player->stop();
		curr_grid = next_grid;
	}

	void Map::collision_check_right()
	{
		if (!isStuck())
		{
			next_grid = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
			//Check if right tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori)) ||
				(wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
					wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
			{
				//check if right tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori))
				{
					std::cout << "right ingredient\n";

					//check if tile on the right of ingredient is a wall
					if (wGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
						wGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
					{
						std::cout << "right ingredient wall\n";
						Window::player->stop();
					}
					//check if tile on the right of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

						//Set grid
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::filledsinkhole);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x += tile_width;
								ingredient.spr->transformation.Scale = glm::vec2(tile_width - 10.f, tile_height - 10.f);
								ingredient.spr->transformation.Translating({ 5.f, 5.f });

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
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::nori))
					{
						std::cout << "right ingredient ingredient\n";
						AudioManager.PlayVoice("Oof_1.wav");
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x += tile_width;
								break;
							}
						}
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto& [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y
								&& inx == Window::player->player_grid_pos.x + 2)
							{
								// start some animations
								ingredient.spr->timer = 0;
								SceneManager::activateSoya(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}
						/*check soya status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with soya*/
							salmon->status = 1;
							salmon->curr_anim = AnimationType::Run;
						}
						else if (salmon->status == 2)
						{
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}
						Window::player->move_right();
						std::cout << "soya dripped\n";
					}

					//check if tile on left of salmon is Wasabi
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::wasabi) &&
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x += tile_width;
								break;
							}
						}
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto& [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y
								&& inx == Window::player->player_grid_pos.x + 2)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateWasabi(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}

						/*check salmon status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with wasabi*/
							salmon->status = 2;
							salmon->curr_anim = AnimationType::Jump;
						}
						else if (salmon->status == 1)
						{
							/*if has soya on it, change to both*/
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}

						Window::player->move_right();
						std::cout << "Wasabi dripped\n";
					}

					//check if tile on left of salmon is tea
					else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::tea) &&
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::salmon))
					{
						/*If salmon has either wasabi/soya/both on it*/
						if (salmon->status != 0)
						{
							// set grid
							grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
							gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::salmon);
							gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
							if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
							{
								wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
							}
							else
							{
								gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
							}
							for (auto ingredient : SceneManager::ingredientcontainer)
							{
								if (ingredient.nametag == check)
								{
									ingredient.spr->transformation.Position.x += tile_width;
									break;
								}
							}
							for (auto& ingredient : SceneManager::ingredientcontainer)
							{

								auto& ing_transform = ingredient.spr->transformation.grid_pos;
								auto& [inx, iny] = ing_transform;
								if (iny == Window::player->player_grid_pos.y
									&& inx == Window::player->player_grid_pos.x + 2)
								{
									ingredient.spr->timer = 0;
									SceneManager::activateTea(ingredient.spr);
									ingredient.spr->animeMe = true;
									break;
								}
							}

							/*change salmon sprite to nothing*/
							if (salmon->status != 0)
							{
								salmon->status = 0;
							}
							salmon->curr_anim = AnimationType::Idle;

							Window::player->move_right();
							std::cout << "tea dripped\n";
						}
					}

					//check if it's a box
					else if (wGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) &&
						wGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

						gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::boxcover);
						AudioManager.PlaySFX("Closing container.wav");
						AudioManager.SetAudioVolume(1.f);
						AudioManager.PlayVoice("YES_1.wav");
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x) + (2 * static_cast<int>(tile_width)), static_cast<int>(Window::player->playerpos.y), static_cast<int>(Window::player->player_grid_pos.x) + 2, static_cast<int>(Window::player->player_grid_pos.y), combine);
						boxcover->target_pos = boxcover->transformation.Position.y;
						boxcover->curr_pos = boxcover->transformation.Position.y - 20;

						SceneManager::set_target_pos(boxcover);
						SceneManager::set_curr_pos(boxcover);
						boxcover->animeMe = true;
						gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x += tile_width;
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.x += tile_width;
								break;
							}
						}

						std::cout << "right ingredient space\n";
						Window::player->move_right();
					}
				}
				/*check wall*/
				else if (wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
					wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
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
			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::sinkhole))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "right sinkhole\n";
				Window::player->move_right();
				Window::player->current_anim = AnimationType::Jump;
				//Window::player->sp->transformation.Scale = glm::vec2(80, 80);
				Window::player->sp->transformation.Scaling(0.1f);
				Window::player->stop();
				AudioManager.PlayVoice("Sad_1.wav");
			}
			//Just move
			else
			{
				//Check if right tile is a box
				if (wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(wall_type::rice_box) && wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
					Window::player->move_right();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
				}
				/*soya/tea/wasabi with player*/
				else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] >= static_cast<int>(grid_number::tea) &&
					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] <= static_cast<int>(grid_number::wasabi))
				{
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::player))
					{
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					}
					else
					{
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
					}
					//set external ingredient to keep first
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);
					Window::player->move_right();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
				}
				//Check if current tile is insidebox
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
				}
				//Check if current tile is inbox2
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_right();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					wGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::inari_box);
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
		Window::player->stop();
		curr_grid = next_grid;
	}

	void Map::collision_check_down()
	{
		if (!isStuck())
		{
			next_grid = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
			//Check if below tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::nori)) ||
				(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) &&
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last)))
			{
				//check if below tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::nori))
				{
					std::cout << "down ingredient\n";

					//check if tile below of ingredient is a wall
					if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] > static_cast<int>(wall_type::first) &&
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] < static_cast<int>(wall_type::last))
					{
						std::cout << "down ingredient wall\n";
						Window::player->stop();
					}
					//check if tile below of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(grid_number::sinkhole))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::filledsinkhole);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y += tile_height;
								ingredient.spr->transformation.Scale = glm::vec2(tile_width - 10.f, tile_height - 10.f);
								ingredient.spr->transformation.Translating({ 5.f, 5.f });

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
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(grid_number::nori))
					{
						std::cout << "down ingredient ingredient\n";
						AudioManager.PlayVoice("Oof_1.wav");
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y += tile_height;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y + 2
								&& inx == Window::player->player_grid_pos.x)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateSoya(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}
						/*check soya status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with soya*/
							salmon->status = 1;
							salmon->curr_anim = AnimationType::Run;
						}
						else if (salmon->status == 2)
						{
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}
						Window::player->move_down();
						std::cout << "soya dripped\n";
					}

					//check if tile on left of salmon is Wasabi
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(grid_number::wasabi) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y += tile_height;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y + 2
								&& inx == Window::player->player_grid_pos.x)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateWasabi(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}

						/*check salmon status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with wasabi*/
							salmon->status = 2;
							salmon->curr_anim = AnimationType::Jump;
						}
						else if (salmon->status == 1)
						{
							/*if has soya on it, change to both*/
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}

						Window::player->move_down();
						std::cout << "Wasabi dripped\n";
					}

					//check if tile on left of salmon is tea
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(grid_number::tea) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::salmon))
					{
						/*If salmon has either wasabi/soya/both on it*/
						if (salmon->status != 0)
						{
							// set grid
							grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::salmon);
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);
							if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
							{
								wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
							}
							else
							{
								gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
							}
							for (auto ingredient : SceneManager::ingredientcontainer)
							{
								if (ingredient.nametag == check)
								{
									ingredient.spr->transformation.Position.y += tile_height;
									break;
								}
							}
							for (auto ingredient : SceneManager::ingredientcontainer)
							{

								auto& ing_transform = ingredient.spr->transformation.grid_pos;
								auto [inx, iny] = ing_transform;
								if (iny == Window::player->player_grid_pos.y + 2
									&& inx == Window::player->player_grid_pos.x)
								{
									ingredient.spr->timer = 0;
									SceneManager::activateTea(ingredient.spr);
									ingredient.spr->animeMe = true;
									break;
								}
							}

							/*change salmon sprite to nothing*/
							if (salmon->status != 0)
							{
								salmon->status = 0;
							}
							salmon->curr_anim = AnimationType::Idle;

							Window::player->move_down();
							std::cout << "tea dripped\n";
						}
					}
					//check if it's a box
					else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(wall_type::rice_box) &&
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(grid_number::boxcover);
						AudioManager.PlaySFX("Closing container.wav");
						AudioManager.SetAudioVolume(1.f);
						AudioManager.PlayVoice("YES_1.wav");
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x), static_cast<int>(Window::player->playerpos.y) + (2 * static_cast<int>(tile_height)), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y + 2, combine);
						boxcover->target_pos = boxcover->transformation.Position.y;
						boxcover->curr_pos = boxcover->transformation.Position.y - 20;

						SceneManager::set_target_pos(boxcover);
						SceneManager::set_curr_pos(boxcover);
						boxcover->animeMe = true;
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y += tile_height;
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y += tile_height;
								break;
							}
						}

						std::cout << "down ingredient space\n";
						Window::player->move_down();
					}
				}
				/*check wall*/
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) ||
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last))
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
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(grid_number::sinkhole))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "down sinkhole\n";
				Window::player->move_down();
				Window::player->current_anim = AnimationType::Jump;
				Window::player->sp->transformation.Scaling(0.1f);
				Window::player->stop();
				AudioManager.PlayVoice("Sad_1.wav");
			}
			//Just move
			else
			{
				//Check if up tile is a box
				if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(wall_type::rice_box) && wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(wall_type::tuna_box))
				{
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
					Window::player->move_down();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::space);
				}
				/*soya/tea/wasabi with player*/
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] >= static_cast<int>(grid_number::tea) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] <= static_cast<int>(grid_number::wasabi))
				{
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::player))
					{
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					}
					else
					{
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
					}
					//set external ingredient to keep first
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
					Window::player->move_down();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					//gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::space);
				}
				//Check if current tile is insidebox
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_down();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ex_box);
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
		Window::player->stop();
		curr_grid = next_grid;
	}

	void Map::collision_check_up()
	{
		if (!isStuck())
		{
			next_grid = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
			//Check if above tile is a wall or ingredient
			if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(grid_number::ingredients) &&
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::nori)) ||
				(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) &&
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last)))
			{
				//check if above tile is ingredient
				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(grid_number::ingredients) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::nori))
				{
					std::cout << "up ingredient\n";

					//check if tile above of ingredient is a wall
					if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] > static_cast<int>(wall_type::first) &&
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] < static_cast<int>(wall_type::last))
					{
						std::cout << "up ingredient wall\n";
						Window::player->stop();
					}
					//check if tile above of ingredient is a sinkhole
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(grid_number::sinkhole))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::filledsinkhole);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						unsigned short it = 0;
						for (auto& ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y -= tile_height;
								ingredient.spr->transformation.Scale = glm::vec2(tile_width - 10.f, tile_height - 10.f);
								ingredient.spr->transformation.Translating({ 5.f, 5.f });

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
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(grid_number::nori))
					{
						std::cout << "up ingredient ingredient\n";
						AudioManager.PlayVoice("Oof_1.wav");
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y -= tile_height;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y - 2
								&& inx == Window::player->player_grid_pos.x)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateSoya(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}

						/*check soya status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with soya*/
							salmon->status = 1;
							salmon->curr_anim = AnimationType::Run;
						}
						else if (salmon->status == 2)
						{
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}
						Window::player->move_up();
						std::cout << "soya dripped\n";
					}

					//check if tile on left of salmon is Wasabi
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(grid_number::wasabi) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::salmon))
					{
						// set grid
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::salmon);
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y -= tile_height;
								break;
							}
						}
						for (auto ingredient : SceneManager::ingredientcontainer)
						{

							auto& ing_transform = ingredient.spr->transformation.grid_pos;
							auto [inx, iny] = ing_transform;
							if (iny == Window::player->player_grid_pos.y - 2
								&& inx == Window::player->player_grid_pos.x)
							{
								ingredient.spr->timer = 0;
								SceneManager::activateWasabi(ingredient.spr);
								ingredient.spr->animeMe = true;
								break;
							}
						}

						/*check salmon status*/
						if (salmon->status == 0)
						{
							/*change salmon sprite to with wasabi*/
							salmon->status = 2;
							salmon->curr_anim = AnimationType::Jump;
						}
						else if (salmon->status == 1)
						{
							/*if has soya on it, change to both*/
							salmon->status = 3;
							salmon->curr_anim = AnimationType::Both;
						}

						Window::player->move_up();
						std::cout << "Wasabi dripped\n";
					}
					//check if tile on left of salmon is tea
					else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(grid_number::tea) &&
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::salmon))
					{
						/*If salmon has either wasabi/soya/both on it*/
						if (salmon->status != 0)
						{
							// set grid
							grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::salmon);
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);
							if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
							{
								wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
							}
							else
							{
								gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
							}
							for (auto& ingredient : SceneManager::ingredientcontainer)
							{
								if (ingredient.nametag == check)
								{
									ingredient.spr->transformation.Position.y -= tile_height;
									break;
								}
							}
							for (auto& ingredient : SceneManager::ingredientcontainer)
							{

								auto& ing_transform = ingredient.spr->transformation.grid_pos;
								auto& [inx, iny] = ing_transform;
								if (iny == Window::player->player_grid_pos.y - 2
									&& inx == Window::player->player_grid_pos.x)
								{
									ingredient.spr->timer = 0;
									SceneManager::activateTea(ingredient.spr);
									ingredient.spr->animeMe = true;
									break;
								}
							}

							/*change salmon sprite to nothing*/
							if (salmon->status != 0)
							{
								salmon->status = 0;
							}
							salmon->curr_anim = AnimationType::Idle;

							Window::player->move_up();
							std::cout << "tea dripped\n";
						}
					}

					//check if it's a box
					else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] >= static_cast<int>(wall_type::rice_box) &&
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] <= static_cast<int>(wall_type::tuna_box))
					{
						grid_number check = static_cast<grid_number>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(grid_number::boxcover);
						AudioManager.PlaySFX("Closing container.wav");
						AudioManager.SetAudioVolume(1.f);
						AudioManager.PlayVoice("YES_1.wav");
						Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
						std::pair<grid_number, Sprite*> combine = std::make_pair(grid_number::boxcover, boxcover);
						SceneManager::loadIngr(static_cast<int>(Window::player->playerpos.x), static_cast<int>(Window::player->playerpos.y) - (2 * static_cast<int>(tile_height)), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y - 2, combine);
						boxcover->target_pos = boxcover->transformation.Position.y;
						boxcover->curr_pos = boxcover->transformation.Position.y - 20;

						SceneManager::set_target_pos(boxcover);
						SceneManager::set_curr_pos(boxcover);
						boxcover->animeMe = true;
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(grid_number::player);

						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y -= tile_height;
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
						if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
						{
							wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
						}
						else
						{
							gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
						}

						for (auto ingredient : SceneManager::ingredientcontainer)
						{
							if (ingredient.nametag == check)
							{
								ingredient.spr->transformation.Position.y -= tile_height;
								break;
							}
						}

						std::cout << "up ingredient space\n";
						Window::player->move_up();
					}
				}
				/*check wall*/
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) ||
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last))
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
			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(grid_number::sinkhole))
			{
				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);

				std::cout << "up sinkhole\n";
				Window::player->move_up();
				Window::player->current_anim = AnimationType::Jump;
				Window::player->sp->transformation.Scaling(0.1f);
				Window::player->stop();
				AudioManager.PlayVoice("Sad_1.wav");
			}
			//Just move
			else
			{
				//Check if up tile is any box
				if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(wall_type::rice_box) && wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(wall_type::tuna_box))
				{
					//save the value of the box stepped on
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

					Window::player->move_up();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(grid_number::space);
				}
				/*soya/tea/wasabi with player*/
				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] >= static_cast<int>(grid_number::tea) &&
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] <= static_cast<int>(grid_number::wasabi))
				{
					if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(grid_number::player))
					{
						gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::space);
					}
					else
					{
						wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ex_box);
					}
					//set external ingredient to keep first
					ex_box = static_cast<wall_type>(wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
					Window::player->move_up();
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(wall_type::insidebox);
				}
				//Check if current tile is insidebox
				else if (wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(wall_type::insidebox))
				{
					Window::player->move_up();
					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(grid_number::player);
					wGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ex_box);
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
		Window::player->stop();
		curr_grid = next_grid;
	}

	void Map::print_map_to_console()
	{
		std::cout << "**************************** gGrid & aGrid MAP LAYOUT ************************************" << std::endl;

		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{
				if (gGrids[r][c] >= '!' && gGrids[r][c] <= '8')
				{
					std::cout << std::setw(4) << static_cast<char>(gGrids[r][c]) << std::setw(4);

				}
				else
				{
					std::cout << std::setw(4) << static_cast<char>(aGrids[r][c]) << std::setw(4);

				}
			}
			std::cout << std::endl;
		}

		std::cout << "Goals: " << SceneManager::amt_of_win_conditions << std::endl;
		std::cout << "Current goals: " << win_amt << std::endl;

		std::cout << "****************************************************************************" << std::endl;

		std::cout << "**************************** wGrid MAP LAYOUT ************************************" << std::endl;
		for (int c = 0; c < max_grid_rows_y; c++)
		{
			for (int r = 0; r < max_grid_cols_x; r++)
			{

				std::cout << std::setw(4) << static_cast<char>(wGrids[r][c]) << std::setw(4);
			}
			std::cout << std::endl;
		}

		std::cout << "****************************************************************************" << std::endl;
	}

	void Map::DrawMap()
	{

		SceneManager::drawTile();
		SceneManager::drawSinkHole();
		SceneManager::drawInsideSinkHole();
		SceneManager::drawIngr();
		SceneManager::drawTop();
		glUniform1f(glGetUniformLocation(Shaders->Textured_Shader()->get_hdl(), "alpha"), 1.f);
		if (Window::player->resetCount >= 1 && Window::player->resetCount < 5)
		{
			SceneManager::FadeOut();
			SceneManager::drawEncourage();

		}
		else if (Window::player->resetCount >= 5)
		{
			SceneManager::FadeOut();
			SceneManager::drawGiveUp();
		}
		Shaders->Textured_Shader()->use();
		//SceneManager::drawRice();
	}
	/********************************************
	 Return the value inside a cell that you click
	********************************************/
	int Map::GetValue(double col_x, double row_y)
	{
		//if you are accessing out of the given grid
		//if (col_x -1 > (max_grid_rows_y) || row_y -1 > (max_grid_cols_x))
		//{
		//	std::cout << "you are out of range!" << std::endl;
		//	return 3; //if you are pressing out of this grid, return 0 as tile value 
		//}
		//else
		return gGrids[static_cast<int>(col_x)][static_cast<int>(row_y)];
	}
	/********************************************
	 Set the value inside a cell that you click
	********************************************/
	void Map::SetValue(double col_x, double row_y, int value)
	{
		//if its a grid_number tile, put it in gGrids
		if (value >= '!' && value <= '7')
		{
			gGrids[static_cast<int>(col_x)][static_cast<int>(row_y)] = value;
		}
		else //put animated in aGrids
		{
			aGrids[static_cast<int>(col_x)][static_cast<int>(row_y)] = value;
		}
		//Window::loaded = false;
		//print_map_to_console(); //debugging
	}


	/**************************************************************
	 Helper function to convert enum in sceneManager.h to string
	**************************************************************/
	std::string Map::IngredientToString(grid_number ingredient)
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

		case(grid_number::tea):
			return ("Tea");
			break;

		default:
			return "";
			break;
		}

	}

	/**************************************************************
	 Helper function to convert enum in sceneManager.h to string
	**************************************************************/
	std::string Map::PodToString(wall_type pod)
	{
		switch (pod)
		{
		case(wall_type::avocado_box):
			return ("Avocado_box");
			break;

		case(wall_type::corn_box):
			return ("Corn_box");
			break;

		case(wall_type::cucumber_box):
			return ("Cucumber_box");
			break;

		case(wall_type::inari_box):
			return ("Inari_box");
			break;

		case(wall_type::nori_box):
			return ("Nori_box");
			break;

		case(wall_type::octopus_box):
			return ("Octopus_box");
			break;

		case(wall_type::rice_box):
			return ("Rice_box");
			break;

		case(wall_type::roes_box):
			return ("Roes_box");
			break;

		case(wall_type::salmon_box):
			return ("Salmon_box");
			break;

		case(wall_type::tamago_box):
			return ("Tamago_box");
			break;

		case(wall_type::tofu_box):
			return ("Tofu_box");
			break;

		case(wall_type::tuna_box):
			return ("Tuna_box");
			break;

		default:
			return "";
			break;
		}
	}
}