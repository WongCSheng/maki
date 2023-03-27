/*
File:		Map.h
@author		louishetong.wang@digipen.edu 40%
co-Author:  thea.sea@digipen.edu 15%
co-Author:  Aurelia (fei.x@digipen.edu) 30%
co-Author:  w.chongsheng@digipen.edu  15%

Description:
*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#pragma once
#ifndef Map_H_
#define Map_H_
#include <string>
#include <vector>
#include "../../src/Window.h"

#include "../Headers/SceneManager.h"

namespace Core
{
	class Sprite;

	class Map
	{
	public:
		Map();
		~Map();
		static inline std::map<std::pair<grid_number, wall_type>, Sprite*> levelWinConditions;
		static void initMap(std::string Filename);
		static void saveEditedMap(std::string Filename);
		static void ResetMap();
		static void RestartMap();
		static int LoadMap();
		static void LoadAMap();
		static void LoadWMap();
		static void LoadGMap();
		static void DrawMap();
		static int GetValue(double col_x, double row_y);
		static void SetValue(double col_x, double row_y, int value);
		/*put here temporarily first*/
		static void collision_check_right();
		static void collision_check_left();
		static void collision_check_up();
		static void collision_check_down();
		static void print_map_to_console();
	
		static bool isStuck();
		static bool isWin();

		static std::string IngredientToString(grid_number ingredient);
		static std::string PodToString(wall_type pod);

		static std::map<std::string, Sprite*> loadedIngredients;	//  all loaded ingredients for the level
		static std::map< std::string, Sprite*> loadedBoxes;			//	all loaded boxes for the level
		static inline std::pair<int, int> windowDim;				//	level current window dimension

		//static inline Core::grid_number box_stepped_on;
		static inline int Map_Height, Map_Width;
		/*static int** MapData;
		static int** BinaryData;*/
		static inline int max_grid_cols_x;
		static inline int max_grid_rows_y;
		static float tile_width, tile_height;
		static int** gGrids;

		static inline Sprite* soya;
		static inline Sprite* rice;
		static inline Sprite* salmon;
		static inline Sprite* wasabi;
		static inline Sprite* tea;

		static int** wGrids;
		static int** aGrids;
		static int** RestartGrids;

		//static std::map<std::pair<grid_number, wall_type>, std::string> levelWinConditionsalt;
		
		static int CorrectCombination;

		static inline bool maki_city;

		static inline bool ingr_corner_stuck;


		/*map changing*/
		/*
		* this is to change textures depending on the region of the map
		* 1 = Rice Plain
		* 2 = Village
		* 3 = Fishing
		* 4 = Maki City
		*/
		static inline int region;
	};
	/*extern std::vector<std::pair<grid_number, wall_type>> levelWinConditions;*/
	

}
#endif