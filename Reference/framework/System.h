#ifndef SYSTEM_H
#define SYSTEM_H

// Component System
#include <vector>
class Entity;
class System
{
public:
	System();
	virtual ~System() = 0;
	virtual void RegisterComponents(const std::vector<Entity*> &entities) = 0;
	virtual void Update(const double dt) = 0;
	virtual void CheckForNewComponents(void) = 0;
};

#endif