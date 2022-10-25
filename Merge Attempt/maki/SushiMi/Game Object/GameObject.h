#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/Components/Component.h"
#include "../Engine/Factory/Factory.h"

namespace Core
{
	namespace Object
	{
		class GameObjectProperty
		{
		public:
			friend class ObjectFactory;
			friend class Component;

			void Init();

			Component* GetComponent(ComponentID ID);

			unsigned int GetID();
			void SetID(unsigned int name);

			std::string GetIDName();
			void SetIDName(std::string name);

			void AddComponent(ComponentID ID, Component* comp);

			void RemoveComponent(ComponentID ID);

		private:
			GameObjectProperty();
			~GameObjectProperty();

			std::unordered_map<ComponentID, Component*> ComponentContainer;

			std::pair<unsigned int, std::string> ObjectID; //Unsigned int is the component tags, String is the name of the object
		};
	}
}