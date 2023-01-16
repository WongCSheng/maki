/*!
@file		JSONSerializer.cpp
@author		fei.x@digipen.edu
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
#include "../Game Object/Player.h"

namespace Core
{
	std::string ReadFileContents(const char* filepath) {
		static std::fstream fs;
		fs.open(filepath, std::fstream::in);

		if (!fs.is_open()) {
			std::cout << "JSONSerializer ReadFileContents: Failed to open file " << filepath << std::endl;
		}

		fs.seekg(0, fs.end); // move cursor to end of file
		size_t fs_size = fs.tellg(); // get position of file cursor, which can be assumed as the file's size
		fs.seekg(0, fs.beg); // move cursor to beginning of file

		std::string file_contents(fs_size, ' '); // reserve space for the file contents
		fs.read(&file_contents[0], fs_size); // copy from filstream into file_contents
		fs.close();

		return file_contents;
	}

	namespace JSONSerializer {
		/* text to screen*/
		Player* Deserialize(std::string const& filepath) {
			std::string json_from_file = ReadFileContents(filepath.c_str());

			rapidjson::Document document; // Create a JSON document
			if (document.Parse(json_from_file.c_str()).HasParseError()) {
				std::cout << "JSONSerializer Deserialize: There was a JSON parse error : " << filepath << std::endl;
				return new Player();
			}

			if (!document.IsObject()) { // if json document does not start with {}, throw an error
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not start with a JSON object" << std::endl;
				return new Player();
			}

			// does the root object has a key called "sprite" and is it an object?
			if (!document.HasMember("sprite") || !document["sprite"].IsObject()) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'sprite'" << std::endl;
				return new Player();
			}

			// Deserialize sprite content
			rapidjson::Value& spriteObj = document["sprite"]; // get the sprite JSON object
			if (!spriteObj.HasMember("filepath") || !spriteObj["filepath"].IsString()) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'filepath'" << std::endl;
				return new Player();
			}
			const char* spriteFilepath = spriteObj["filepath"].GetString(); // need to convert the data retrieved to a C++ type

			if (!spriteObj.HasMember("position") || !spriteObj["position"].IsArray()) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'position'" << std::endl;
				return new Player();
			}

			rapidjson::Value& posArr = spriteObj["position"];
			if (posArr.Size() != 2) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " 'position' must have array size of 2" << std::endl;
				return new Player();
			}
			float pos[2];
			for (rapidjson::SizeType i = 0; i < posArr.Size(); i++) {
				rapidjson::Value& posValue = posArr[i];
				if (!posValue.IsNumber()) { // allows float or integer
					std::cout << "JSONSerializer Deserialize: " << filepath << " position[" << i << "] must be a number" << std::endl;
					return new Player();
				}
			}
			//setting player pos from JSON into custom variable
			//set your custom variable!!!! important
			Player::playerpos_restart.x = pos[0];
			Player::playerpos_restart.y = pos[1];

			Player::playerptr->x = pos[0];
			Player::playerptr->y = pos[1];


			if (!spriteObj.HasMember("scale") || !spriteObj["scale"].IsArray()) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'scale'" << std::endl;
				return new Player();
			}

			rapidjson::Value& scaleArr = spriteObj["scale"];
			if (scaleArr.Size() != 2) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " 'scale' must have array size of 2" << std::endl;
				return new Player();
			}
			float scale[2];
			for (rapidjson::SizeType i = 0; i < scaleArr.Size(); i++) {
				rapidjson::Value& scaleValue = scaleArr[i];
				if (!scaleValue.IsNumber()) { // allows float or integer
					std::cout << "JSONSerializer Deserialize: " << filepath << " scale[" << i << "] must be a number" << std::endl;
					return new Player();
				}

				scale[i] = scaleValue.GetFloat(); // since you know scaleValue is a number, can just get the value as a float
			}

			if (!document.HasMember("animation") || !document["animation"].IsArray()) {
				std::cout << "JSONSerializer Deserialize: " << filepath << " does not have 'animation'" << std::endl;
				return new Player();
			}
			rapidjson::Value& animationArr = document["animation"];
			std::vector<std::string> animationList;
			for (rapidjson::SizeType i = 0; i < animationArr.Size(); i++) {
				rapidjson::Value& animationName = animationArr[i];
				if (!animationName.IsString()) {
					std::cout << "JSONSerializer Deserialize: " << filepath << " animation[" << i << "] must be a string" << std::endl;
					return new Player();
				}
				animationList.push_back(animationName.GetString());
			}

			std::cout << "JSONSerializer Deserialize: Managed to parse " << filepath << std::endl;
			return new Player(spriteFilepath, pos, scale, animationList);
		}


		/* screen to text*/
		void Serialize(Player* player, std::string const& filepath) {
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
			jsonSpriteValue.PushBack(Player::playerptr->x, jsonDoc.GetAllocator()); // Write in the x value


			// Serialize "position"
			jsonSpriteValue.SetArray(); // sets the type to a JSON array
			// IMPORTANT: need to get the player's sprite's transformation to pass in the position values, currently hardcoded
			jsonSpriteValue.PushBack(Player::playerptr->x, jsonDoc.GetAllocator()); // Write in the x value
			jsonSpriteValue.PushBack(Player::playerptr->y, jsonDoc.GetAllocator()); // Write in the y value
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
			if (!fs.is_open()) {
				std::cout << "JSONSerializer Serialize: " << filepath << " cannot be opened" << std::endl;
				return;
			}
			fs.write(jsonStrBuffer.GetString(), jsonStrBuffer.GetSize()); // writing the JSON string into the file
			fs.close();
		}

		/*  _________________________________________________________________________ */
		/*! DeserializeAndPrintConsole
		@param const std::string& filepath
		json file name
		@return bool
		returns 0 if failed, 1 if success

		Takes in a json file and prints contents to console. If failed, asserts and prints error code.
		//*/
		//bool Serializer::DeserializeAndPrintConsole(const std::string& filepath) {
		//
		//	using namespace rapidjson;
		//	using namespace std;
		//	Document doc;
		//	ifstream ifs(filepath);
		//	IStreamWrapper isw(ifs);
		//	ParseResult result = doc.ParseStream(isw);
		//	bool objectsLeft = true;
		//
		//	if (!result) { //check if parsing succedded
		//		printf("JSON parse error: %s (%zu)\n", GetParseError_En(result.Code()), result.Offset());
		//		assert(("JSON parse error: %s (%zu)\n", !result));
		//		return 0; //failure
		//	}
		//
		//
		//	//go through biggest object in file
		//	for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
		//	{
		//		cout << iter->name.GetString() << ":";
		//
		//		//immediately print 
		//		if (iter->value.IsInt())
		//			cout << iter->value.GetInt() << endl;
		//
		//		else if (iter->value.IsString())
		//			cout << iter->value.GetString() << endl;
		//
		//		else if (iter->value.IsDouble())
		//			cout << iter->value.GetDouble() << endl;
		//
		//		else if (iter->value.IsFloat())
		//			cout << iter->value.GetFloat() << endl;
		//
		//		else if (iter->value.IsBool()) {
		//			if (iter->value.GetBool())
		//				cout << "true" << endl;
		//			else
		//				cout << "false" << endl;
		//		}
		//
		//		else if (iter->value.IsNull())
		//			cout << "null" << endl;
		//
		//		//bigger objects we need to for loop through
		//		else if (iter->value.IsArray())
		//		{
		//			int arrSize = iter->value.Size();
		//			auto newArr = iter->value.GetArray();
		//
		//			for (int i = 0; i < arrSize; ++i) {
		//
		//				if (newArr[i].IsInt())
		//					cout << newArr[i].GetInt() << endl;
		//
		//				else if (newArr[i].IsString())
		//					cout << newArr[i].GetString() << endl;
		//
		//				else if (newArr[i].IsDouble())
		//					cout << newArr[i].GetDouble() << endl;
		//
		//				else if (newArr[i].IsFloat())
		//					cout << newArr[i].GetFloat() << endl;
		//
		//				else if (newArr[i].IsBool()) {
		//					if (newArr[i].GetBool())
		//						cout << "true" << endl;
		//					else
		//						cout << "false" << endl;
		//				}
		//			}
		//		}
		//		else if (iter->value.IsObject())
		//		{
		//			while (objectsLeft) { //implement code to loop here until there are no more objects
		//				objectsLeft = !objectsLeft;
		//			}
		//			//currently doesnt support;
		//			cout << "Invalid value type!" << endl;
		//			return 0;
		//		}
		//		else
		//		{
		//			cout << "Invalid value type!" << endl;
		//			return 0; //fail to parse 
		//		}
		//	}
		//	return 1; //success
		//}
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		////SAVING
		////NOT IMPLEMENTED, NOT FULLY FUNCTIONAL
		//
		//
		//
		//
		//
		//
		//
		//
		///*  _________________________________________________________________________ */
		///*! SerializeEntity
		//@param rapidjson::Document& doc
		//doc to serialize into
		//@param Entity entity
		//entity to serialize
		//@return void
		//
		//This function serializes a single object.
		//*/
		//
		//
		//rapidjson::Value Serializer::SerializeObjects(const std::string& filepath, std::map<std::string, Object::GameObject> objMap) {
		//
		//	using namespace rapidjson;
		//	using namespace std;
		//	string tempStr;
		//	Document doc;
		//	ifstream ifs(filepath);
		//	IStreamWrapper isw(ifs);
		//	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
		//
		//	rapidjson::Value TestObjectValue(rapidjson::kObjectType);
		//	for (auto& [name, obj] : objMap)
		//	{
		//		//rttr::type type = obj.get_type();
		//
		//		////rttr::variant orientation_val = type.get_property("orientation").get_value(obj); //glm::vec2
		//
		//		//rttr::variant dirCurr_val = type.get_property("dirCurr").get_value(obj); //float
		//		//rttr::variant mass_bool = type.get_property("mass").get_value(obj); //float
		//		//rttr::variant anim_rainbow_bool = type.get_property("anim_rainbow").get_value(obj); //bool
		//		//rttr::variant rainbowCount_val = type.get_property("rainbowCount").get_value(obj); //double
		//		//rttr::variant anim_bw_bool = type.get_property("anim_bw").get_value(obj); //bool
		//		//rttr::variant bwCount_val = type.get_property("bw_Count").get_value(obj); //double
		//		//rttr::variant flip_bool = type.get_property("flip").get_value(obj); //bool
		//
		//
		//		//TestObjectValue.AddMember("dirCurr", dirCurr_val.get_value<float>(), allocator);
		//		//TestObjectValue.AddMember("mass", mass_bool.get_value<bool>(), allocator);
		//		//TestObjectValue.AddMember("anim_rainbow", anim_rainbow_bool.get_value<bool>(), allocator);
		//		//TestObjectValue.AddMember("rainbowCount", rainbowCount_val.get_value<double>(), allocator);
		//		//TestObjectValue.AddMember("anim_bw", anim_bw_bool.get_value<bool>(), allocator);
		//		//TestObjectValue.AddMember("bw_Count", bwCount_val.get_value<double>(), allocator);
		//		//TestObjectValue.AddMember("flip", flip_bool.get_value<bool>(), allocator);
		//
		//	}
		//	return TestObjectValue;
		//
		//	////if (entity.hascomponentABC)
		//	////1. Get all the data of the object
		//
		//	//rttr::variant damage_value = type.get_property("Damage").get_value(entity);
		//	//rttr::variant position_value = type.get_property("Position").get_value(entity);
		//
		//	////2. write them into the document
		//	//doc.AddMember("Damage", damage_value.get_value<int>(), doc.GetAllocator());
		//
		//}
		//
		//
	}
}