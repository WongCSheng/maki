#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H

#include "System.h"

#include <vector>

using std::vector;

class PointLight;
class DirectionLight;
class LightSystem :
	public System
{
public:
	LightSystem();
	virtual ~LightSystem();
	virtual void RegisterComponents(const std::vector<Entity*> &entities);
	virtual void Update(const double dt);
	virtual void CheckForNewComponents(void);

	vector<PointLight*>& GetPointLights(void);
	DirectionLight* GetDirLight(void);

private:
	vector<PointLight*> pointLights;
	vector<DirectionLight*> directionLights;
	float updateTimer;
};

#endif