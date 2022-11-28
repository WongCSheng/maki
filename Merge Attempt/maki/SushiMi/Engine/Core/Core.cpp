/*
File:		Core.cpp
Author:		w.chongsheng@digipen.edu
Description: This file contains the MainSystem which runs all the subsystems in the engine.
			 Subsystems consists of Rendering, Transforming, Camera and Factory.
*/

#include "Core.h"
#include "../Engine/Components/Physics/Physics.h"

namespace Core
{

	MainSystem* Core::MainSystem::instance = 0; //Singleton of MainSystem.

	/*
		Constructor for MainSystem.
	*/
	MainSystem::MainSystem()
	{
		renderer = std::make_unique<Renderer>(Renderer());
		systems.emplace_back(std::move(renderer));

		cameraSystem = std::make_unique<CameraSystem>(CameraSystem());
		systems.emplace_back(std::move(cameraSystem));

		transformer = std::make_unique<Transformer>(Transformer());
		systems.emplace_back(std::move(transformer));

		physicssystem = std::make_unique<PhysicSystem>(PhysicSystem());
		systems.emplace_back(std::move(physicssystem));
	}

	/*
		Destructor for MainSystem.
	*/
	MainSystem::~MainSystem()
	{
		for (auto& sys : systems)
		{
			if (sys != nullptr)
			{
				delete sys;
				sys = nullptr;
			}
		}
	}

	/*
		Create Instance of MainSystem.
	*/

	MainSystem& Core::MainSystem::Instance()
	{
		if (instance != 0)
		{
			return *instance;
		}

		instance = new MainSystem();
		return *instance;
	}

	/*
		Register Components to each SubSystem.
	*/

	void MainSystem::Init()
	{
		for (auto& sys : systems)
		{
			sys->Init();
		}
	}

	/*
		Runs the update() function for each SubSystem.
	*/

	void MainSystem::Update(const double dt)
	{
		for (int i = 0; i < systems.size(); ++i)
		{
			systems[i]->Update(dt);
		}

		Object::
	}

	/*
		Checks for new Components in each SubSystem.
	*/

	void MainSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{
		for (int i = 0; i < systems.size(); ++i)
		{
			systems[i]->RegisterComponent(ObjectContainer);
		}
	}

	void MainSystem::endprocess()
	{
		//should delete all pointers
		//renderer.get_deleter();
	}

}
//Core::Core::MainSystem::MainSystem()
//{
//}
//
//Core::Core::MainSystem::~MainSystem()
//{
//	for (SystemFrame* i : SubSystems)
//	{
//		if (i != NULL)
//		{
//			delete i;
//			i = NULL;
//		}
//
//		if (elem_pos > 0)
//		{
//			--elem_pos;
//		}
//	}
//}
//
//void Core::Core::MainSystem::Sys_Init()
//{
//	elem_pos = 0;
//}
//
//void Core::Core::MainSystem::update(const float dt)
//{
//
//}
//
//void Core::Core::MainSystem::RegisterEntities(std::array<Entity, 1000> entities)
//{
//	for (SystemFrame* i : SubSystems)
//	{
//		i->RegisterEntities(entities);
//	}
//}
