#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include "System.h"
#include "RendererSystem.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "LightSystem.h"

#include <vector>

using std::vector;

class MainSystem :
	public System
{
public:
	static inline MainSystem& Instance(void)
	{
		if (instance != 0)
		{
			return *instance;
		}

		instance = new MainSystem();
		return *instance;
	}

	virtual void RegisterComponents(const std::vector<Entity*> &entities);
	virtual void Update(const double dt);
	virtual void CheckForNewComponents(void);

	RendererSystem *rendererSystem;
	TransformSystem *transformSystem;
	CameraSystem *cameraSystem;
	LightSystem *lightSystem;

private:
	MainSystem();
	virtual ~MainSystem();

	static MainSystem* instance;

	vector<System*> systems;
};

#endif