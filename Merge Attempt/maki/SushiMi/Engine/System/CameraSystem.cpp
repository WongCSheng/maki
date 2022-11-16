/*
File: CameraSystem.cpp
Author: w.chongsheng@digipen.edu
Description: Camera System that takes data stored in Camera2D.h and runs it with it's logic.
*/

#include "CameraSystem.h"
#include "../Camera/Camera2D.h"
#include "../Window/GameWindow.h"
#include "../Game Object/GameObject.h"

namespace Core
{
	CameraSystem::CameraSystem()
	{
	}


	CameraSystem::~CameraSystem()
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
	void CameraSystem::Init()
	{
		// assign address of object of type Object with name "Camera" in objects
		//pgo = &Object::objects.at("Camera");
		//pgo = &Object::GameObject();
	
	
		/*************************************************************************************************************************************/
		// assign address of object of type Object with name "Camera" in objects
		pgo = ptr->GetObjectProperties()->GetComponent(ComponentID::Camera);

		// compute camera window's aspect ratio
		glfwGetFramebufferSize(pWindow, &width, &height);
		ar = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

		// compute camera's up and right vectors
		up = { -sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };
		right = { cos(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)), sin(pgo->orientation.x / 180.f * static_cast<GLfloat>(PI)) };

		// at startup, camera must be initialized to free camera
		view_xform =
		{
			{1, 0, 0},
			{0, 1, 0},
			{-pgo->position.x, -pgo->position.y, 1} //negated because translate the view in the opposite direction of where we want cam to move
		};

		GLfloat cam_W = ar * GLHelper::height;
		GLfloat cam_H = ar * GLHelper::width;
		// compute other matrices
		camwin_to_ndc_xform =
		{
			{2 / cam_W, 0, 0},	// formula 2/W and 2/H
			{0, 2 / cam_H, 0},
			{0, 0, 1}
		};
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;	// World->View->NDC
	}

	void CameraSystem::Update(const double dt)
	{
		GLfloat dt = GLHelper::delta_time;
		ar = (GLfloat)GLHelper::width / (GLfloat)GLHelper::height;
		// update POV using keypress
		if (camtype_flag == GL_TRUE)
		{
			if (first_person_cam == GL_FALSE)
			{
				first_person_cam = GL_TRUE;
			}
			else if (first_person_cam == GL_TRUE)
			{
				first_person_cam = GL_FALSE;
			}
			camtype_flag = GL_FALSE;
		}

		if (first_person_cam == GL_TRUE)
		{
			view_xform = { {right.x,up.x,0.f},
							{right.y,up.y,0.f},
							{glm::dot(-glm::normalize(right),pgo->position),glm::dot(-glm::normalize(up),pgo->position),1.f}
			};
		}
		else if (first_person_cam == GL_FALSE)
		{
			view_xform = { {1.f,0.f,0.f},
							{0.f,1.f,0.f},
							{-pgo->position.x,-pgo->position.y,1.f}
			};
		}
		if (left_turn_flag == GL_TRUE)
		{
			pgo->orientation.x += pgo->orientation.y;
		}
		if (right_turn_flag == GL_TRUE)
		{
			pgo->orientation.x -= pgo->orientation.y;
		}
		// update camera's up and right vectors

		up = { -sinf(glm::radians(pgo->orientation.x)),
				cosf(glm::radians(pgo->orientation.x)) };

		right = { cosf(glm::radians(pgo->orientation.x)),
					sinf(glm::radians(pgo->orientation.x)) };

		// update camera's position
		if (move_flag == GL_TRUE)
		{
			//simple physics
			linear_speed = velocity * dt;
			velocity += acceleration * dt;
			pgo->position += (linear_speed * glm::normalize(up));//displace the camera
			vel2 = velocity;

		}

		if (decelerate == GL_TRUE) {
			//simple physics

			linear_speed = (vel2 * dt);
			vel2 -= 5.0f * (acceleration * dt);

			if (linear_speed > 0) //not reached 0
				pgo->position += (linear_speed * glm::normalize(up));//displace the camera
			else
				decelerate = GL_FALSE;

		}

		// implement camera's zoom effect (if required)
		if (zoom_flag == GL_TRUE)
		{
			if (height <= min_height)
			{
				height_chg_dir = 1;
			}
			else if (height >= max_height)
			{
				height_chg_dir = -1;
			}
			height += (height_chg_dir * height_chg_val);
		}


		// compute window-to-NDC transformation matrix
		// compute other matrices like rotation,scaling and translation
		camwin_to_ndc_xform = { {2.0f / (height * ar),0.f,0.f},
								{0.f,2.f / height,0.f},
								{0.f,0.f,1.f}
		};
		GLfloat radians = glm::radians(camera2d.pgo->orientation.x);

		glm::mat3 rot_mat
		{
				{cos(radians), sin(radians), 0},
				{-sin(radians), cos(radians), 0},
				{0, 0, 1}
		};

		glm::mat3 scale_mat
		{
			{camera2d.pgo->scaling.x, 0, 0},
			{0, camera2d.pgo->scaling.y, 0},
			{0, 0, 1}
		};

		glm::mat3 trans_mat
		{
			{1, 0, 0},
			{0, 1, 0},
			{camera2d.pgo->position.x, camera2d.pgo->position.y, 1}
		};
		glm::mat3 model_mtx = trans_mat * rot_mat * scale_mat;
		camera2d.pgo->mdl_to_ndc_xform = world_to_ndc_xform * model_mtx;
		// compute world-to-NDC transformation matrix
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

	//store gameobj into container of cameras
	void CameraSystem::AddinCameras(Object::GameObject* gameobj)
	{
	
		/*for (int i = 0; i < camera.size(); ++i)
		{
			camera[i]
		}*/
	
		if (gameobj->GetObjectProperties()->GetComponent(ComponentID::Camera))
		{
		
			cameras.push_back(gameobj->GetObjectProperties()->GetComponent(ComponentID::Camera));
		}
	}

	void CameraSystem::Update(const double dt)
	{	
		/*for (int i = 0; i < cameras.size(); ++i)
		{
			cameras[i]->update(Upfront::Window::win);
		}*/
	}

	void CameraSystem::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}
}