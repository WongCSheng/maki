/*!*****************************************************************************

\file       LevelSelect.cpp
\author     Aurelia Chong
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

namespace Core
{
	std::map<int, icons> level_icons;
	std::string node_level_txt;

	void init_LevelSelectMap()
	{
		//13 nodes positions
		std::array<gfxVector2, 13> nodePos
		{
		{ 
			{390, 100},
			{322, 270},
			{470, 265},
			{550, 160},
			{680, 185},

			{940, 185},
			{1175, 180},
			{1340, 260},
			{1400, 468},
			{1237, 530},

			{1055, 450},
			{883, 554},
			{865, 765}
			}
		};

		for(int i = 0; i < 13; i++)
		{
			icons icon;
			icon.isCrown = false;
			icon.isLocked = true;
			icon.node_pos = nodePos[i];
			icon.isStar = true;
			level_icons.insert({ i,icon });
		}
	}

	void Levels::LevelSelect()
	{

		int screenwidth = 0, screenheight = 0;
		glfwGetWindowSize(Window::window_ptr, &screenwidth, &screenheight);

		for (int i = 0; i < static_cast<int>(GameSave::LevelStatusContainer.size()); i++)
		{
			//level clear is true -> crown draw
			if(GameSave::LevelStatusContainer[i].isLevelClear == 1 )
			{
				level_icons.at(i).isCrown = true;
			}

			//level
			if (GameSave::LevelStatusContainer[i].isUnlocked == 1)
			{
				level_icons.at(i).isLocked = false;
			}

			if (GameSave::LevelStatusContainer[i].isQuestClear == 1)
			{
				level_icons.at(i).isStar = true;
			}
			else
				level_icons.at(i).isStar = false;
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
