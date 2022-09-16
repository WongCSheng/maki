#include "MainSystem.h"

MainSystem* MainSystem::instance = 0;

MainSystem::MainSystem()
{
	rendererSystem = new RendererSystem();
	systems.push_back(rendererSystem);

	cameraSystem = new CameraSystem();
	systems.push_back(cameraSystem);

	transformSystem = new TransformSystem();
	systems.push_back(transformSystem);

	lightSystem = new LightSystem();
	systems.push_back(lightSystem);
}

MainSystem::~MainSystem()
{
	for (auto &sys : systems)
	{
		if (sys != NULL)
		{
			delete sys;
			sys = NULL;
		}
	}
}

void MainSystem::RegisterComponents(const std::vector<Entity*> &entities)
{
	for (auto &sys : systems)
	{
		sys->RegisterComponents(entities);
	}
}

void MainSystem::Update(const double dt)
{
	//CheckForNewComponents();

	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->Update(dt);
	}
}

void MainSystem::CheckForNewComponents(void)
{
	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->CheckForNewComponents();
	}
}