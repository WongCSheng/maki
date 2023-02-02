#pragma once
#ifndef Map_H_
#define Map_H_
#include <string>

/*set a static grid first*/
#define GRID_COL 18
#define GRID_ROW 10

/*OLD:
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
	class Sprite;

	class Map
	{
	public:
		Map();
		~Map();

		static void initMap(std::string Filename);
		static void ResetMap();
		static int LoadMap();
		static void DrawMap();
		/*put here temporarily first*/
		static void collision_check_right();
		static void collision_check_left();
		static void collision_check_up();
		static void collision_check_down();
		static void print_map_to_console();
	
		static bool isStuck();
		static bool isWin();

		static inline int Map_Height, Map_Width;
		/*static int** MapData;
		static int** BinaryData;*/
		static int grid_row;
		static int grid_col;
		static float tile_width, tile_height;
		static int** gGrids;

		//texture names
		static inline Sprite* rice;
		static inline Sprite* nori;
		static inline Sprite* inari;
		static inline Sprite* box;
		static inline Sprite* boxcover;
		static inline Sprite* sinkhole;
		static inline Sprite* tile;
		static inline Sprite* tile2;
		static inline Sprite* tile3;
		static inline Sprite* tile4;
		static inline Sprite* tile5;
		static inline Sprite* tile6;
		static inline Sprite* tile7;
		static inline Sprite* tile8;
		static inline Sprite* tile9;
		static inline Sprite* tile10;
		static inline Sprite* tile11;
		static inline Sprite* tile12;
	};
}
#endif