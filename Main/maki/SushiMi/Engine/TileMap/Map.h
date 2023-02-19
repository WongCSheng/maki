#pragma once

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "../Engine/System/SystemFrame.h"

/*set a static grid first*/
#define GRID_COL 18
#define GRID_ROW 10

namespace Core
{
	class Sprite;

	class Map : public SystemFrame
	{
	public:
		Map();
		~Map();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

		static void initMap(std::string Filename);
		static void ResetMap();
		static void LoadMap();
		static void DrawMap();
		static int GetValue(int col_x, int row_y);
		static void SetValue(int col_x, int row_y, int value);
		/*put here temporarily first*/
		/*static void collision_check_right();
		static void collision_check_left();
		static void collision_check_up();
		static void collision_check_down();*/
		static void print_map_to_console();
	
		static bool isWin();

		static inline int grid_row;
		static inline int grid_col;
		static float tile_width, tile_height;

		static int tile_counter;

		static int** gGrids;
		static short** cGrids;
		static short** rGrids;
		static short** pGrids;
	};
}