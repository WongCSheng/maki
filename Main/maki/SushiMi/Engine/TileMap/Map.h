#pragma once
#ifndef Map_H_
#define Map_H_

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