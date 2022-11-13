/*
File: CameraSystem.h
Author: w.chongsheng@digipen.edu
Description: Header for CameraSystem.cpp
*/

#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#include "../Headers/STL_Header.h"
#include "SystemFrame.h"
#include "../Components/Component.h"


namespace Core
{
	//Forward Declaration
	class Camera2D;

	class CameraSystem : public SystemFrame
	{
	public:
		CameraSystem();
		virtual ~CameraSystem();
		virtual void Init();
		void AddinCameras(Object::GameObject* gameobj);
		virtual void Update(const double dt);
		virtual void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);

	private:
		std::vector<Component*> cameras;
	};
}

#endif