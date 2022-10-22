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

/*  _________________________________________________________________________ */
/*! DeserializeAndPrintConsole
@param const std::string& filepath
json file name
@return bool
returns 0 if failed, 1 if success

Takes in a json file and prints contents to console. If failed, prints error code.
*/
bool Serializer::DeserializeAndPrintConsole(const std::string& filepath) {

	using namespace rapidjson;
	using namespace std;
	Document doc;
	ifstream ifs(filepath);
	IStreamWrapper isw(ifs);
	ParseResult result = doc.ParseStream(isw);
	bool objectsLeft = true;

	if (!result) { //check if parsing succedded
		printf("JSON parse error: %s (%zu)\n", GetParseError_En(result.Code()), result.Offset());
		return 0; //failure
	}

	//go through biggest object in file
	for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
	{
		cout << iter->name.GetString() << ":";

		//immediately print 
		if (iter->value.IsInt())
			cout << iter->value.GetInt() << endl;

		else if (iter->value.IsString())
			cout << iter->value.GetString() << endl;

		else if (iter->value.IsDouble())
			cout << iter->value.GetDouble() << endl;

		else if (iter->value.IsFloat())
			cout << iter->value.GetFloat() << endl;

		else if (iter->value.IsBool()) {
			if (iter->value.GetBool())
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}

		else if (iter->value.IsNull())
			cout << "null" << endl;

		//bigger objects we need to for loop through
		else if (iter->value.IsArray())
		{
			int arrSize = iter->value.Size();
			auto newArr = iter->value.GetArray();

			for (int i = 0; i < arrSize; ++i) {

				if (newArr[i].IsInt())
					cout << newArr[i].GetInt() << endl;

				else if (newArr[i].IsString())
					cout << newArr[i].GetString() << endl;

				else if (newArr[i].IsDouble())
					cout << newArr[i].GetDouble() << endl;

				else if (newArr[i].IsFloat())
					cout << newArr[i].GetFloat() << endl;

				else if (newArr[i].IsBool()) {
					if (newArr[i].GetBool())
						cout << "true" << endl;
					else
						cout << "false" << endl;
				}
			}
		}
		else if (iter->value.IsObject())
		{
			while (objectsLeft) { //implement code to loop here until there are no more objects
				objectsLeft = !objectsLeft;
			}
			//currently doesnt support;
			cout << "Invalid value type!" << endl;
			return 0;
		}
		else
		{
			cout << "Invalid value type!" << endl;
			return 0; //fail to parse 
		}
	}
	return 1; //success
}












//SAVING
//NOT IMPLEMENTED, NOT FULLY FUNCTIONAL








/*  _________________________________________________________________________ */
/*! SerializeEntity
@param rapidjson::Document& doc
doc to serialize into
@param Entity entity
entity to serialize
@return void

This function serializes a single entity.
*/

static void SerializeEntity(rapidjson::Document& doc, Core::Object::GameObjectProperty entity) {

	rapidjson::Value ObjectVal(rapidjson::kObjectType);
	//rttr::type type = entity.get_type();
	//if (entity.hascomponentABC)
	//1. Get all the data of the object



	/*rttr::variant health_value = type.get_property("Health").get_value(entity);
	rttr::variant damage_value = type.get_property("Damage").get_value(entity);
	rttr::variant position_value = type.get_property("Position").get_value(entity);*/

	////2. write them into the document
	//doc.AddMember("Health", health_value.get_value<int>(), doc.GetAllocator());
	//doc.AddMember("Damage", damage_value.get_value<int>(), doc.GetAllocator());

}


