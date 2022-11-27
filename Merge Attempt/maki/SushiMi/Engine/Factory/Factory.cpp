
#include "Factory.h"
#include "../Game Object/GameObject.h"

namespace Core
{
	ObjectFactory::ObjectFactory()
	{
	}

	ObjectFactory::~ObjectFactory()
	{
	}

	Object::GameObject* ObjectFactory::Create()
	{
		Object::GameObject* newlycreated = new Object::GameObject();

		return newlycreated;
	}

	void ObjectFactory::AddtoDestroyList(Object::GameObject* Obj)
	{
		DeleteList.insert(Obj);
	}

	void ObjectFactory::DestroyEverything()
	{
		std::set<Object::GameObject*>::iterator it = DeleteList.begin();

		for (it; it != DeleteList.end(); ++it)
		{
			delete &it;
		}

		DeleteList.clear();
	}

	void ObjectFactory::Update(const double dt)
	{
		for (std::set<Object::GameObject*>::iterator it = DeleteList.begin(); it != DeleteList.end(); ++it)
		{
			Object::GameObject* temp = *it;

			std::unordered_map<std::string, Object::GameObject*>::iterator Objit = ObjectContainer.find(temp->GetObjectProperties()->GetIDName());

			ObjectContainer.erase(Objit);

			delete temp;
		}

		DeleteList.clear();
	}

	void ObjectFactory::AddObjects(Object::GameObject* added, std::string i)
	{
		ObjectContainer.insert({ i, added });

	}

	void ObjectFactory::Init()
	{
		
	}

	Object::GameObject* ObjectFactory::BuildSerialise(const std::string filename)
	{
		return nullptr;
	}

	void ObjectFactory::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}
}