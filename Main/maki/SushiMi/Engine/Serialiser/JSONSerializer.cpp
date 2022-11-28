/*!
@file		JSONSerializer.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains a Serializer class that can parse json files.
You can choose to print to console or directly deserialize into your
chosen game object.

*//*__________________________________________________________________________*/

#pragma once
#include "../Engine/Serialiser/JSONSerializer.h"
#include "../Game Object/GameObject.h"

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
