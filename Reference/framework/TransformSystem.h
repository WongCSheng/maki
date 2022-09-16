#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include <vector>
#include "System.h"

using std::vector;

class Transform;
class Entity;
class TransformSystem :
	public System
{
public:
	TransformSystem();
	virtual ~TransformSystem();
	virtual void RegisterComponents(const std::vector<Entity*> &entities);
	virtual void Update(const double dt);
	virtual void CheckForNewComponents(void);
	void UpdateTransformation(Transform* Transform);

private:
	void RemoveFromTree(Transform* transform);
	vector<Transform*> transforms;
	Entity* root;
};

#endif