
#include "Factory.h"

namespace Core
{
	ObjectFactory::ObjectFactory()
	{
	}

	ObjectFactory::~ObjectFactory()
	{
	}

	Object::GameObjectProperty* ObjectFactory::Create(const std::string filename)
	{
		return nullptr;
	}

	void ObjectFactory::AddtoDestroyList(Object::GameObjectProperty* Obj)
	{
		DeleteList.insert(Obj);
	}

	void ObjectFactory::DestroyEverything()
	{
		for (std::set<Object::GameObjectProperty*>::iterator it = DeleteList.begin(); it != DeleteList.end(); ++it)
		{
			Object::GameObjectProperty* temp = *it;

			std::unordered_map<Object::ObjectID, Object::GameObjectProperty>::iterator Objit = ObjectContainer.find(temp->GetID());

			ObjectContainer.erase(Objit);

			delete temp;
		}

		DeleteList.clear();
	}
}