//******************************************************************************/
/*!
\file		CameraSystem.h
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Header for Camera systems.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/
#pragma once

#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

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
		virtual void Update(const double dt);
		virtual void RegisterComponent(std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer);

	private:
		std::vector<Camera2D*> cameras;
	};
}

#endif