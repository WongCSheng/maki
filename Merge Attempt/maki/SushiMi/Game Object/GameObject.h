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
		
		Core::Component* ComponentContainer;

		unsigned int ID;

	public:
		friend class Core::Component;
		
		void Init();

		void Destroy();

		template<typename T>
		T* GetComponent(ObjectID ID);

		int GetID();

		void AddComponent(ObjectID ID,Core::Component* comp);

		void RemoveComponent(Core::Component* comp);
	};
}