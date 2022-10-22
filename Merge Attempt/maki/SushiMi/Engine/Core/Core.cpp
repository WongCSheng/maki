/*
File:		Core.cpp
Author:		w.chongsheng@digipen.edu
Description: This file contains the MainSystem which runs all the subsystems in the engine.
			 Subsystems consists of Rendering, Transforming, Camera and Factory.
*/

#include "Core.h"

Core::MainSystem* Core::MainSystem::instance = 0; //Singleton of MainSystem.

/*
	Constructor for MainSystem.
*/
Core::MainSystem::MainSystem()
{
	renderer = new Renderer();
	systems.push_back(renderer);

	cameraSystem = new CameraSystem();
	systems.push_back(cameraSystem);

	transformer = new Transformer();
	systems.push_back(transformer);
}

/*
	Destructor for MainSystem.
*/
Core::MainSystem::~MainSystem()
{
	for (auto& sys : systems)
	{
		if (sys != NULL)
		{
			delete sys;
			sys = NULL;
		}
	}
}

/*
	Create Instance of MainSystem.
*/

Core::MainSystem& Core::MainSystem::Instance()
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

void Core::MainSystem::Init()
{
	for (auto& sys : systems)
	{
		sys->Init();
	}
}

/*
	Runs the update() function for each SubSystem.
*/

void Core::MainSystem::Update(const double dt)
{
	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->Update(dt);
	}
}

/*
	Checks for new Components in each SubSystem.
*/

void Core::MainSystem::Exit()
{
	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->CheckForNewComponents();
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
