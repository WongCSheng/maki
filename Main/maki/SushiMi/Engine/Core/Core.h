#pragma once
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
/*
File:		 Core.h
Author:		 w.chongsheng@digipen.edu
Description: Header for Core.cpp
*/
/******************************************************************************/

#ifndef CORE_H_
#define CORE_H_

#include "../System/Renderer.h"
#include "../System/Transformer.h"
#include "../System//CameraSystem.h"
#include "../System/PhysicSystem.h"
#include "../Engine/Input/Input.h"
#include "../Editors/LevelEditor.h"
#include "../System/TextureSystem.h"

#include <vector>

namespace Core
{
	enum class SystemID
	{
		Transformer = 0,
		CameraSystem,
		Renderer,
		Windows,
		TextureSystem,
		LevelEditor,
		AudioSystem,
		Factory
	};

	class MainSystem : public SystemFrame
	{
	private:
		/*MainSystem();
		virtual ~MainSystem();*/

		//static MainSystem* instance;

		Transformer* transformer;
		CameraSystem* cameraSystem;
		Renderer* rendersystem;
		Window* windowsystem;
		TextureSystem* texturesystem;
		Editor::LevelEditor* leveleditorsystem;

		std::unordered_map<SystemID, SystemFrame*> systems;

		//std::unordered_map<SystemID, std::unique_ptr<SystemFrame>> systems;

	public:
		//static MainSystem& Instance();

		MainSystem();
		virtual ~MainSystem();

		void Init();
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		void clear();
		static ObjectFactory* objfactory;
		static AssetsManager* assManager;
		Input* inputsystem;

		void AddtoObjFactory();

		template<typename T>
		T* AccessSystem(SystemID wantsys)
		{
			return static_cast<T*>(systems[wantsys]);
		}
	};
}

#endif