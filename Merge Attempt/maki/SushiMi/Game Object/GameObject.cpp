/*
GameObject.cpp
*/

#include "GameObject.h"

namespace Object
{
	GameObjectProperty::GameObjectProperty()
	{
		ID = ObjectID::None;
	}

	GameObjectProperty::~GameObjectProperty()
	{
		ComponentContainer.erase(ComponentContainer.begin(), ComponentContainer.end());
	}

	void GameObjectProperty::Init()
	{
		for (auto& i : ComponentContainer)
		{
			i.second->SetOwner(this);
			i.second->Init();
		}
	}

	void GameObjectProperty::AddToDestroyList()
	{
		
	}

	Core::Component* GameObjectProperty::GetComponent(ObjectID ID)
	{
		return ComponentContainer[ID];
	}

	ObjectID GameObjectProperty::GetID()
	{
		return ID;
	}

	std::string GameObjectProperty::GetIDName()
	{
		
	}

	void AddComponent(ObjectID ID, Core::Component* comp)
	{
		
	}
}