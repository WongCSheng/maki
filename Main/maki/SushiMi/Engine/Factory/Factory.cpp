
/*
File: Factory.cpp
Author:		Wong Chong Sheng 
email:		w.chongsheng@digipen.edu
co-Author:  Chong Rui Xuan Aurelia 
email:		fei.x@digipen.edu
Description: 
*/
#include "Factory.h"
#include "../Game Object/GameObject.h"
#include "../Headers/RapidJSON_Header.h"

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
			delete *it;
		}

		DeleteList.clear();
	}

	void ObjectFactory::Update(const double dt)
	{
		/*for (std::set<Object::GameObject*>::iterator it = DeleteList.begin(); it != DeleteList.end(); ++it)
		{
			Object::GameObject* temp = *it;

			std::unordered_map<std::string, Object::GameObject*>::iterator Objit = ObjectContainer.find(temp->GetObjectProperties()->GetIDName());

			ObjectContainer.erase(Objit);

			delete temp;
		}

		DeleteList.clear();*/
	}

	void ObjectFactory::AddObjects(Object::GameObject* added, std::string i)
	{
		ObjectContainer.insert({ i, added });

	}

	void ObjectFactory::Init()
	{
		
	}

	void ObjectFactory::DeserializeObjects(const char* filename) {
	
		/*None = 0b0000'0000,
			Renderer = 0b0000'0010,
			Transform = 0b0000'0100,
			Camera = 0b0000'1000,
			Physics = 0b0001'0000,*/

			//set doc
		rapidjson::Document doc;
		std::ifstream ifs(filename);
		rapidjson::IStreamWrapper isw(ifs);
		doc.SetObject();

		rapidjson::Value tempVal(rapidjson::kObjectType);
		std::string tempStr;
		int objCount = 0;

		for (auto& it : ObjectContainer) {
			
			tempVal.SetObject();

			//copy string for obj name
			tempStr = it.first;
			rapidjson::Value nameVal(tempStr.c_str(), tempStr.size(), doc.GetAllocator());
			//add obj name
			tempVal.AddMember("Name", nameVal, doc.GetAllocator());
			//add obj id
			tempVal.AddMember("ID", it.second->characteristics->GetID(), doc.GetAllocator());

			tempStr = (it.second->characteristics->GetIDName());
			rapidjson::Value idVal(tempStr.c_str(), tempStr.size(), doc.GetAllocator());
			//add obj id name
			tempVal.AddMember("ID Name", idVal, doc.GetAllocator());

			for (auto& itr : it.second->GetObjectProperties()->GetComponentContainer()) {
				if (itr.first == Core::ComponentID::Collision) {
					tempVal.AddMember("Component", "Collision", doc.GetAllocator());
				
				}
			
			}

			//add to top lvl object
			std::string objCountStr = std::to_string(objCount);
			rapidjson::Value index(objCountStr.c_str(), objCountStr.size(), doc.GetAllocator());
			doc.AddMember(index, tempVal, doc.GetAllocator());
			objCount++;


		}



		//write ObjectID into json doc
		//ObjectContainer[objectID]

		//go through ObjectContainer
		// if ObjectContainer.ComponentContainer.ID == x component

		FILE* fp = std::fopen(filename, "wb"); // non-Windows use "w"
		char buffer[1024];
		rapidjson::FileWriteStream fs(fp, buffer, sizeof(buffer));
		rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(fs);
		doc.Accept(writer);
		fclose(fp);
	}


	void ObjectFactory::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}
}