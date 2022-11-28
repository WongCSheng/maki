#pragma once
#include <../glm/glm/glm.hpp>
#include <../glm/glm/gtc/matrix_transform.hpp>

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
};

static std::unique_ptr<Camera> camera;