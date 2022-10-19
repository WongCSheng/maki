#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/Entity/ECS.h"

namespace Object
{
	enum class ObjectID
	{
		None = 0,
		Renderer,
		transform,
		camera,
		physics,
		GameObject,
		End
	};
	
	class GameObjectProperty
	{
	private:
		GameObjectProperty();
		~GameObjectProperty();
		
		std::unordered_map<ObjectID,Core::Component*> ComponentContainer;

		ObjectID ID;

	public:
		friend class Core::Component;
		
		void Init();

		void AddToDestroyList();

		Core::Component* GetComponent(ObjectID ID);

		ObjectID GetID();

		std::string GetIDName();

		void AddComponent(ObjectID ID,Core::Component* comp);

		void RemoveComponent(Core::Component* comp);
	};
}