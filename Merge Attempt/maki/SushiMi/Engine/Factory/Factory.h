#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/System/SystemFrame.h"
#include "../Game Object/GameObject.h"

namespace Core
{
	class ObjectFactory : public SystemFrame
	{
	private:
		unsigned int LastObjectID;

		std::unordered_map<unsigned int, Object::GameObjectProperty*> ObjectContainer;

		std::set<Object::GameObjectProperty*> DeleteList;

	public:		
		ObjectFactory();
		virtual ~ObjectFactory();

		Object::GameObjectProperty* Create(const std::string filename);

		void AddtoDestroyList(Object::GameObjectProperty* Obj);

		void DestroyEverything();

		virtual void Update(const double dt);

		void AddObjects(Object::GameObjectProperty* added, unsigned int i);

		virtual void Init();

		Object::GameObjectProperty* BuildSerialise(const std::string filename);
	};
}