#pragma once

#ifndef CAMERASYSTEM_H_
#define CAMERASYSTEM_H_

#include "../Headers/STL_Header.h"
#include "SystemFrame.h"
#include "../Entity/ECS.h"

//Forward Declaration

namespace Core
{
	class Camera2D;
	class CameraSystem : public ::SystemFrame
	{
	public:
		CameraSystem();
		virtual ~CameraSystem();
		virtual void RegisterComponents(const Core::Component comp);
		virtual void Update(const double dt);
		virtual void CheckForNewComponents(void);

	private:
		std::vector<Camera2D*> cameras;
	};
}

#endif