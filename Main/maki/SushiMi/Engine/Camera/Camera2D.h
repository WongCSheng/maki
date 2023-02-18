#pragma once
/*!
@file		Camera.h
@author		louishetong.wang@digipen.edu
@date		20/09/2022

@brief		Updated Camera that projects at 0,0 and is able to update its viewport.
*//*__________________________________________________________________________*/
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <memory>
//using namespace std;

class Camera
{
public:
	Camera(int window_width, int window_height);
	~Camera();

	glm::mat4 Get_Projection();

	void Update_Viewport(int new_width, int new_height);

	glm::mat4 projection;

private:
	int width, height;
};