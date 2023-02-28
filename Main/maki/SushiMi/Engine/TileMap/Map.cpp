#include "Map.h"

#include "../Window/Window.h"
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../System/Scene/SceneManager.h"
#include "../System/Graphics/TextureSystem.h"
#include "../Core/Core.h"

namespace Core
{
	
	//int Map::gGrids[GRID_ROW][GRID_COL];
	int width, height;
	unsigned int SceneManager::amt_of_win_conditions, win_amt;

	Map::Map()
	{
	}

	Map::~Map()
	{
		for (int i = 0; i < grid_row; i++)
		{
			delete gGrids[i];
			delete cGrids[i];
			delete rGrids[i];
			delete pGrids[i];
		}
		delete gGrids;
		delete cGrids;
		delete rGrids;
		delete pGrids;
	}

	int** Map::gGrids;
	short** Map::cGrids;
	short** Map::rGrids;
	short** Map::pGrids;

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
		cGrids = new short* [grid_row];
		rGrids = new short* [grid_row];
		pGrids = new short* [grid_row];

		for (int i = 0; i < grid_row; i++)
		{
			gGrids[i] = new int[grid_col];
			cGrids[i] = new short[grid_col];
			rGrids[i] = new short[grid_col];
			pGrids[i] = new short[grid_col];
		}

		char ch;
		short sh;

		//for gGrids and cGrids
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				fin >> ch;
				gGrids[r][c] = ch;

				if (ch >= static_cast<char>(wall_type::first) && ch <= static_cast<char>(wall_type::last))
				{
					cGrids[r][c] = 1;
				}
				else if (ch >= static_cast<char>(ingredients::player) && ch <= static_cast<char>(ingredients::end))
				{
					cGrids[r][c] = 2;
				}
				else
				{
					cGrids[r][c] = 0;
				}
			}
		}

		//for rGrids
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				fin >> sh;
				rGrids[r][c] = sh;
			}
		}

		//for pGrids
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				fin >> sh;
				pGrids[r][c] = sh;
			}
		}

		fin.close();
	}

	void Map::ResetMap()
	{
		SceneManager::destroyTile();
		SceneManager::destroyIngr();

		if (Window::timetodeletegrid)
		{
			for (int i = 0; i < grid_row; i++)
			{
				delete gGrids[i];
				delete cGrids[i];
				delete rGrids[i];
				delete pGrids[i];
			}
			delete gGrids;
			delete cGrids;
			delete rGrids;
			delete pGrids;
		}

		win_amt = 0;
		SceneManager::amt_of_win_conditions = 0;
	}

	void Map::LoadMap()
	{
		glfwGetWindowSize(Window::window_ptr, &width, &height);
		
		tile_width = width / grid_row;
		tile_height = height / grid_col;

		tile_counter = 0;
		
		/*Testing whether is loaded correctly*/
		for (int c = 0; c < grid_col; c++)
		{
			for (int r = 0; r < grid_row; r++)
			{
				switch (gGrids[r][c])
				{
				case static_cast<int>(wall_type::rice_ground0) :
					if (TextureSystem::GetTileTexture(wall_type::rice_ground0)) //if no such texture exists
					{
						/*Texture ground1;
						ground1.TextureLoadIn("../textures/Tiles/Ground/RicePlain_Ground0_0.jpg");
						std::pair<ingredients, Texture> combine = std::make_pair(ingredients::ground1, std::move(ground1));

						TextureSystem::addIngrTexture(combine);

						SceneManager::loadIngrTex(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);*/

						Texture tex;
						tex.TextureLoadIn("../textures/Tiles/Ground/RicePlain_Ground0_0.jpg");

						SceneManager::loadTileTex(wall_type::ground0, tex);

						SceneManager::StoreTileCoor()
					}

					SceneManager::StoreIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;

				case static_cast<int>(ingredients::rice_ground1):
					Sprite* ground1 = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_1.jpg");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::ground1, std::move(ground1));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;

				case static_cast<int>(ingredients::rice_ground2):
					Sprite* ground1 = new Sprite("../textures/Tiles/Ground/RicePlain_Ground0_2.jpg");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::ground1, std::move(ground1));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;

				case static_cast<int>(ingredients::player) :
				{
//					Window::player->playerpos.x = r / static_cast<float>(grid_row) * width;
//					Window::player->playerpos.y = c / static_cast<float>(grid_col) * height;
//					Window::player->playerpos_restart.x = Window::player->playerpos.x;
//					Window::player->playerpos_restart.y = Window::player->playerpos.y;
////#ifndef EDITOR
//					Window::player->sp->transformation.Position.x = r / static_cast<float>(grid_row) * width;
//					Window::player->sp->transformation.Position.y = c / static_cast<float>(grid_col) * height;
////#endif
//					/*save player index in grid*/
//					Window::player->player_grid_pos.x = r;
//					Window::player->player_grid_pos.y = c;
//					/*save initial index for restart purposes*/
//					Window::player->player_initial_grid_pos.x = r;
//					Window::player->player_initial_grid_pos.y = c;

					Sprite* player = new Sprite("../textures/spritesheet/spritesheet.png");
					player->transformation.Position = glm::vec2(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height);
					player->transformation.Scale = glm::vec2(100, 100);

					player->Add_animation("../textures/spritesheet/Idle.txt");
					player->Add_animation("../textures/spritesheet/Run.txt");
					break;
				}
					

				case static_cast<int>(ingredients::rice):
				{
					Sprite* rice = new Sprite("../textures/Tiles/Ingredients/Ingredients0_rice.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::rice, std::move(rice));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					

				case static_cast<int>(ingredients::nori):
				{
					Sprite* nori = new Sprite("../textures/Tiles/Ingredients/Ingredients1_nori.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::nori, std::move(nori));

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
				case static_cast<int>(ingredients::inari):
				{
					Sprite* inari = new Sprite("../textures/Tiles/Ingredients/Ingredients0_inari.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::inari, inari);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					SceneManager::loadIngr_initPos(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					

				case static_cast<int>(ingredients::box1):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Rice.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::box1, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;

				}
					

				case static_cast<int>(ingredients::box2):
				{
					Sprite* box = new Sprite("../textures/Tiles/Pods/Pod_Inari.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::box2, box);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);

					SceneManager::win_condition.push_back(std::make_pair(r, c));
					SceneManager::amt_of_win_conditions++;
					break;
				}
					

				case static_cast<int>(ingredients::boxcover):
				{
					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, boxcover);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}

				case static_cast<int>(ingredients::sinkhole):
				{
					Sprite* sinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole0_1.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, sinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}
					
				case static_cast<int>(ingredients::filledsinkhole):
				{
					Sprite* filledsinkhole = new Sprite("../textures/Tiles/Trap/Sinkhole_Filled.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, filledsinkhole);

					SceneManager::loadIngr(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, r, c, combine);
					break;
				}

				//Temporary placeholder for food in sinkhole
				case static_cast<int>(ingredients::temp):
				{
					Sprite* foodinsinkhole = new Sprite("../textures/doge.png");
					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::temp, foodinsinkhole);

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
					//tile->Add_animation()
					SceneManager::loadTile(r / static_cast<float>(grid_row) * width, c / static_cast<float>(grid_col) * height, combine);
					break;
				}

				default:
					assert("Texture type not found\n");
					break;
				}
			}
		}

		print_map_to_console();
	}

	bool Map::isWin()
	{
		return ((win_amt == SceneManager::amt_of_win_conditions) ? true : false);
	}

	//void Map::collision_check_left()
	//{
	//	if (!isStuck())
	//	{
	//		//Check if right tile is a box1
	//		if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box1))
	//		{
	//			Window::player->move_left();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox1);
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if right tile is box2
	//		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box2))
	//		{
	//			Window::player->move_left();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox2);
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if player is INSIDE the box1
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox1))
	//		{
	//			Window::player->move_left();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::box1);
	//		}
	//		//Check if player is INSIDE the box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox2))
	//		{
	//			Window::player->move_left();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::box2);
	//		}
	//		//Check if left tile is a wall or ingredient
	//		else if ((gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items)) ||
	//			(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
	//				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
	//		{
	//			//check if left tile is ingredient
	//			if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items))
	//			{
	//				std::cout << "left ingredient\n";
	//				
	//				//check if tile on the left of ingredient is a wall
	//				if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
	//				{
	//					std::cout << "left ingredient wall\n";
	//					Window::player->stop();
	//				}
	//				//check if tile on the left of ingredient is a sinkhole
	//				else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::sinkhole))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

	//					//Set grid
	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::temp);
	//					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x -= tile_width;
	//							break;
	//						}
	//					}

	//					std::cout << "left ingredient sinkhole\n";
	//					Window::player->move_left();
	//				}
	//				//check if tile on the left of ingredient is another food
	//				else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items))
	//				{
	//					std::cout << "left ingredient ingredient\n";
	//					Window::player->stop();
	//				}
	//				//check if it's a box
	//				else if (gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box1) ||
	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box2))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::boxcover);

	//					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
	//					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, boxcover);
	//					SceneManager::loadIngr(Window::player->playerpos.x - (2 * tile_width + 5), Window::player->playerpos.y, Window::player->player_grid_pos.x - 2, Window::player->player_grid_pos.y, combine);

	//					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x -= tile_width + 5;
	//							break;
	//						}
	//					}

	//					win_amt++;

	//					std::cout << "left ingredient box\n";
	//					Window::player->move_left();
	//				}
	//				//Otherwise, it is a space
	//				else
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y]);

	//					gGrids[Window::player->player_grid_pos.x - 2][Window::player->player_grid_pos.y] = static_cast<int>(check);
	//					gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x -= tile_width;
	//							break;
	//						}
	//					}
	//					
	//					std::cout << "left ingredient space\n";
	//					Window::player->move_left();
	//				}
	//			}
	//			/*check wall*/
	//			else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
	//				gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
	//			{
	//				std::cout << "Wall on left" << std::endl;
	//				Window::player->stop();
	//			}
	//		}
	//		//check with box
	//		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box1) ||
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box2))
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);
	//			
	//			Window::player->move_left();
	//		}
	//		/*check with covered box*/
	//		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::boxcover))
	//		{
	//			std::cout << "Cover on left\n";
	//			Window::player->stop();
	//		}
	//		/*check for sinkhole*/
	//		else if (gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::sinkhole))
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "left sinkhole\n";
	//			Window::player->move_left();
	//		}
	//		else
	//		{
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "normal left" << std::endl;
	//			Window::player->move_left();
	//		}
	//	}
	//}

	//void Map::collision_check_right()
	//{
	//	if (!isStuck())
	//	{

	//		//Check if right tile is a box1
	//		if(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box1))
	//		{
	//			Window::player->move_right();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox1);
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if right tile is box2
	//		else if(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box2))
	//		{
	//			Window::player->move_right();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox2);
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if player is INSIDE the box1
	//		else if(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox1))
	//		{
	//			Window::player->move_right();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::box1);
	//		}
	//		//Check if player is INSIDE the box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox2))
	//		{
	//			Window::player->move_right();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x - 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::box2);
	//		}
	//		//Check if right tile is a wall or ingredient
	//		else if ((gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items)) ||
	//			(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
	//				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last)))
	//		{
	//			//check if right tile is ingredient
	//			if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items))
	//			{
	//				std::cout << "right ingredient\n";

	//				//check if tile on the right of ingredient is a wall
	//				if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) &&
	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
	//				{
	//					std::cout << "right ingredient wall\n";
	//					Window::player->stop();
	//				}
	//				//check if tile on the right of ingredient is a sinkhole
	//				else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::sinkhole))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::temp);
	//					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x += tile_width;
	//							break;
	//						}
	//					}

	//					std::cout << "right ingredient sinkhole\n";
	//					Window::player->move_right();
	//				}
	//				//check if tile on the right of ingredient is another food
	//				else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] > static_cast<int>(ingredients::ingredients) &&
	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] < static_cast<int>(ingredients::items))
	//				{
	//					std::cout << "right ingredient ingredient\n";
	//					Window::player->stop();
	//				}
	//				//check if it's a box
	//				else if (gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box1) ||
	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::box2))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::boxcover);
	//					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
	//					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, boxcover);
	//					SceneManager::loadIngr(Window::player->playerpos.x + (2 * tile_width), Window::player->playerpos.y, Window::player->player_grid_pos.x + 2, Window::player->player_grid_pos.y, combine);

	//					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x += tile_width;
	//							break;
	//						}
	//					}

	//					win_amt++;

	//					std::cout << "right ingredient box\n";
	//					Window::player->move_right();
	//				}
	//				//Otherwise, it is a space
	//				else
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y]);

	//					gGrids[Window::player->player_grid_pos.x + 2][Window::player->player_grid_pos.y] = static_cast<int>(check);
	//					gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.x += tile_width;
	//							break;
	//						}
	//					}

	//					std::cout << "right ingredient space\n";
	//					Window::player->move_right();
	//				}
	//			}
	//			/*check wall*/
	//			else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] > static_cast<int>(wall_type::first) ||
	//				gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] < static_cast<int>(wall_type::last))
	//			{
	//				std::cout << "Wall on right" << std::endl;
	//				Window::player->stop();
	//			}
	//		}
	//		/*check with covered box*/
	//		else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::boxcover))
	//		{
	//			std::cout << "Cover on right\n";
	//			Window::player->stop();
	//		}
	//		/*check for sinkhole*/
	//		else if (gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::sinkhole))
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "right sinkhole\n";
	//			Window::player->move_right();
	//		}
	//		//Just move
	//		else
	//		{
	//			gGrids[Window::player->player_grid_pos.x + 1][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "normal right" << std::endl;
	//			Window::player->move_right();
	//		}
	//	}
	//}

	//void Map::collision_check_down()
	//{
	//	if (!isStuck())
	//	{
	//		//Check if right tile is a box1
	//		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(ingredients::box1))
	//		{
	//			Window::player->move_down();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox1);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if right tile is box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(ingredients::box2))
	//		{
	//			Window::player->move_down();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox2);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if player is INSIDE the box1
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox1))
	//		{
	//			Window::player->move_down();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::box1);
	//		}
	//		//Check if player is INSIDE the box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox2))
	//		{
	//			Window::player->move_down();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::box2);
	//		}
	//		//Check if below tile is a wall or ingredient
	//		else if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(ingredients::ingredients) &&
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(ingredients::items)) ||
	//			(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) &&
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last)))
	//		{
	//			//check if below tile is ingredient
	//			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(ingredients::ingredients) &&
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(ingredients::items))
	//			{
	//				std::cout << "down ingredient\n";

	//				//check if tile below of ingredient is a wall
	//				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] > static_cast<int>(wall_type::first) &&
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] < static_cast<int>(wall_type::last))
	//				{
	//					std::cout << "down ingredient wall\n";
	//					Window::player->stop();
	//				}
	//				//check if tile below of ingredient is a sinkhole
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(ingredients::sinkhole))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(ingredients::temp);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y += tile_height;
	//							break;
	//						}
	//					}

	//					std::cout << "down ingredient sinkhole\n";
	//					Window::player->move_down();
	//				}
	//				//check if tile below of ingredient is another food
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] >= static_cast<int>(ingredients::ingredients) &&
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] <= static_cast<int>(ingredients::items))
	//				{
	//					std::cout << "down ingredient ingredient\n";
	//					Window::player->stop();
	//				}
	//				//check if it's a box
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(ingredients::box1) ||
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] == static_cast<int>(ingredients::box2))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(ingredients::boxcover);
	//					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
	//					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, boxcover);
	//					SceneManager::loadIngr(Window::player->playerpos.x, Window::player->playerpos.y + (2 * tile_height), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y + 2, combine);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y += tile_height;
	//							break;
	//						}
	//					}

	//					win_amt++;

	//					std::cout << "down ingredient box\n";
	//					Window::player->move_down();
	//				}
	//				//Otherwise, it is a space
	//				else
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1]);
	//					
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] = static_cast<int>(check);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y += tile_height;
	//							break;
	//						}
	//					}

	//					std::cout << "down ingredient space\n";
	//					Window::player->move_down();
	//				}
	//			}
	//			/*check wall*/
	//			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] > static_cast<int>(wall_type::first) ||
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] < static_cast<int>(wall_type::last))
	//			{
	//				std::cout << "Wall on down" << std::endl;
	//				Window::player->stop();
	//			}
	//		}
	//		/*check with covered box*/
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(ingredients::boxcover))
	//		{
	//			std::cout << "Cover on down\n";
	//			Window::player->stop();
	//		}
	//		/*check for sinkhole*/
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] == static_cast<int>(ingredients::sinkhole))
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "down sinkhole\n";
	//			Window::player->move_down();
	//		}
	//		//Just move
	//		else
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "normal down" << std::endl;
	//			Window::player->move_down();
	//		}
	//	}
	//}
	//
	//void Map::collision_check_up()
	//{
	//	if (!isStuck())
	//	{
	//		//Check if right tile is a box1
	//		if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(ingredients::box1))
	//		{
	//			Window::player->move_up();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox1);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if right tile is box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(ingredients::box2))
	//		{
	//			Window::player->move_up();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::inbox2);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::space);
	//		}
	//		//Check if player is INSIDE the box1
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox1))
	//		{
	//			Window::player->move_up();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::box1);
	//		}
	//		//Check if player is INSIDE the box2
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] == static_cast<int>(ingredients::inbox2))
	//		{
	//			Window::player->move_up();
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 1] = static_cast<int>(ingredients::box2);
	//		}
	//		//Check if above tile is a wall or ingredient
	//		else if ((gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(ingredients::ingredients) &&
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(ingredients::items)) ||
	//			(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) &&
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last)))
	//		{
	//			//check if above tile is ingredient
	//			if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(ingredients::ingredients) &&
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(ingredients::items))
	//			{
	//				std::cout << "up ingredient\n";

	//				//check if tile above of ingredient is a wall
	//				if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] > static_cast<int>(wall_type::first) &&
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] < static_cast<int>(wall_type::last))
	//				{
	//					std::cout << "up ingredient wall\n";
	//					Window::player->stop();
	//				}
	//				//check if tile above of ingredient is a sinkhole
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(ingredients::sinkhole))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(ingredients::temp);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y -= tile_height;
	//							break;
	//						}
	//					}

	//					std::cout << "up ingredient sinkhole\n";
	//					Window::player->move_up();
	//				}
	//				//check if tile above of ingredient is another food
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] > static_cast<int>(ingredients::ingredients) &&
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y + 2] < static_cast<int>(ingredients::items))
	//				{
	//					std::cout << "up ingredient ingredient\n";
	//					Window::player->stop();
	//				}
	//				//check if it's a box
	//				else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(ingredients::box1) ||
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] == static_cast<int>(ingredients::box2))
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(ingredients::boxcover);
	//					Sprite* boxcover = new Sprite("../textures/Tiles/Pods/Pod_Cover.png");
	//					std::pair<ingredients, Sprite*> combine = std::make_pair(ingredients::boxcover, boxcover);
	//					SceneManager::loadIngr(Window::player->playerpos.x, Window::player->playerpos.y - (2 * tile_height), Window::player->player_grid_pos.x, Window::player->player_grid_pos.y - 2, combine);

	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y -= tile_height;
	//							break;
	//						}
	//					}

	//					win_amt++;

	//					std::cout << "up ingredient box\n";
	//					Window::player->move_up();
	//				}
	//				//Otherwise, it is a space
	//				else
	//				{
	//					ingredients check = static_cast<ingredients>(gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1]);
	//					
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 2] = static_cast<int>(check);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::player);
	//					gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//					for (auto ingredient : SceneManager::ingredientcontainer)
	//					{
	//						if (ingredient.first == check)
	//						{
	//							ingredient.second->transformation.Position.y -= tile_height;
	//							break;
	//						}
	//					}

	//					std::cout << "up ingredient space\n";
	//					Window::player->move_up();
	//				}
	//			}
	//			/*check wall*/
	//			else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] > static_cast<int>(wall_type::first) ||
	//				gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] < static_cast<int>(wall_type::last))
	//			{
	//				std::cout << "Wall on up" << std::endl;
	//				Window::player->stop();
	//			}
	//		}
	//		/*check with covered box*/
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(ingredients::boxcover))
	//		{
	//			std::cout << "Cover on up\n";
	//			Window::player->stop();
	//		}
	//		/*check for sinkhole*/
	//		else if (gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] == static_cast<int>(ingredients::sinkhole))
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "up sinkhole\n";
	//			Window::player->move_up();
	//		}
	//		//Just move
	//		else
	//		{
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y - 1] = static_cast<int>(ingredients::player);
	//			gGrids[Window::player->player_grid_pos.x][Window::player->player_grid_pos.y] = static_cast<int>(ingredients::space);

	//			std::cout << "normal up" << std::endl;
	//			Window::player->move_up();
	//		}
	//	}
	//}

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
		SceneManager::drawIngr();
	}
	/********************************************
	 Return the value inside a cell that you click
	********************************************/
	int Map::GetValue(int col_x, int row_y)
	{
		return gGrids[col_x][row_y];
	}
	/********************************************
	 Set the value inside a cell that you click
	********************************************/
	void Map::SetValue(int col_x, int row_y, int value)
	{
		gGrids[col_x][row_y] = value;
	}
}  