//******************************************************************************/
/*!
\file		Factory.cpp
\author 	Wong Chong Sheng
\email    	w.chongsheng@digipen.edu
\date   	25/10/2022
\brief		Factory for managing GameObjects.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 //******************************************************************************/

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

		return nullptr;
	}

	void ObjectFactory::AddtoDestroyList(Object::GameObject* Obj)
	{
		DeleteList.insert(Obj);
	}

	void ObjectFactory::DestroyEverything()
	{
		std::unordered_map<unsigned int, Object::GameObject*>::iterator it = ObjectContainer.begin();

		for (it; it != ObjectContainer.end(); ++it)
		{
			delete it->second;
		}

		ObjectContainer.clear();
	}

	void ObjectFactory::Update(const double dt)
	{
		for (std::set<Object::GameObject*>::iterator it = DeleteList.begin(); it != DeleteList.end(); ++it)
		{
			Object::GameObject* temp = *it;

			std::unordered_map<unsigned int, Object::GameObject*>::iterator Objit = ObjectContainer.find(temp->GetObjectProperties()->GetID());

			ObjectContainer.erase(Objit);

			delete temp;
		}

		DeleteList.clear();
	}

	void ObjectFactory::AddObjects(Object::GameObject* added, unsigned int i)
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
}