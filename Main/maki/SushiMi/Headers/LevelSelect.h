#pragma once

#include "../Headers/SceneManager.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Factory/Factory.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include "../src/Window.h"
#include "Headers/Main.h"
#include  "../Engine/GameSave/GameSave.h"
#include <string>
namespace Core
{
	struct icons
	{
		//Sprite* node;  //black or yellow node
		//Sprite* state; //crown or lock
		bool isCrown;
		bool isLocked;
		bool isStar;
		gfxVector2 node_pos;
	};

	//std::map<int, icons> level_icons;

	 void init_LevelSelectMap();
	
	
}
