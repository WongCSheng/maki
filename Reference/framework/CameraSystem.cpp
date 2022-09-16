#include "CameraSystem.h"
#include "Entity.h"
#include "FirstPersonCamera.h"

CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}

void CameraSystem::RegisterComponents(const std::vector<Entity*> &entities)
{
	for (int i = 0; i < entities.size(); ++i)
	{
		FirstPersonCamera* camera = entities[i]->GetComponent<FirstPersonCamera>();
		if (camera != NULL)
		{
			cameras.push_back(camera);
		}
	}
}

void CameraSystem::Update(const double dt)
{
	for (int i = 0; i < cameras.size(); ++i)
	{
		/*if (cameras[i]->remove)
		{
			delete cameras[i];
			cameras[i] = NULL;
			--i;
			continue;
		}*/
		cameras[i]->Update(dt);
	}
}

void CameraSystem::CheckForNewComponents(void)
{

}