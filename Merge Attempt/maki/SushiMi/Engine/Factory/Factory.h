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

		std::unordered_map<unsigned int, Object::GameObject*> ObjectContainer;

		std::set<Object::GameObject*> DeleteList;

	public:		
		ObjectFactory();
		virtual ~ObjectFactory();

		Object::GameObject* Create();

		void AddtoDestroyList(Object::GameObject* Obj);

		void DestroyEverything();

		virtual void Update(const double dt);

		void AddObjects(Object::GameObject* added, unsigned int i);

		virtual void Init();

		Object::GameObject* BuildSerialise(const std::string filename);
	};
}