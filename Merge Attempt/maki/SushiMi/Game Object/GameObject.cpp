/*
GameObject.cpp
*/

#include "GameObject.h"

namespace Core
{
	namespace Object
	{
		//Game Object Properties
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
			for (auto&& i : ComponentContainer)
			{
				i.second->SetOwner(this);
				i.second->Init();
			}
		}
		
		template<typename T>
<<<<<<< Updated upstream:Merge Attempt/maki/SushiMi/Game Object/GameObject.cpp
		T* GameObjectProperty::GetComponent(Core::ComponentID ID)
=======
		T GameObjectProperty::GetComponent(Core::ComponentID ID)
>>>>>>> Stashed changes:Main/maki/SushiMi/Game Object/GameObject.cpp
		{
			if (ComponentContainer.find(ID) == ComponentContainer.end())
			{
				std::cout << "No such Component" << std::endl;

				return nullptr;
			}
			
			//T ptr = ComponentContainer[ID];
			
			return ComponentContainer[ID];
		}

		std::unordered_map<ComponentID, Component*> GameObjectProperty::GetComponentContainer()
		{
			return ComponentContainer;
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

		template<typename T>
		void GameObjectProperty::AddComponent(Core::ComponentID ID, Core::Component* comp)
		{
			ComponentContainer.insert({ ID, std::make_unique<Component>(comp) });
		}

		void GameObjectProperty::RemoveComponent(Core::ComponentID ID)
		{
			ComponentContainer.erase(ID);
		}

		//Game Object
		GameObject::GameObject()
		{
			characteristics = new GameObjectProperty;
		}

		GameObject::~GameObject()
		{
		}

		void GameObject::Init()
		{
			
		}

		GameObjectProperty* GameObject::GetObjectProperties()
		{
			return characteristics;
		}
	}
}