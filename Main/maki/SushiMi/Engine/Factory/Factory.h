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
<<<<<<< HEAD
		unsigned int LastObjectID;

=======
>>>>>>> M3-submission-branch
		std::set<Object::GameObject*> DeleteList;

	public:		
		ObjectFactory();
		virtual ~ObjectFactory();

<<<<<<< HEAD
		std::unordered_map<std::string, Object::GameObject*> ObjectContainer;
=======
		static inline std::unordered_map<std::string, Object::GameObject*> ObjectContainer;
		unsigned int LastObjectID;
>>>>>>> M3-submission-branch

		Object::GameObject* Create();

		void AddtoDestroyList(Object::GameObject* Obj);

		void DestroyEverything();

		void Update(const double dt);

		void AddObjects(Object::GameObject* added, std::string i);

		void Init();

<<<<<<< HEAD
<<<<<<<< HEAD:Main/maki/SushiMi/Engine/Factory/Factory.h
		void SerializeObjects(const char* filename);
========
		void Serialize(const char* filename);
>>>>>>>> M3-submission-branch:Graphics/maki/SushiMi/Engine/Factory/Factory.h

=======
		void DeserializeObjects(const char* filename);
	
>>>>>>> M3-submission-branch
		void RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer);
	};
}
