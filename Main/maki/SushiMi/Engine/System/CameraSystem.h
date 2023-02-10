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
<<<<<<< HEAD
=======

		static CameraSystem* GetInstance() {
			static CameraSystem camerasystem;
			return &camerasystem;
		}

>>>>>>> M3-submission-branch
		virtual void Init();
		void AddinCameras(Object::GameObject* gameobj);
		virtual void Update(const double dt);
		virtual void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
		/*-----------------------Variables declaration------------------------------------------*/
		
		//Object::GameObject* pgo;//Object* pgo; // pointer to game obj that embeds the camera
		//gfxVector2 right, up;

		////additional parameters for camera
		//GLint height{ 1000 };
		//GLfloat ar;

		//gfxMatrix3 camwin_to_ndc_xform;
		//gfxMatrix3 world_to_ndc_xform;
		//gfxMatrix3 view_xform;

		////window parameters
		//GLint min_height{ 500 }, max_height{ 720 };
		//// height is increasing if 1 and decreasing if -1
		//GLint height_chg_dir{ 1 };
		//// increments by which window height is changed per Z key press
		//GLint height_chg_val{ 5 };

		//// camera speed when button U is pressed
		//GLfloat linear_speed{ 2.f };
		//GLfloat velocity{ 500.f };
		//GLfloat vel2{ 500.f };
		//GLfloat acceleration{ 100.f };
		//GLfloat deceleration{ 0.0f };

		////bool for physics
		//GLboolean decelerate{ GL_FALSE };

		//// Keyboard button press flags:
		//GLboolean camtype_flag{ GL_FALSE }; // button V
		//GLboolean zoom_flag{ GL_FALSE }; // button Z
		//GLboolean left_turn_flag{ GL_FALSE }; // button H
		//GLboolean right_turn_flag{ GL_FALSE }; // button K
		//GLboolean move_flag{ GL_FALSE }; // button W
		//static Camera2D camera2d;


	private:
		std::vector<Component*> cameras;
<<<<<<< HEAD
=======

		//static CameraSystem* instance;
>>>>>>> M3-submission-branch
	};
}

#endif