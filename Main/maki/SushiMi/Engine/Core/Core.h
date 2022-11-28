#pragma once

/*
File:		 Core.h
Author:		 w.chongsheng@digipen.edu
Description: Header for Core.cpp
*/

#ifndef CORE_H_
#define CORE_H_

#include "../System/SystemFrame.h"
#include "..//System/Renderer.h"
#include "../System/Transformer.h"
#include "../System//CameraSystem.h"
#include "../System/PhysicSystem.h"
#include "../Engine/Input/Input.h"

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
		ObjectFactory* objfactory;
		Input* inputsystem;

		Renderer* renderer;
		Transformer* transformer;
		CameraSystem* cameraSystem;
		PhysicSystem* physicssystem;
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