#pragma once
<<<<<<< HEAD

=======
/*!
\file		Core.h
\author 	Wong Chong Sheng
\par    	w.chongsheng@digipen.edu
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		Header for Core.cpp
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
>>>>>>> M3-submission-branch
/*
File:		 Core.h
Author:		 w.chongsheng@digipen.edu
Description: Header for Core.cpp
*/
<<<<<<< HEAD
=======
/******************************************************************************/
>>>>>>> M3-submission-branch

#ifndef CORE_H_
#define CORE_H_

<<<<<<< HEAD
#include "../System/SystemFrame.h"
#include "..//System/Renderer.h"
#include "../System/Transformer.h"
<<<<<<<< HEAD:Main/maki/SushiMi/Engine/Core/Core.h
#include "../System//CameraSystem.h"
#include "../System/PhysicSystem.h"
========
#include "../System/CameraSystem.h"
#include "../System/PhysicsSystem.h"
>>>>>>>> M3-submission-branch:Graphics/maki/SushiMi/Engine/Core/Core.h
#include "../Engine/Input/Input.h"
=======
#include "../System/Renderer.h"
#include "../System/Transformer.h"
#include "../System//CameraSystem.h"
#include "../System/PhysicSystem.h"
#include "../Engine/Input/Input.h"
#include "../Editors/LevelEditor.h"
#include "../System/TextureSystem.h"
>>>>>>> M3-submission-branch

#include <vector>

namespace Core
{
	class MainSystem : public SystemFrame
	{
	private:
		/*MainSystem();
		virtual ~MainSystem();*/

		//static MainSystem* instance;

		std::vector<SystemFrame*> systems;

	public:
		//static MainSystem& Instance();

		MainSystem();
		virtual ~MainSystem();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		void clear();
<<<<<<< HEAD
<<<<<<<< HEAD:Main/maki/SushiMi/Engine/Core/Core.h
========

>>>>>>>> M3-submission-branch:Graphics/maki/SushiMi/Engine/Core/Core.h
		ObjectFactory* objfactory;
		Input* inputsystem;

		Renderer* renderer;
		Transformer* transformer;
		CameraSystem* cameraSystem;
		PhysicSystem* physicssystem;
=======
		static ObjectFactory* objfactory;
		Input* inputsystem;

		void AccessObjFactory();

		Transformer* transformer;
		CameraSystem* cameraSystem;
		Renderer* rendersystem;
		std::unique_ptr<Window> windowsystem;
		TextureSystem* texturesystem;
		std::unique_ptr<Editor::LevelEditor> leveleditorsystem;
	

>>>>>>> M3-submission-branch
	};
}

//#include "../Headers/STL_Header.h"
//#include "../Engine/System/SystemFrame.h"
//
////Forward declaration
//class Entity;
//class Component;
//class Renderer;
//class Transformer;
//class CameraSystem;
//
//namespace Core
//{
//	class MainSystem : public SystemFrame
//	{
//	private:
//		MainSystem();
//		~MainSystem();
//		
//		static MainSystem* inst; //Instance of System
//		float PrevTime{}; //Previous Time for dt
//		bool active{}; //Active status
//
//		std::array<SystemFrame*, 1000> SubSystems; //Container for Systems
//	
//	public:
//
//		void Sys_Init();
//
//		void RegisterEntities(const std::array<Entity, 1000> entities);
//
//		void update(const float dt);
//
//		std::vector<std::string> current_components(const std::array<Entity, 1000> &entities);
//
//		void AddComponents(const Component components);
//
//		void AddEntities(const Entity entities);
//
//		void AddSystem(SystemFrame* system);
//		void DeleteSystem();
//
//		Renderer* rendersys;
//		Transformer* tranformsys;
//		CameraSystem* camerasys;
//	};
//}

#endif