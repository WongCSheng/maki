/*!
\file		Core.cpp
\author 	Wong Chong Sheng
\par    	w.chongsheng@digipen.edu
\author 	Aurelia Chong
\par    	email: fei.x@digipen.edu
\date   	16 Nov 2022
\brief		This file contains the MainSystem which runs all the subsystems in the engine.
/*
File:		Core.cpp
Author:		w.chongsheng@digipen.edu
Description: This file contains the MainSystem which runs all the subsystems in the engine.
			 Subsystems consists of Rendering, Transforming, Camera and Factory.
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Core.h"
#include "../Engine/Components/Physics/Physics.h"
#include "../../src/Window.h"

//MainSystem* MainSystem::instance = 0; //Singleton of MainSystem.

/*
	Constructor for MainSystem.
*/
namespace Core
{
	MainSystem::MainSystem()
	{
		cameraSystem = CameraSystem::GetInstance();
		systems.insert({ SystemID::CameraSystem, cameraSystem });
		// -
		transformer = Transformer::GetInstance();
		systems.insert({ SystemID::Transformer, transformer });

		windowsystem = Window::GetInstance(800, 600);
		systems.insert({ SystemID::Windows, windowsystem });
		// -
		rendersystem = Renderer::GetInstance();
		systems.insert({ SystemID::Renderer, rendersystem });

		texturesystem = TextureSystem::GetInstance();
		systems.insert({ SystemID::TextureSystem, texturesystem });
#if defined(DEBUG) | defined(_DEBUG)
		leveleditorsystem = Editor::LevelEditor::GetInstance();
		systems.insert({ SystemID::LevelEditor, leveleditorsystem });
#endif


		objfactory = new ObjectFactory();

		inputsystem = new Input();
	}

	/*
		Destructor for MainSystem.
	*/
	MainSystem::~MainSystem()
	{
		/*for (auto& sys : systems)
		{
			if (sys != NULL)
			{
				delete sys;
				sys = NULL;
			}
		}*/
		//To shift into cleanup
		
		//glfwSetKeyCallback(GLHelper::ptr_window, Input::key_callback);

		//delete windowsystem;
	}

	/*
		Create Instance of MainSystem.
	*/

	//MainSystem& MainSystem::Instance()
	//{
	//	if (instance != 0)
	//	{
	//		return *instance;
	//	}
	//
	//	instance = new MainSystem();
	//	return *instance;
	//}

	/*
		Register Components to each SubSystem.
	*/

	void MainSystem::Init()
	{
		for (auto sys = systems.begin(); sys != systems.end(); sys++)
		{
			sys->second->Init();

		}
	}

	/*
		Runs the update() function for each SubSystem.
	*/

	void MainSystem::Update(const double dt)
	{
		for (auto sys = systems.begin(); sys != systems.end(); sys++)
		{
			sys->second->Update(dt);
		}

		int mousestate = glfwGetMouseButton(Window::window_ptr, MOUSE_BUTTON_LEFT);

		gfxVector2 mousePos = inputsystem->GetMouse(Window::window_ptr, mousestate);
	}

	/*
		Checks for new Components in each SubSystem.
	*/

	void MainSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{
		for (auto sys = systems.begin(); sys != systems.end(); sys++)
		{
			sys->second->RegisterComponent(ObjectContainer);
		}

	}

	void MainSystem::clear()
	{
		for (auto& i : objfactory->ObjectContainer)
		{
			objfactory->AddtoDestroyList(i.second);
		}

		objfactory->DestroyEverything();

		TextureSystem::GetInstance()->Shutdown();

		delete objfactory;

		delete inputsystem;
	}
	void MainSystem::AccessObjFactory()
	{
		Editor::LevelEditor::AddToFactory(objfactory);
	}
}
