/*!
@file		JSONSerializer.cpp
@author		Chong Rui Xuan Aurelia
@par		fei.x@digipen.edu
@date		6/1/2022

This file contains a Serializer class that can parse json files.
You can choose to print to console or directly deserialize into your
chosen game object.

*//*__________________________________________________________________________*/

#pragma once
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Game Object/GameObject.h"
#include <fstream>
#include <exception>
#include <vector>
#include "../Components/Transform/Transform.h"
#include "../Game Object/Player.h"
#include "../Core/Core.h"

namespace Core
{
	ObjectFactory* MainSystem::objfactory;
	std::map<std::string, std::vector<std::string>> levelCorrectIngredients;

	std::string ReadFileContents(const char* filepath)
	{
		std::ifstream jFile(filepath);

		if (!jFile.is_open())
		{
			std::string error = std::string("Failed to open ") + filepath;
			return error;
		}
		std::stringstream file_contents;
		file_contents << jFile.rdbuf();
		return file_contents.str().c_str();
	}

	void DeserializeEntity(std::string const& filepath, ObjectFactory* objfact)
	{
		//std::cout << filepath << " <<<<<<<reading from this filepath\n";
		std::string json_from_file = ReadFileContents(filepath.c_str());

		std::string name; //name of object we are parsing (under sprite component)
		float alpha;	  //alpha component of Sprite

		//Object::GameObject gameObj = ObjectFactory::Create();
		rapidjson::Document document;

		if (document.Parse(json_from_file.c_str()).HasParseError())
		{
			std::cout << "JSONSerializer DeserializeEntity: There was a JSON parse error : " << filepath << std::endl;
			return;
		}
		// remember to delete entity if nullptr is returned
		if (!document.IsObject())
		{
			std::cout << "JSONSerializer DeserializeEntity: " << filepath << " does not start with a JSON object 1" << std::endl;
			return;
		}

		/* creating a gameObj inst to store and to be saved into Obj Container */
		Object::GameObject* gameObj = new Object::GameObject(); //contains characteristics of game objects
		std::cout << "Managed to parse " << filepath << std::endl;

		if (!document.HasMember("components") || !document["components"].IsArray())
		{
			std::cout << "JSONSerializer DeserializeEntity: " << filepath << " does not start with a JSON object 2" << std::endl;

			return;
		}

		for (rapidjson::SizeType i = 0; i < document["components"].Size(); i++)
		{
			rapidjson::Value& compJsonObj = document["components"][i]; // access element inside components array


			if (!compJsonObj.IsObject())
			{
				std::cout << "JSONSerializer DeserializeEntity: " << filepath << " does not start with a JSON object 3" << std::endl;
			}

			if (!compJsonObj.HasMember("type") || !compJsonObj["type"].IsString())
			{
				std::cout << "JSONSerializer DeserializeLevel: " << filepath << " does not start with a JSON object 4" << std::endl;

				return;
			}

			if (compJsonObj["type"] == "Transform")
			{
				//destructor will  auto destroy? WATCH out for MemLeak!!!
				transComp = new Transform();
				transComp->Deserialize(compJsonObj);
				gameObj->GetObjectProperties()->AddComponent(ComponentID::Transform, transComp);
				//std::cout << "transform component is : " << transComp << std::endl;
				//delete transComp;
			}

			else if (compJsonObj["type"] == "Sprite")
			{
				//rapidjson::Value& spritJsonObj = document["Sprite"]; // get the sprite JSON object
				//if (!spritJsonObj.HasMember("texturepath") || !spritJsonObj["texturepath"].IsString())
				//{
				//	std::cout << "JSONSerializer Deserialize Sprite: " << filepath << " does not have 'texturepath'" << std::endl;
				//	return;
				//}
				const char* texturePath = compJsonObj["texturepath"].GetString(); // need to convert the data retrieved to a C++ type
				name = compJsonObj["name"].GetString();	//	name of object (under sprite component)

				//std::cout << "loading of " << name << "\n";
				Sprite* object = new Sprite(texturePath);
				/*Sprite::menu->transformation.Position = glm::vec2(0, 0);
				Sprite::menu->transformation.Scale = glm::vec2(1000, 800);*/
				if (compJsonObj.HasMember("alpha"))
				{
					alpha = compJsonObj["alpha"].GetFloat();
					object->alpha = alpha;
				}


				object->Deserialize(compJsonObj);

				gameObj->GetObjectProperties()->AddComponent(ComponentID::Renderer, object);
				//delete object;
			}


		}

		//std::string name("Object: " + std::to_string(objfact->LastObjectID));
		//std::cout << name << " inserting into object container\n";
		objfact->AddObjects(gameObj, name);	//	save everything in gameObj into container
		//delete gameObj;
	}

	/*										Deserializes multiple components at once
	-------------------------------------------------------------------------------*/
	void DeserializeAll(std::string const& filepath, ObjectFactory* objfact)
	{

		std::string json_from_file = ReadFileContents(filepath.c_str());

		rapidjson::Document component;

		if (component.Parse(json_from_file.c_str()).HasParseError())
		{
			std::cout << "JSONSerializer DeserializeAll: There was a JSON parse error : " << filepath << std::endl;
			return;
		}
		// remember to delete entity if nullptr is returned
		if (!component.IsObject())
		{
			std::cout << "JSONSerializer DeserializeAll: " << filepath << " does not start with a JSON object 1" << std::endl;
			return;
		}

		const rapidjson::Value& jsonArr = component["components"];
		for (rapidjson::size_t i{}; i < jsonArr.Size(); i++)
		{
			const rapidjson::Value& object = jsonArr[static_cast<rapidjson::SizeType>(i)];

			if (!object.IsObject())
			{
				std::cout << "JSONSerializer DeserializeAll: " << filepath << " is not an object" << std::endl;
				return;
			}
			std::string objFilePath = object["filename"].GetString();
			DeserializeEntity(objFilePath, objfact);
			
		}
	}

	Player* Deserialize(std::string const& filepath)
	{
		std::string json_from_file = ReadFileContents(filepath.c_str());

		rapidjson::Document document; // Create a JSON document
		if (document.Parse(json_from_file.c_str()).HasParseError())
		{
			std::cout << "JSONSerializer Deserialize Player: There was a JSON parse error : " << filepath << std::endl;
			Player* player{};
			return player;
		}

		if (!document.IsObject())
		{ // if json document does not start with {}, throw an error
			std::cout << "JSONSerializer Deserialize Player: " << filepath << " does not start with a JSON object" << std::endl;
			Player* player{};
			return player;
		}

		// does the root object has a key called "sprite" and is it an object?
		if (!document.HasMember("sprite") || !document["sprite"].IsObject())
		{
			std::cout << "JSONSerializer Deserialize Player: " << filepath << " does not have 'sprite'" << std::endl;
			Player* player{};
			return player;
		}

		// Deserialize sprite content
		rapidjson::Value& spriteObj = document["sprite"]; // get the sprite JSON object
		if (!spriteObj.HasMember("filepath") || !spriteObj["filepath"].IsString())
		{
			std::cout << "JSONSerializer Deserialize Player: " << filepath << " does not have 'filepath'" << std::endl;
			Player* player{};
			return player;
		}
		const char* spriteFilepath = spriteObj["filepath"].GetString(); // need to convert the data retrieved to a C++ type

		if (!spriteObj.HasMember("position") || !spriteObj["position"].IsArray())
		{
			std::cout << "JSONSerializer Deserialize Player: " << filepath << " does not have 'position'" << std::endl;
			Player* player{};
			return player;
		}

		rapidjson::Value& posArr = spriteObj["position"];
		if (posArr.Size() != 2)
		{
			std::cout << "JSONSerializer Deserialize Player: " << filepath << " 'position' must have array size of 2" << std::endl;
			Player* player{};
			return player;
		}
		float pos[2];
		for (rapidjson::SizeType i = 0; i < posArr.Size(); i++)
		{
			rapidjson::Value& posValue = posArr[i];
			if (!posValue.IsNumber())
			{ // allows float or integer
				std::cout << "JSONSerializer Deserialize Player: " << filepath << " position[" << i << "] must be a number" << std::endl;
				Player* player{};
				return player;
			}
			pos[i] = posValue.GetFloat(); // since posValue is a number, can just get the value as a float
		}
		//setting player pos from JSON into custom variable
		//set your custom variable!!!! important
		

		/*playerpos_restart.x = pos[0];
		player->playerpos_restart.y = pos[1];

		player->playerpos.x = pos[0];
		player->playerpos.y = pos[1];*/


		if (!spriteObj.HasMember("scale") || !spriteObj["scale"].IsArray())
		{
			std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'scale'" << std::endl;
			Player* player{};
			return player;
		}

		rapidjson::Value& scaleArr = spriteObj["scale"];
		if (scaleArr.Size() != 2)
		{
			std::cout << "JSONSerializer Deserialize: " << filepath << " 'scale' must have array size of 2" << std::endl;
			Player* player{};
			return player;
		}

		float scale[2];
		for (rapidjson::SizeType i = 0; i < scaleArr.Size(); i++)
		{
			rapidjson::Value& scaleValue = scaleArr[i];
			if (!scaleValue.IsNumber())
			{ // allows float or integer
				std::cout << "JSONSerializer Deserialize: " << filepath << " scale[" << i << "] must be a number" << std::endl;
				Player* player{};
				return player;
			}

			scale[i] = scaleValue.GetFloat(); // since you know scaleValue is a number, can just get the value as a float
		}

		if (!document.HasMember("animation") || !document["animation"].IsArray())
		{
			std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'animation'" << std::endl;
			Player* player{};
			return player;
		}
		rapidjson::Value& animationArr = document["animation"];
		std::vector<std::string> animationList;
		for (rapidjson::SizeType i = 0; i < animationArr.Size(); i++)
		{
			rapidjson::Value& animationName = animationArr[i];
			if (!animationName.IsString())
			{
				std::cout << "JSONSerializer Deserialize: " << filepath << " animation[" << i << "] must be a string" << std::endl;
				Player* player{};
				return player;
			}
			animationList.push_back(animationName.GetString());
		}

		//std::cout << "JSONSerializer Deserialize: Managed to parse " << filepath << std::endl;

		return new Player(spriteFilepath, pos, scale, animationList);
		/*Player *valid_player(spriteFilepath, pos, scale, animationList);
		valid_player->playerpos = player->playerpos;
		valid_player->playerpos_restart = player->playerpos_restart;
		return valid_player;*/
	}

}


/* screen to text*/
void Core::Serialize(const Player& player, std::string const& filepath)
{
	rapidjson::Document jsonDoc; // create json document
	jsonDoc.SetObject(); // sets the root to be a JSON object

	rapidjson::Value jsonSpriteObj; // Serialize the Sprite into a JSON object
	jsonSpriteObj.SetObject();

	// Serialize "filepath"
	rapidjson::Value jsonSpriteValue; // To add any type/kind of value into the Sprite object
	// IMPORTANT: need to get the player's sprite's filename string, currently hardcoded on saving sprite filename
	jsonSpriteValue.SetString("../textures/spritesheet/spritesheet.png", jsonDoc.GetAllocator());
	jsonSpriteObj.AddMember("filepath", jsonSpriteValue, jsonDoc.GetAllocator()); // save the filepath string into the sprite JSON object

	// Serialize "position"
	jsonSpriteValue.SetArray(); // sets the type to a JSON array
	// IMPORTANT: need to get the player's sprite's transformation to pass in the position values, currently hardcoded
	jsonSpriteValue.PushBack(player.playerpos.x, jsonDoc.GetAllocator()); // Write in the x value
	jsonSpriteValue.PushBack(player.playerpos.y, jsonDoc.GetAllocator()); // Write in the y value
	jsonSpriteObj.AddMember("position", jsonSpriteValue, jsonDoc.GetAllocator());

	// Serialize "scale"
	jsonSpriteValue.SetArray(); // sets the type to a JSON array
	// IMPORTANT: need to get the player's sprite's transformation to pass in the scale values, currently hardcoded
	jsonSpriteValue.PushBack(100, jsonDoc.GetAllocator()); // Write in the x value
	jsonSpriteValue.PushBack(100, jsonDoc.GetAllocator()); // Write in the y value
	jsonSpriteObj.AddMember("scale", jsonSpriteValue, jsonDoc.GetAllocator()); // save the scale array into the sprite JSON object

	// Serialize "animation" array
	rapidjson::Value jsonAnimArr;
	jsonAnimArr.SetArray(); // set JSON type to array

	// Adding 2 animations. This can be turned into a for loop
	/* Presuming animList is a vector of string
		for (std::string& anim : animList) { // loop through the vector
			rapidjson::Value jsonAnimValue;
			jsonAnimValue.SetString(anim.c_str(), jsonDoc.GetAllocator()); // set the value of jsonAnimValue
			jsonAnimArr.PushBack(jsonAnimValue, jsonDoc.GetAllocator()); // add the anim name into the json animation array
		}
	*/
	rapidjson::Value jsonAnimValue;
	jsonAnimValue.SetString("../textures/spritesheet/Idle.txt", jsonDoc.GetAllocator());
	jsonAnimArr.PushBack(jsonAnimValue, jsonDoc.GetAllocator());
	jsonAnimValue.SetString("../textures/spritesheet/Run.txt", jsonDoc.GetAllocator());
	jsonAnimArr.PushBack(jsonAnimValue, jsonDoc.GetAllocator());

	jsonDoc.AddMember("animation", jsonAnimArr, jsonDoc.GetAllocator()); // add the animation JSON array into the JSON document

	// Saving the JSON document into a string
	rapidjson::StringBuffer jsonStrBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonStrBuffer);
	jsonDoc.Accept(jsonWriter);

	/*if (Editor::LevelEditor::levelsave == 1 )
	{*/
	// Write the JSON string into file
	std::fstream fs;
	fs.open(filepath, std::fstream::out);
	if (!fs.is_open())
	{
		std::cout << "JSONSerializer Serialize: " << filepath << " cannot be opened" << std::endl;
		return;
	}
	fs.write(jsonStrBuffer.GetString(), jsonStrBuffer.GetSize()); // writing the JSON string into the file
	fs.close();
}





