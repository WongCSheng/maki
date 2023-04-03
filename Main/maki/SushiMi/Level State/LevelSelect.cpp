/*!*****************************************************************************

\file       LevelSelect.cpp
\author     Aurelia Chong (100%)
\par        DP email: fei.x@digipen.edu
\date       03-29-2023

\brief
This program implements level selection map

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

*******************************************************************************/

#include "../Headers/LevelSelect.h"
#include "LevelsHeader.h"
#include <array>
#include "Engine/Font/Font.h"
#include <iostream>
#include "../src/Window.h"
#include "Headers/Main.h"


namespace Core
{
	//map that stores all level selection map icons
	std::map<int, icons> level_icons;

	//string that stores the level names
	std::string node_level_txt;

	/*		 Function to initialise map items		*/
	void init_LevelSelectMap()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		//initialise 13 nodes positions
		std::array<gfxVector2, 13> nodePos
		{
		{

			{ ( (float)390 /(float)1920 )* (float)screenwidth , ( (float)100/ (float)1080 ) * (float)screenheight}, //nodepos1
			{ ((float)322 / (float)1920) * (float)screenwidth , ((float)270 / (float)1080) * (float)screenheight}, //nodepos2
			{ ((float)470 / (float)1920) * (float)screenwidth , ((float)265 / (float)1080) * (float)screenheight}, //nodepos3
			{ ((float)550 / (float)1920) * (float)screenwidth , ((float)160 / (float)1080) * (float)screenheight}, //nodepos4
			{ ((float)680 / (float)1920) * (float)screenwidth , ((float)185 / (float)1080) * (float)screenheight}, //nodepos5
			{ ((float)940 / (float)1920) * (float)screenwidth , ((float)185 / (float)1080) * (float)screenheight}, //nodepos6
			{ ((float)1175 / (float)1920) * (float)screenwidth , ((float)180 / (float)1080) * (float)screenheight}, //nodepos7
			{ ((float)1340 / (float)1920) * (float)screenwidth , ((float)260 / (float)1080) * (float)screenheight}, //nodepos8
			{ ((float)1400 / (float)1920) * (float)screenwidth , ((float)500 / (float)1080) * (float)screenheight}, //nodepos9
			{ ((float)1237 / (float)1920) * (float)screenwidth , ((float)550 / (float)1080) * (float)screenheight}, //nodepos10
			{ ((float)1055 / (float)1920) * (float)screenwidth , ((float)450 / (float)1080) * (float)screenheight}, //nodepos11
			{ ((float)883 / (float)1920) * (float)screenwidth , ((float)570 / (float)1080) * (float)screenheight}, //nodepos12
			{ ((float)865 / (float)1920) * (float)screenwidth , ((float)815 / (float)1080) * (float)screenheight}, //nodepos13

			}
		};
		for(int i = 0; i < 13; i++)
		{
			icons icon;
			icon.isCrown = false;
			icon.isLocked = true;
			icon.node_pos = nodePos[i];
			icon.isStar = false;
			level_icons.insert({ i,icon });
		}
	}

	/*		Draws level Select Map		*/
	void Levels::LevelSelect()
	{
		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);
		for (int i = 0; i < static_cast<int>(GameSave::LevelStatusContainer.size()); i++)
		{
			//level clear is true -> draw crown 
			if(GameSave::LevelStatusContainer[i].isLevelClear == 1 )
			{
				level_icons.at(i).isCrown = true;
			}

			if(GameSave::LevelStatusContainer[i].isQuestClear == 1)
			{
				level_icons.at(i).isStar = true;
			}

			//level unlocked true -> remove lock
			if (GameSave::LevelStatusContainer[i].isUnlocked == 1)
			{
				level_icons.at(i).isLocked = false;
			}
		}

		for (int i = 0; i < level_icons.size();  i++)
		{
			// for node
			Core::Object::GameObject* nodeObj = CoreSystem->objfactory->ObjectContainer.at("map_node");
			Sprite* nodeSprite = nodeObj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
			nodeSprite->transformation.Position = { level_icons.at(i).node_pos.x ,level_icons.at(i).node_pos.y };
			nodeSprite->transformation.Scale = { 85,85 };
			Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
			Shaders->Textured_Shader()->Send_Mat4("model_matrx", nodeSprite->transformation.Get());
			nodeSprite->draw();
			

			if(level_icons.at(i).isLocked)
			{
				//for lock
				Core::Object::GameObject* lockObj = CoreSystem->objfactory->ObjectContainer.at("map_lock");
				Sprite* lockSprite = lockObj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
				lockSprite->transformation.Position = { level_icons.at(i).node_pos.x ,level_icons.at(i).node_pos.y };
				lockSprite->transformation.Scale = { 85,85 };
				Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", lockSprite->transformation.Get());
				lockSprite->draw();
			}
			else
			{	//for level texts
				if(i == 0 || i == 1)
				{
					node_level_txt = "T" + std::to_string(i+1); //offset text level value
				}
				else
				{
					node_level_txt = "L" + std::to_string(i-1); //offset text level value
				}
				glm::vec3 color_txt{ 0.f, 0.f, 0.f };
				Shaders->Font_Shader()->use();
				Font::RenderText(*Shaders, node_level_txt  , (level_icons.at(i).node_pos.x + 25), ( screenheight - level_icons.at(i).node_pos.y -50 ), .55f, color_txt, 1.f);
				Shaders->Textured_Shader()->use();
				//if a level is unlocked, it can respond to mouse input
				if (Window::mouseLeft)
				{
					double xpos = 0, ypos = 0;
					glfwGetCursorPos(Window::window_ptr, &xpos, &ypos);
					double nodewidth = 85;

					//check against the node
					if (xpos > level_icons.at(i).node_pos.x && ypos > level_icons.at(i).node_pos.y && xpos < level_icons.at(i).node_pos.x + nodewidth && ypos < level_icons.at(i).node_pos.y + nodewidth)
					{
						Window::isLevelSelection = false;
						switch (i)
						{
						case 0:
							Window::isTut1 = true;
							break;
						case 1:
							Window::isTut2 = true;
							break;
						case 2:
							Window::isLevel1 = true;
							break;
						case 3:
							Window::isLevel2 = true;
							break;
						case 4:
							Window::isLevel3 = true;
							break;
						case 5:
							Window::isLevel4 = true;
							break;
						case 6:
							Window::isLevel5 = true;
							break;
						case 7:
							Window::isLevel6 = true;
							break;
						case 8:
							Window::isLevel7 = true;
							break;
						case 9:
							Window::isLevel8 = true;
							break;
						case 10:
							Window::isLevel9 = true;
							break;
						case 11:
							Window::isLevel10 = true;
							break;
						case 12:
							Window::isLevel11 = true;
							break;

						default:
							break;
						}
					}
				}
			}

			if (level_icons.at(i).isCrown)
			{
				//for crown
				Core::Object::GameObject* crownObj = CoreSystem->objfactory->ObjectContainer.at("map_crown");
				Sprite* crownSprite = crownObj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
				crownSprite->transformation.Position = { level_icons.at(i).node_pos.x + 6 ,level_icons.at(i).node_pos.y - 35 };
				crownSprite->transformation.Scale = { 70,70 };
				Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", crownSprite->transformation.Get());
				crownSprite->draw();
			}

			if (level_icons.at(i).isStar)
			{
				//for crown
				Core::Object::GameObject* starObj = CoreSystem->objfactory->ObjectContainer.at("map_star");
				Sprite* starSprite = starObj->GetObjectProperties()->GetComponent<Sprite>(ComponentID::Renderer);
				starSprite->transformation.Position = { level_icons.at(i).node_pos.x + 8 ,level_icons.at(i).node_pos.y +40 };
				starSprite->transformation.Scale = { 70,70 };
				Shaders->Textured_Shader()->Send_Alpha("alpha", 1.f);
				Shaders->Textured_Shader()->Send_Mat4("model_matrx", starSprite->transformation.Get());
				starSprite->draw();
			}

		}

	}
}
