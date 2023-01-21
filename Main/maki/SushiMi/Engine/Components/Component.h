/*
File:		 Component.h
Author:		 w.chongsheng@digipen.edu
Description: Header for ECS.cpp
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Core
{
	//Forward Declaration
	namespace Object
	{
		class GameObjectProperty;
	}

	enum class ComponentID
	{
		None = 0b0000'0000,
		Renderer = 0b0000'0010,
		Transform = 0b0000'0100,
		Camera = 0b0000'1000,
		Physics = 0b0001'0000,
		Collision = 0b0010'0000
	};

	class Component
	{
	public:
		friend class Object::GameObjectProperty;
		
		Component();
		virtual ~Component();

		// Function to initialize the component's owner when it is added to the entity
		virtual void Init() = 0;
		virtual void Serialise(const std::string name) = 0;
		virtual void Deserialise(const std::string name) = 0;
		Object::GameObjectProperty* GetOwner();
		void SetOwner(Object::GameObjectProperty* owner);
		void Reset(bool set);

		virtual bool IsActive();
		virtual void Activate();
		virtual void Deactivate();
		virtual void Remove();	// queue it for deletion

	protected:
		Object::GameObjectProperty* owner;
		bool active;
		bool add;	// queue for addition in runtime
		bool remove;	// queue for remove
		ComponentID ID;
	};

	class ComponentManager
	{
	public:
		ComponentManager() {};
		~ComponentManager() {};

		std::unordered_map<ComponentID, Component*> ComponentContainer;
	};
}

//class Entity
	//{
	//private:
	//	int id;
	//	bool active;

	//	std::vector<Component*> components;

	//	static int entity_count;

	//public:
	//	Entity();
	//	~Entity();

	//	// Compulsory component
	//	Transform* transform;

	//	const int GetID(void);
	//	bool IsActive(void);
	//	void Activate(void);
	//	void Deactivate(void);
	//	void AddChild(Entity* child);
	//	void DetachChild(Entity* child);
	//	void DetachChild(int number);
	//	void DetachAllChild(void);
	//	void DetachParent(void);

	//	template <typename T>
	//	T* AddComponent()
	//	{
	//		if (!GetComponent<T>())
	//		{
	//			T* comp = new T();
	//			components.push_back(comp);
	//			comp->Init(this);
	//			return comp;
	//		}
	//		return NULL;
	//	}

	//	template <typename T>
	//	T* GetComponent()
	//	{
	//		for (auto c : components)
	//		{
	//			if (typeid(*c) == typeid(T))
	//			{
	//				return reinterpret_cast<T*>(c);
	//			}
	//		}
	//		return NULL;
	//	}

	//	template <typename T>
	//	bool RemoveComponent()
	//	{
	//		for (auto& c : components)
	//		{
	//			if (typeid(*c) == typeid(T))
	//			{
	//				c->remove = true;
	//				return true;
	//			}
	//		}
	//		return false;
	//	}
	//	bool remove;
	//};







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