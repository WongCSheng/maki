//******************************************************************************/
/*!
\file		CameraSystem.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Camera systems.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

#include "CameraSystem.h"
#include "../Camera/Camera2D.h"
//#include "../Window/GameWindow.h"

Core::CameraSystem::CameraSystem()
{
}


Core::CameraSystem::~CameraSystem()
{
}

//void Core::CameraSystem::Init(const std::vector<Entity*>& entities)
//{
//	for (int i = 0; i < entities.size(); ++i)
//	{
//		Camera2D* camera = entities[i]->GetComponent<Camera2D>();
//		if (camera != NULL)
//		{
//			cameras.push_back(camera);
//		}
//	}
//}

void Core::CameraSystem::Init()
{

}

void Core::CameraSystem::Update(const double dt)
{
	/*for (int i = 0; i < cameras.size(); ++i)
	{
		cameras[i]->update(Upfront::Window::win);
	}*/
}

void Core::CameraSystem::RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer)
{

}