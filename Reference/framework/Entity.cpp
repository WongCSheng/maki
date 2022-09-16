#include "Entity.h"
#include "Transform.h"
#include "Component.h"
#include "Material.h"

int Entity::entity_count = 0;

Entity::Entity() :
active(true),
remove(false)
{
	transform = AddComponent<Transform>();
	//AddComponent<Material>();
	id = entity_count;
	++entity_count;
}


Entity::~Entity()
{
	transform->children.clear();
	transform->parent->Owner()->DetachChild(this);
	transform->parent = NULL;
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i] != NULL)
		{
			delete components[i];
			components[i] = NULL;
		}
	}
}

const int Entity::GetID(void)
{
	return id;
}

bool Entity::IsActive(void)
{
	return active;
}

void Entity::Activate(void)
{
	active = true;
}

void Entity::Deactivate(void)
{
	active = false;
}

void Entity::AddChild(Entity* child)
{
	//children.push_back(child);
	//child->parent = this;
	transform->children.push_back(child->transform);
	//transform->parent = transform;
	child->transform->parent = transform;
}

void Entity::DetachChild(Entity* child)
{
	for (unsigned i = 0; i < transform->children.size(); ++i)
	{
		if (transform->children[i] == child->transform)
		{
			transform->children[i]->parent = NULL;
			transform->children.erase(transform->children.begin() + i);
			break;
		}
	}
}

void Entity::DetachChild(int number)
{
	transform->children[number]->parent = NULL;
	transform->children.erase(transform->children.begin() + number);
}

void Entity::DetachAllChild(void)
{
	for (unsigned i = 0; i < transform->children.size(); ++i)
	{
		transform->children[i]->parent = NULL;
	}

	transform->children.clear();
}

void Entity::DetachParent(void)
{
	transform->parent = NULL;
}

void Entity::Delete(void)
{
	/*remove = true;
	for (int i = 0; i < transform->children.size(); ++i)
	{
		transform->children[i]->Owner()->Delete();
	}
	for (auto &c : components)
	{
		c->Remove();
	}*/
}
