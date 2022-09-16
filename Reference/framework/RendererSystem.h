#ifndef RENDERER_SYSTEM_H
#define RENDERER_SYSTEM_H

#include "System.h"
#include <vector>

class MeshFilter;
class Material;
class MeshRenderer;
class RendererSystem : public System
{
public:
	RendererSystem();
	virtual ~RendererSystem();
	virtual void RegisterComponents(const std::vector<Entity*> &entities);
	virtual void Update(const double dt);
	virtual void CheckForNewComponents(void);

private:
	std::vector<MeshFilter*> meshFilterComponents;
	std::vector<Material*> materialComponents;
	std::vector<MeshRenderer*> meshRendererComponents;
};

#endif