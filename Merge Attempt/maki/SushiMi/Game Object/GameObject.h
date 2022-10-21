#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/Entity/ECS.h"
#include "../Engine/Factory/Factory.h"

namespace Core
{
	namespace Object
	{
		class GameObjectProperty
		{
		public:
			friend class Core::ObjectFactory;
			friend class Core::Component;

			void Init();

			Core::Component* GetComponent(Core::ComponentID ID);

			unsigned int GetID();
			void SetID(unsigned int name);

			std::string GetIDName();
			void SetIDName(std::string name);

			void AddComponent(Core::ComponentID ID, Core::Component* comp);

			void RemoveComponent(Core::ComponentID ID);

		private:
			GameObjectProperty();
			~GameObjectProperty();

			std::unordered_map<Core::ComponentID, Core::Component*> ComponentContainer;

			std::pair<unsigned int, std::string> ObjectID;
		};
	}
}