/*
File: Physics.cpp
Author: w.chongsheng@digipen.edu
Description: Physics components that stores data for which to be used in PhysicSystem.cpp
*/

#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/System/SystemFrame.h"

namespace Core
{
	//forward declaration
	namespace Object
	{
		class GameObject;
	}
	
	class ObjectFactory : public SystemFrame
	{
	private:
		unsigned int LastObjectID;

		std::unordered_map<std::string, Object::GameObject*> ObjectContainer;

		std::set<Object::GameObject*> DeleteList;

	public:		
		ObjectFactory();
		virtual ~ObjectFactory();

		Object::GameObject* Create();

		void AddtoDestroyList(Object::GameObject* Obj);

		void DestroyEverything();

		void Update(const double dt);

		void AddObjects(Object::GameObject* added, std::string i);

		void Init();

		Object::GameObject* BuildSerialise(const std::string filename);

		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
	};
}
