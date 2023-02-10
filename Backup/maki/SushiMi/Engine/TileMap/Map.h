#pragma once
#ifndef Map_H_
#define Map_H_
#include <string>

enum class TileType
{
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	MAKI = 3,
	GOAL = 4
};

/*set a static grid first*/
#define GRID_COL 30
#define GRID_ROW 30

namespace Core
{
	class Sprite;

	class Map
	{
	public:
		Map();
		~Map();

		static int initMap(std::string Filename);
		static void DrawMap();
		static void ResetMap();
		/*put here temporarily first*/
		static void collision_check_right();
		static void collision_check_left();
		static void collision_check_up();
		static void collision_check_down();
	


		static bool isStuck();
		static bool isWin();

		static inline int Map_Height, Map_Width;
		static int** MapData;
		static int** BinaryData;
		static int grid_row;
		static int grid_col;
		static float tile_width, tile_height;
		static int gGrids[GRID_ROW][GRID_COL];
	};
}
#endif