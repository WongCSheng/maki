#pragma once

#include "../Headers/STL_Header.h"
#include "../Engine/System/SystemFrame.h"
#include "../Game Object/GameObject.h"

namespace Core
{
	class ObjectFactory : public SystemFrame
	{
	private:
		unsigned int ObjectID;

		std::unordered_map<Object::ObjectID, Object::GameObjectProperty> ObjectContainer;

		std::set<Object::GameObjectProperty*> DeleteList;

	public:
		ObjectFactory();
		~ObjectFactory();

		Object::GameObjectProperty* Create(const std::string filename);

		void AddtoDestroyList(Object::GameObjectProperty* Obj);

		void DestroyEverything();

		virtual void Update(const double dt);

		virtual void CheckForNewComponents(void);

		virtual void RegisterComponents(const Core::Component comp);

		Object::GameObjectProperty* BuildSerialise(const std::string filename);
					  
					  
	};				  
}