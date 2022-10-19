
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
		std::unordered_map<unsigned int, Object::GameObjectProperty*>::iterator it = ObjectContainer.begin();

		for (it; it != ObjectContainer.end(); ++it)
		{
			delete it->second;
		}

		ObjectContainer.clear();
	}

	void ObjectFactory::Update(const double dt)
	{
		for (std::set<Object::GameObjectProperty*>::iterator it = DeleteList.begin(); it != DeleteList.end(); ++it)
		{
			Object::GameObjectProperty* temp = *it;

			std::unordered_map<unsigned int, Object::GameObjectProperty*>::iterator Objit = ObjectContainer.find(temp->GetID());

			ObjectContainer.erase(Objit);

			delete temp;
		}

		DeleteList.clear();
	}

	void ObjectFactory::AddObjects(Object::GameObjectProperty* added, unsigned int i)
	{
		ObjectContainer.insert({ i, added });
	}
}