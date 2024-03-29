/*!*****************************************************************************

\file       Level9.cpp
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
#include "../Headers/Main.h"
#include <string>


namespace Core
{
	extern std::ifstream fin;

	extern std::vector<Basket> CurrentIngredients; // retreive the curent level loaded ingredients
	void Levels::Level9()
	{
		Map::region = 3;

		if (!Window::loaded)
		{
			Map::maki_city = 0; //it is not maki city
			Window::player->current_anim = AnimationType::Idle;
			if (SceneManager::tilecontainer.size() > 0 || SceneManager::ingredientcontainer.size() > 0 || SceneManager::topcontainer.size() > 0 || SceneManager::in_sinkhole.size() > 0)
			{
				Map::ResetMap();
			}

			Window::resetQuest();

			Map::initMap("../TileMap/level9.txt");

			Map::LoadMap();
			Window::isQuestTab = false;
			Window::loaded = true;

			AudioManager.StopSFX();
			AudioManager.LoadSFX("Hard Floor Walking.ogg");
			AudioManager.LoadSFX("Hard Floor Walking_1.ogg");
			AudioManager.LoadSFX("Hard Floor Walking_2.ogg");
			AudioManager.LoadSFX("Water_Light Waves_Loop.ogg");
			AudioManager.LoadMusic("Fishing_Village.ogg");
			AudioManager.PlayMusic("Fishing_Village.ogg");
			AudioManager.SetMusicVolume(0.7f);
			AudioManager.PlaySFX("Water_Light Waves_Loop.ogg");
			AudioManager.SetAudioVolume(0.3f);
			AudioManager.PlayVoice("Idle_1.ogg");

			if (fin)
			{
				fin.close();
			}
			fin.open("../Data/Dialogue/lvl9_dialogue.txt");
			if (!fin)
			{
				std::cout << "Unable to open dialogue file!";
				return;
			}
			std::getline(fin, Window::realstring);




			Window::dialogue_style = static_cast<int>(Window::dialogue::L9);
			Window::curr_len = 0;

			SceneManager::num_dialogue_clicks = 1; //num of dialogue pages BEFORE game starts
			Window::isDialogue = true;
			CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																	// for quest tab drawing of ingredients
			//also need dialogue after game end
		}

		//draw lv9 tile map
		Map::DrawMap();
		SceneManager::particle->timer += ((Get_Delta()));
		if (SceneManager::particle->timer < 1.0f)
		{
			SceneManager::particle->alpha -= ((Get_Delta()));
			SceneManager::draw_Particle(); //draw particle above map, but below quest and fade
		}

		//draw playerpos at lvl 9
		Shaders->Textured_Shader()->Send_Mat4("model_matrx", Window::player->Transformation());

		//std::cout << "goals no " << Window::numQuests << std::endl;

		if (Window::gameIsPaused == false)
		{
			
			Window::player->draw(Get_Delta());

		}
		else if (Window::gameIsPaused == true)
		{
			Window::player->draw(0);

		}
		/*Fade out effect*/
		if (!Window::isWinCondition)
		{
			SceneManager::rec->timer = 0.f;
			SceneManager::FadeOut();
			SceneManager::drawBlackOverlay();
			Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
		}
		if (Map::isWin())
		{
			//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			Window::isWinCondition = true;
		}
		if (Window::isWinCondition == true)
		{
			GameSave::LevelStatusContainer[10].isLevelClear = 1;
			GameSave::LevelStatusContainer[11].isUnlocked = 1; //set next level unlocked
			GameSave::LevelStatusContainer[10].isQuestClear = 1;


			int screenwidth = 0, screenheight = 0;
			glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

			if (Window::keystate_space)
			{
				SceneManager::spacepressed++;
				Window::keystate_space = false;

			}
			if (SceneManager::spacepressed >= 1)
			{
				SceneManager::rec->timer += Get_Delta();
				/*Fade in function, comes together*/
				SceneManager::FadeIn();
				SceneManager::drawBlackOverlay();
				if (SceneManager::rec->timer > 3.f)
				{
					Window::isLevel9 = false; //unload curr level
					Window::isLevel10 = true; //load new level
					Window::isWinCondition = false; //reset win condition
					Window::loaded = false; //set to load
					SceneManager::spacepressed = 0;
				}
			}
			SceneManager::loadWinOverlay(static_cast<int>(screenwidth * 0.25), static_cast<int>(screenheight * 0.25));
			SceneManager::drawWinOverlay();
		}
	}
}