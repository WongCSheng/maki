#include "Map.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>


namespace Core
{
	Core::Map::Map()
	{
	}

	Core::Map::~Map()
	{
	}

	int Core::Map::initMap(const char* Filename)
	{
		//Open File using ifstream
		std::fstream fin(Filename);
		if(!fin)
		{
			std::cout << "Unable to open csv file!";
			return 0;
		}

		return 0;
	}

	void Core::Map::DrawMap()
	{
	}
}