/*!*****************************************************************************

\file       Level3.cpp
\author     Thea Sea (80% - Level State and loading)
\par        DP email: thea.sea@digipen.edu
\co-author	Louis He Tong Wang (10% - Transitions)
\co-author	Wong Chong Sheng (10% - AudioManager)
\date       03-01-2023

\brief
This program implements a Level State

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/

#include "LevelsHeader.h"
#include "../Headers/SceneManager.h"
#include "../Engine/Shaders/ShaderLibrary.h"
#include "../Engine/Audio/AudioEngine.h"
#include "../Engine/TileMap/Map.h"
#include "../Engine/Core/Core.h"
#include <string>


namespace Core
{
	extern std::ifstream fin;

	extern std::vector<Basket> CurrentIngredients; // retreive the curent level loaded ingredients
	void Levels::Level3()
	{
		if (!Window::loaded)
		{
			Map::region = 1;
			Map::maki_city = 0; //it is not maki city
			Window::player->current_anim = AnimationType::Idle;
			if (SceneManager::tilecontainer.size() > 0 || SceneManager::ingredientcontainer.size() > 0 || SceneManager::topcontainer.size() > 0 || SceneManager::in_sinkhole.size() > 0)
			{

				Map::ResetMap();
			}

			Window::resetQuest();

			Map::initMap("../TileMap/level3.txt");

			Map::LoadMap();
			Window::isQuestTab = false;
			Window::loaded = true;

			AudioManager.LoadSFX("Gravel_Drag-Movement_1.ogg");
			AudioManager.LoadMusic("BGM with Forest Day volume test.ogg");
			AudioManager.PlayMusic("BGM with Forest Day volume test.ogg");
			AudioManager.SetMusicVolume(0.5f);
			AudioManager.PlayVoice("Idle_1.ogg");

			if (fin)
			{
				fin.close();
			}
			fin.open("../Data/Dialogue/lvl3_dialogue.txt");
			if (!fin)
			{
				std::cout << "Unable to open dialogue file!";
				return;
			}
			std::getline(fin, Window::realstring);

			Window::dialogue_style = static_cast<int>(Window::dialogue::L3);
			Window::curr_len = 0;

			SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
			Window::isDialogue = true;
			CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																	// for quest tab drawing of ingredients
			//also need dialogue after game end
		}
		/*Fade out effect*/
		if (!Window::isWinCondition)
		{
			SceneManager::FadeOut();
			SceneManager::drawBlackOverlay();
		}
		//draw lv3 tile map
		Map::DrawMap();
		SceneManager::particle->timer += ((Get_Delta()));
		if (SceneManager::particle->timer < 1.0f)
		{
			SceneManager::particle->alpha -= ((Get_Delta()));
			SceneManager::draw_Particle(); //draw particle above map, but below quest and fade
		}

		//draw playerpos at lvl 3
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", Window::player->Transformation());

		//std::cout << "goals no " << Window::numQuests << std::endl;

		if (Window::gameIsPaused == false)
		{
			if (Window::isPlayerinSinkhole)
			{

			}
			else
				Window::player->draw(Get_Delta());

		}
		else if (Window::gameIsPaused == true)
		{
			Window::player->draw(0);

		}
		if (Map::isWin())
		{
			//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			Window::isWinCondition = true;
		}
		if (Window::isWinCondition == true)
		{
			SceneManager::rec->timer += Get_Delta();
			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

			if (Window::keystate_space)
			{
				SceneManager::spacepressed++;
				Window::keystate_space = false;

			}
			if (SceneManager::spacepressed == 1)
			{
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
			}
			SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
			SceneManager::drawWinOverlay();
			//stop all player controls
			//press button to undraw lv 3, and draw lv 4
			if (SceneManager::spacepressed == 2)
			{
				Window::isLevel3 = false; //unload curr level
				Window::isLevel4 = true; //load new level
				Window::isWinCondition = false; //reset win condition
				Window::loaded = false; //set to load
				Window::keystate_space = false;
				SceneManager::spacepressed = 0;
			}

		}
	}


}
