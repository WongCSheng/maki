#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/Components/Component.h"
#include "../Engine/Factory/Factory.h"
#include "../Engine/System/Linked List/LinkedList.h"

namespace Core
{
	namespace Object
	{
		/*
		Characteristics of a Game Object.
		*/
		class GameObjectProperty
		{
		public:
			//friend class Component;
			friend class GameObject;

			void Init();

			template<typename T>
<<<<<<< Updated upstream:Merge Attempt/maki/SushiMi/Game Object/GameObject.h
			T* GetComponent(ComponentID ID);
=======
			T GetComponent(ComponentID ID);

			std::unordered_map<ComponentID, Component*> GetComponentContainer();
>>>>>>> Stashed changes:Main/maki/SushiMi/Game Object/GameObject.h

			unsigned int GetID();
			void SetID(unsigned int name);

			std::string GetIDName();
			void SetIDName(std::string name);

			template<typename T>
			void AddComponent(ComponentID ID, Component* comp);

			void RemoveComponent(ComponentID ID);

		private:
			GameObjectProperty();
			~GameObjectProperty();

			std::unordered_map<ComponentID, std::unique_ptr<Component>> ComponentContainer;

			std::pair<unsigned int, std::string> ObjectID; //Unsigned int is the component tags, String is the name of the object
		};


		/*
		Game Object itself
		*/
		class GameObject
		{
		private:
			GameObjectProperty* characteristics; //use unique_ptr

		protected:
			virtual ~GameObject();

		public:
			friend class ObjectFactory;
			
			//LinkedList<Component*> HeadOfList;
			
			GameObject();

			virtual void Init();

			GameObjectProperty* GetObjectProperties();
		};
	}
}