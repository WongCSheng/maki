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
		void Init();
		void AddinCameras(Object::GameObject* gameobj);
		void Update(const double dt);
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		/*-----------------------Variables declaration------------------------------------------*/
		//bool for physics
		bool accelerate{ false };
		bool decelerate{ false };

		// Keyboard button press flags:
		bool camtype_flag{ false }; // button V
		bool zoom_flag{ false }; // button Z
		bool left_turn_flag{ false }; // button H
		bool right_turn_flag{ false }; // button K
		bool move_flag{ false }; // button W
		//static Camera2D camera2d;


	private:
		std::vector<Component*> cameras;
	};
}

#endif