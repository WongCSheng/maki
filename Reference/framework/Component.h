#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;
class Component
{
public:
	Component();
	virtual ~Component() = 0;

	// Function to initialize the component's owner when it is added to the entity
	void Init(Entity* owner);
	Entity* Owner(void);

	bool IsActive(void);
	void Activate();
	void Deactivate();
	void Remove();	// queue it for deletion

protected:
	Entity* owner;
	bool active;
	bool add;	// queue for addition in runtime
	bool remove;	// queue for remove
};

#endif