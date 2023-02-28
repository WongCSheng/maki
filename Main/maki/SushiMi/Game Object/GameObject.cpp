/*
GameObject.cpp
*/

#include "GameObject.h"
#include "../Engine/System/Scene/SceneManager.h"

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
			for (auto& x : ComponentContainer)
			{
				if (x.second) {
					delete x.second;
				}
			}
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
		
		/*template<typename T>*/
		Component* GameObjectProperty::GetComponent(Core::ComponentID ID)
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

		void GameObjectProperty::RemoveComponent(Core::ComponentID ID)
		{
			if (ComponentContainer[ID]) {
			delete ComponentContainer[ID];
			}
			ComponentContainer.erase(ID);
		}

		std::unordered_map<ComponentID, Component*> GameObjectProperty::GetComponentContainer()
		{
			return ComponentContainer;
		}

		//Game Object
		GameObject::GameObject()
		{
			characteristics = new GameObjectProperty;
		
		}

		GameObject::~GameObject()
		{
			delete characteristics;
		}

		void GameObject::Init()
		{
			
		} 


		GameObjectProperty* GameObject::GetObjectProperties()
		{
			return characteristics;
		}

		void GameObject::CreateIngredientProperty(ingredients ID)
		{
			Sprite* addsprite = new Sprite();
			collision* addcollision = new collision();

			
			characteristics->AddComponent(ComponentID::Sprite, addsprite);
			characteristics->AddComponent(ComponentID::Collision, addcollision);

			characteristics->SetID(static_cast<int>(ID));
			characteristics->SetIDName(static_cast<std::string>(ID));
		}
	}
} 