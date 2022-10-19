/*
GameObject.cpp
*/

#include "GameObject.h"

namespace Object
{
	GameObjectProperty::GameObjectProperty()
	{
		ObjectID.first = 0;
		ObjectID.second = "Nothing";
	}

	GameObjectProperty::~GameObjectProperty()
	{
		ComponentContainer.erase(ComponentContainer.begin(), ComponentContainer.end());
	}

	void GameObjectProperty::Init()
	{
		for (auto i : ComponentContainer)
		{
			i.second->SetOwner(this);
			i.second->Init();
		}
	}

	Core::Component* GameObjectProperty::GetComponent(Core::ComponentID ID)
	{
		return ComponentContainer[ID];
	}

	unsigned int GameObjectProperty::GetID()
	{
		return ObjectID.first;
	}

	void GameObjectProperty::SetID(unsigned int name)
	{
		ObjectID.first = name;
	}

	std::string GameObjectProperty::GetIDName()
	{
		return ObjectID.second;
	}

	void GameObjectProperty::SetIDName(std::string name)
	{
		ObjectID.second = name;
	}

	void GameObjectProperty::AddComponent(Core::ComponentID ID, Core::Component* comp)
	{
		ComponentContainer.insert({ ID, comp });
	}
}