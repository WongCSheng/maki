#pragma once
#ifndef Map_H_
#define Map_H_

enum class TileType
{
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	MAKI = 3,
	GOAL = 4
}

namespace Core
{
	class Map
	{
	public:
		Map();
		~Map();

		int initMap(const char* Filename);
		void DrawMap();

	private:
		static int Map_Height, Map_Width;
		static int** MapData;
		static int** BinaryData;
	};
}
#endif