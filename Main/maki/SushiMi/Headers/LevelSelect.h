#pragma once
/*!*****************************************************************************

\file       LevelSelect.h
\author     Aurelia Chong
\par        DP email: fei.x@digipen.edu
\date       03-29-2023

\brief
This program contains headers for the functions in LevelSelect.cpp
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/
#include "../Headers/SceneManager.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Factory/Factory.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include "../src/Window.h"

namespace Core
{
	struct icons
	{
		bool isCrown;
		bool isLocked;
		bool isStar;
		gfxVector2 node_pos;
	};

	 void init_LevelSelectMap();
	
	
}
