
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

		return nullptr;
	}

	void ObjectFactory::AddtoDestroyList(Object::GameObject* Obj)
	{
		DeleteList.insert(Obj);
	}

	void ObjectFactory::DestroyEverything()
	{
		std::unordered_map<std::string, Object::GameObject*>::iterator it = ObjectContainer.begin();

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


	void ObjectFactory::Serialize(const char* filename) {
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
		int objCount = 0;

		for (auto& it : ObjectContainer) {

			tempVal.SetObject();
			//std::pair<unsigned int, std::string> ObjectID; //Unsigned int is the component tags, String is the name of the object
			// 
			//std::unordered_map<ComponentID, Component*> ComponentContainer;


			tempVal.AddMember("Obj Name", it.second->characteristics->GetID(), doc.GetAllocator());
			tempVal.AddMember("Name", it.second->characteristics->GetID(), doc.GetAllocator());
			tempVal.AddMember("3", 324235, doc.GetAllocator());
			//
			//std::string s = std::to_string(objCount);
			//Value index(s.c_str(), s.size(), doc.GetAllocator()); // copy string

			objCount++;


		}

		doc.AddMember("test", tempVal, doc.GetAllocator());
		//doc.AddMember("Obj Name2",12344, doc.GetAllocator());


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