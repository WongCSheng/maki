#pragma once

/*
File:		 ECS.h
Author:		 w.chongsheng@digipen.edu
Description: Header for ECS.cpp
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include <string>
#include <vector>

namespace Core
{
	class Transform;
	class Material;
	class Component;

	class Entity
	{
	private:
		int id;
		bool active;

		std::vector<Component*> components;

		static int entity_count;

	public:
		Entity();
		~Entity();

		// Compulsory component
		Transform* transform;

		const int GetID(void);
		bool IsActive(void);
		void Activate(void);
		void Deactivate(void);
		void AddChild(Entity* child);
		void DetachChild(Entity* child);
		void DetachChild(int number);
		void DetachAllChild(void);
		void DetachParent(void);

		template <typename T>
		T* AddComponent()
		{
			if (!GetComponent<T>())
			{
				T* comp = new T();
				components.push_back(comp);
				comp->Init(this);
				return comp;
			}
			return NULL;
		}

		template <typename T>
		T* GetComponent()
		{
			for (auto c : components)
			{
				if (typeid(*c) == typeid(T))
				{
					return reinterpret_cast<T*>(c);
				}
			}
			return NULL;
		}

		template <typename T>
		bool RemoveComponent()
		{
			for (auto& c : components)
			{
				if (typeid(*c) == typeid(T))
				{
					c->remove = true;
					return true;
				}
			}
			return false;
		}
		bool remove;
	};

	class Component
	{
	protected:
		Entity* owner;
		bool active;
		bool add;	// queue for addition in runtime
		bool remove;	// queue for remove

	public:
		Component();
		virtual ~Component() = 0;

		// Function to initialize the component's owner when it is added to the entity
		void Init(Entity* owner);
		Entity* Owner();

		bool IsActive();
		void Activate();
		void Deactivate();
		void Remove();	// queue it for deletion
	};
}

//#include "../Headers/STL_Header.h"
//
//#define Add true
//#define Remove false
//
////Forward Declaration
//class Entity;
//
//namespace Core
//{
//	enum class ComponentID
//	{
//		Gameobject = 0,
//		Physics,
//		Player,
//		Enemy
//	};
//
//	class Component
//	{
//	protected:
//		Entity* original;
//		uint16_t part_number;
//		bool active;
//
//	public:
//		Component();
//		//Component(Entity* init) : original(init) {}
//		~Component() {}
//
//		bool isActive();
//		void Activate();
//		void Deactivate();
//
//	};
//
//	class Entity
//	{
//	private:
//
//		bool active{};
//		std::pair<std::string, uint8_t> ID{}; // ID number
//		std::unordered_map<uint8_t, Component*> components; //Array of component pointers
//
//		unsigned int max_size{};
//
//	public:
//
//		Entity() {};
//		Entity(std::string str, int x) { ID = std::make_pair(str, x); }
//		~Entity();
//
//		//Getting ECS info
//		int getECSID();
//
//		std::string getECSName(Component* components);
//
//		void addComponents(Component* newcomp, std::pair<std::string, int> identity);
//
//		void removeComponents(std::pair<std::string, int> identity);
//
//	};
//}

#endif