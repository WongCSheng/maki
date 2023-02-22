#pragma once
#ifndef Map_H_
#define Map_H_
#include <string>
#include <vector>

#include "../Headers/SceneManager.h"
/*set a static grid first*/
#define GRID_COL 18
#define GRID_ROW 10


namespace Core
{
	class Sprite;

	class Map
	{
	public:
		Map();
		~Map();

		static void initMap(std::string Filename);
		static void saveEditedMap(std::string Filename);
		static void ResetMap();
		static int LoadMap();
		static void DrawMap();
		static int GetValue(int col_x, int row_y);
		static void SetValue(int col_x, int row_y, int value);
		/*put here temporarily first*/
		static void collision_check_right();
		static void collision_check_left();
		static void collision_check_up();
		static void collision_check_down();
		static void print_map_to_console();
	
		static bool isStuck();
		static bool isWin();
		
		static void fadeToBlack();
		//static inline Core::grid_number box_stepped_on;
		static inline int Map_Height, Map_Width;
		/*static int** MapData;
		static int** BinaryData;*/
		static inline int grid_row;
		static inline int grid_col;
		static float tile_width, tile_height;
		static int** gGrids;
		

		static std::map<std::pair<grid_number, wall_type>, std::string> levelWinConditionsalt;
		
		static int CorrectCombination;
	};
	extern int width, height;
	extern std::vector<std::pair<grid_number, wall_type>> levelWinConditions;
	extern int grid_row;
	extern int grid_col;
}
#endif