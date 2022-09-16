#include "LightSystem.h"
#include "Entity.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "Transform.h"

LightSystem::LightSystem() :
updateTimer(1.f)
{
}


LightSystem::~LightSystem()
{
}

void LightSystem::RegisterComponents(const std::vector<Entity*> &entities)
{
	for (unsigned i = 0; i < entities.size(); ++i)
	{
		PointLight* pointLight = entities[i]->GetComponent<PointLight>();
		if (pointLight != NULL)
		{
			pointLights.push_back(pointLight);
		}
		DirectionLight* dLight = entities[i]->GetComponent<DirectionLight>();
		if (dLight != NULL)
		{
			directionLights.push_back(dLight);
		}
	}
}

void LightSystem::Update(const double dt)
{
	updateTimer += (float)dt;

	if (updateTimer > 0.5f)
	{
		updateTimer = 0.f;
		for (unsigned i = 0; i < pointLights.size(); ++i)
		{
			if (pointLights[i]->remove)
			{
				delete pointLights[i];
				pointLights[i] = NULL;
				--i;
				continue;
			}
			pointLights[i]->position = pointLights[i]->owner->transform->worldposition;
		}

		directionLights[0]->Update(dt);
	}
}

void LightSystem::CheckForNewComponents(void)
{

}

vector<PointLight*>& LightSystem::GetPointLights(void)
{
	return pointLights;
}

DirectionLight* LightSystem::GetDirLight(void)
{
	return directionLights[0];
}