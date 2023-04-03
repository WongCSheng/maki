/*!*****************************************************************************

\file       Level11.cpp
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
	void Levels::Level11()
	{
		
		if (!Window::loaded)
		{
			Map::maki_city = 1; //set to maki city
			Window::player->current_anim = AnimationType::Idle;
			if (SceneManager::tilecontainer.size() > 0 || SceneManager::ingredientcontainer.size() > 0 || SceneManager::topcontainer.size() > 0 || SceneManager::in_sinkhole.size() > 0)
			{
				Map::ResetMap();
			}

			Window::resetQuest();

			Map::initMap("../TileMap/level11.txt");
			SceneManager::loadFader(0, 0);
			Map::LoadMap();
			Window::isQuestTab = false;
			Window::loaded = true;

			AudioManager.StopSFX();
			AudioManager.LoadSFX("Hard Floor Walking.ogg");
			AudioManager.LoadSFX("Hard Floor Walking_1.ogg");
			AudioManager.LoadSFX("Hard Floor Walking_2.ogg");
			AudioManager.LoadSFX("City Noise.ogg");
			AudioManager.LoadMusic("Forest_bgm.ogg");
			AudioManager.PlayMusic("Forest_bgm.ogg");
			AudioManager.SetMusicVolume(0.7f);
			AudioManager.PlaySFX("City Noise.ogg");
			AudioManager.SetAudioVolume(0.3f);
			AudioManager.PlayVoice("Idle_1.ogg");

			if (fin)
			{
				fin.close();
			}
			fin.open("../Data/Dialogue/lvl11_dialogue.txt");
			if (!fin)
			{
				std::cout << "Unable to open dialogue file!";
				return;
			}
			std::getline(fin, Window::realstring);

			Window::dialogue_style = static_cast<int>(Window::dialogue::MAKI_CITY);
			Window::curr_len = 0;

			SceneManager::num_dialogue_clicks = 2; //num of dialogue pages BEFORE game starts
			Window::isDialogue = true;
			CurrentIngredients = SceneManager::ingredientcontainer; //** IMPT : this line is needed for EACH level during loading
																	// for quest tab drawing of ingredients
			//also need dialogue after game end
		}

		//draw lv11 tile map
		Map::DrawMap();
		SceneManager::particle->timer += ((Get_Delta()));
		if (SceneManager::particle->timer < 1.0f)
		{
			SceneManager::particle->alpha -= ((Get_Delta()));
			SceneManager::draw_Particle(); //draw particle above map, but below quest and fade
		}
		
		//draw playerpos at lvl 11
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
		if (!Window::isWinCondition)
		{
			/*fading effect throughout*/
			SceneManager::fader->timer += ((Get_Delta()));
			if (SceneManager::fader->timer <= 2.5f)
			{
				SceneManager::fader->alpha += ((Get_Delta())/3);
			}
			if (SceneManager::fader->timer > 3.f)
			{
				SceneManager::fader->alpha -= ((Get_Delta())/3);
			}
			if (SceneManager::fader->timer > 5.5f)
			{
				SceneManager::fader->timer = 0.f;
				SceneManager::fader->alpha = 0.f;
			}
			SceneManager::drawFader(SceneManager::fader->alpha);
		}
		if (Map::isWin())
		{
			//std::cout << "you win!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			Window::isWinCondition = true;
		}
		if (Window::isWinCondition == true)
		{
			GameSave::LevelStatusContainer[12].isLevelClear = 1; //this is the last level so it will not unlock another level

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
					Window::isLevel11 = false; //unload curr level
					Window::finallevelclear = true; //start to trigger ending cutscene
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