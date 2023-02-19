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

#include "../System/Graphics/Renderer.h"
#include "../System/Transform/Transformer.h"
#include "../System/Camera/CameraSystem.h"
#include "../System/Physics/PhysicSystem.h"
#include "../Engine/Input/Input.h"
#include "../Editors/LevelEditor.h"
#include "../System/Graphics/TextureSystem.h"

#include <vector>

namespace Core
{
	class MainSystem : public SystemFrame
	{
	private:
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
		static ObjectFactory* objfactory;
		Input* inputsystem;

		void AccessObjFactory();

		Transformer* transformer;
		CameraSystem* cameraSystem;
		Renderer* rendersystem;
		std::unique_ptr<Window> windowsystem;
		TextureSystem* texturesystem;
		std::unique_ptr<Editor::LevelEditor> leveleditorsystem;
		SceneManager* scnsystem;
	

	};
}

#endif