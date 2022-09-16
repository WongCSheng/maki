#include "Component.h"


Component::Component() :
active(true),
remove(false)
{
}


Component::~Component()
{
}

void Component::Init(Entity* owner)
{
	this->owner = owner;
}

Entity* Component::Owner(void)
{
	return owner;
}

bool Component::IsActive()
{
	return active;
}

void Component::Activate()
{
	active = true;
}

void Component::Deactivate()
{
	active = false;
}

void Component::Remove()
{
	remove = true;
}