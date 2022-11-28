#include "Camera.h"
/*!
@file		Camera.cpp
@author		louishetong.wang@digipen.edu
@date		20/09/2022

@brief		Updated Camera that projects at 0,0 and is able to update its viewport.
*//*__________________________________________________________________________*/
Camera::Camera(int window_width, int window_height)
{
	projection = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);
}

Camera::~Camera()
{
}

glm::mat4 Camera::Get_Projection()
{
	return projection;
}

void Camera::Update_Viewport(int new_width, int new_height)
{
	projection = glm::ortho(0.0f, (float)new_width, (float)new_height, 0.0f, -1.0f, 1.0f);
}
