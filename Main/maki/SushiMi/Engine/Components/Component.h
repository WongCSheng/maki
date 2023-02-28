/*
File:		 Component.h
Author:		 w.chongsheng@digipen.edu
Description: Header for ECS.cpp
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "../Headers/RapidJSON_Header.h"


namespace Core
{
	//Forward Declaration
	namespace Object
	{
		class GameObjectProperty;
	}

	enum class ComponentID : std::uint8_t
	{
		None = 0,
		Sprite,
		Transform,
		Camera,
		Physics,
		Collision,
		Texture
	};

	class Component
	{
	public:
		friend class Object::GameObjectProperty;
		
		Component();
		virtual ~Component() = 0;

		// Function to initialize the component's owner when it is added to the entity
		virtual void Init() = 0;
		//virtual void Serialize(const std::string name)  = 0 ;
		//virtual void Deserialize(const rapidjson::Value& jsonObj) = 0;
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