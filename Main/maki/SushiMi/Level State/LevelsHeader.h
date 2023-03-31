/*!*****************************************************************************

\file       LevelsHeader.h
\author     Thea Sea, thea.sea, 2102348 (100%)
\par        DP email: thea.sea@digipen.edu
\date       03-01-2023

\brief
This program implements a Level State Header

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/

#pragma once
#include "../Engine/GameSave/GameSave.h"
namespace Core
{
	class Levels
	{
	public:
		static void Tutorial1();
		static void Tutorial2();
		static void Level1();
		static void Level2();
		static void Level3();
		static void Level4();
		static void Level5();
		static void Level6();
		static void Level7();
		static void Level8();
		static void Level9();
		static void Level10();
		static void Level11();
		static void TestLevel();

		GameSave L1;
		
		//std::ifstream fin;
		//std::vector<Basket> CurrentIngredients; // retreive the curent level loaded ingredients
	};
}
