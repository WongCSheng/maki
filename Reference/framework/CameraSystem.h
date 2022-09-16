#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "System.h"

#include <vector>

using std::vector;

class FirstPersonCamera;
class CameraSystem :
	public System
{
public:
	CameraSystem();
	virtual ~CameraSystem();
	virtual void RegisterComponents(const std::vector<Entity*> &entities);
	virtual void Update(const double dt);
	virtual void CheckForNewComponents(void);

private:
	vector<FirstPersonCamera*> cameras;
};

#endif