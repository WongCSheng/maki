
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
#include "../Serialiser/JSONSerializer.h"

namespace Core
{
	ObjectFactory::ObjectFactory()
	{
		LastObjectID = 0;
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
			//erase from ObjectContainer
			delete *it;
		}
	}

	void ObjectFactory::Update(const double )
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
		LastObjectID++;
	}

	unsigned int ObjectFactory::Get_num_of_Objects()
	{
		return LastObjectID;
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
			rapidjson::Value nameVal(tempStr.c_str(), static_cast<rapidjson::SizeType>(tempStr.size()), doc.GetAllocator());
			//add obj name
			tempVal.AddMember("Name", nameVal, doc.GetAllocator());
			//add obj id
			tempVal.AddMember("ID", it.second->characteristics->GetID(), doc.GetAllocator());

			tempStr = (it.second->characteristics->GetIDName());
			rapidjson::Value idVal(tempStr.c_str(), static_cast<rapidjson::SizeType>(tempStr.size()), doc.GetAllocator());
			//add obj id name
			tempVal.AddMember("ID Name", idVal, doc.GetAllocator());

			for (auto& itr : it.second->GetObjectProperties()->GetComponentContainer()) {
				if (itr.first == Core::ComponentID::Collision) {
					tempVal.AddMember("Component", "Collision", doc.GetAllocator());
				
				}
			
			}

			//add to top lvl object
			std::string objCountStr = std::to_string(objCount);
			rapidjson::Value index(objCountStr.c_str(), static_cast<rapidjson::SizeType>(objCountStr.size()), doc.GetAllocator());
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

	void ObjectFactory::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> )
	{

	}

	//ASSETS MANAGER

	AssetsManager::AssetsManager()
	{

	}

	AssetsManager::~AssetsManager()
	{
		files.clear();
	}

	void AssetsManager::Init()
	{

	}

	void AssetsManager::Update(const double )
	{

	}

	void AssetsManager::RegisterComponent(std::unordered_map<std::string, Object::GameObject*> ObjectContainer)
	{

	}

	void AssetsManager::Add_files(std::string path)
	{
		for (auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_directory())
			{
				Go_Deeper(entry.path());
			}
			else
			{
				files.push_back(entry.path().string());
			}

			std::cout << entry.path() << std::endl;
		}
	}

	void AssetsManager::Go_Deeper(std::filesystem::path path)
	{
		for (auto& sub : std::filesystem::directory_iterator(path))
		{
			if (sub.is_directory())
			{
				Go_Deeper(sub.path());
			}
			else
			{
				files.push_back(sub.path().string());
			}
		}
	}
	
	void AssetsManager::Add_Assets(ObjectFactory* container)
	{
		for (auto& item : files)
		{
			if (item.substr(item.find_last_of(".")) == ".json")
			{
				DeserializeEntity(item, container);
			}
		}
	}

	/*void AssetsManager::Remove_Assets(const std::string file)
	{

	}

	void AssetsManager::Add_Audio(std::map<std::string, FMOD::Sound*> &container)
	{
		for (auto& audio : files)
		{
			if (audio.substr(audio.find_last_of(".")) == ".wav")
			{
				
			}
		}
	}

	void AssetsManager::Remove_Audio()
	{

	}

	void AssetsManager::Add_Maps(std::vector<std::string> container)
	{
		for (auto& maps : files)
		{

		}
	}*/

	std::vector<std::string>& AssetsManager::GetFiles()
	{
		return files;
	}

	void AssetsManager::ClearFileContainer()
	{
		files.clear();
	}
}