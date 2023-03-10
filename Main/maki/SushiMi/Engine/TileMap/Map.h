#pragma once
#ifndef Map_H_
#define Map_H_
#include <string>
#include <vector>

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
		
		static void fadeToBlack();
		static std::string EnumToString(grid_number ingredient);

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

		static std::map<std::pair<grid_number, wall_type>, std::string> levelWinConditionsalt;
		
		static int CorrectCombination;
	};
	/*extern std::vector<std::pair<grid_number, wall_type>> levelWinConditions;*/
	

}
#endif