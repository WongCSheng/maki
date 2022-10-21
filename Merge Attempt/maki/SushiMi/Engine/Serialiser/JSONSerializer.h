/*!
@file		JSONSerializer.h
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains a Serializer class that can parse json files.
You can choose to print to console or directly deserialize into your
chosen game object.

*//*__________________________________________________________________________*/

#pragma once

#include "../Headers/RapidJSON_Header.h"
#include "../Headers/STL_Header.h"

#ifndef JSERIALIZE_H
#define JSERIALIZE_H

class Serializer {

public:

	//serialize everything
	//set value to gameobject if all property names match
	//void Serialize(const std::string& filepath);

	/*  _________________________________________________________________________ */
	/*! DeserializeObject
	@param const std::string& filepath
	json file
	@gameObject& obj
	class to deserialize into
	@return bool
	returns 0 if failed, 1 if success

	Takes in a json file uses contents to change obj properties
	*/
	template<class gameObject>
	bool DeserializeObject(gameObject& obj, const std::string& filepath) {

		using namespace rapidjson;
		using namespace std;
		string tempStr;
		Document doc;
		ifstream ifs(filepath);
		IStreamWrapper isw(ifs);
		ParseResult result = doc.ParseStream(isw);
		//rttr::type ObjType = obj.get_type();

		if (!result) { //check if parsing succedded
			printf("JSON parse error: %s (%zu)\n", GetParseError_En(result.Code()), result.Offset());
			return 0; //failure
		}

		for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
		{
			tempStr = iter->name.GetString(); //gets json property name
			//rttr::property propertyType = ObjType.get_property(tempStr); //get the name by type


			if (iter->value.IsInt())
				obj.SetInt(iter->value.GetInt());

			else if (iter->value.IsString())
				obj.SetStr(iter->value.GetString());

			else if (iter->value.IsDouble())
				obj.SetDouble(iter->value.IsDouble());

			else if (iter->value.IsFloat())
				obj.SetFloat(iter->value.GetFloat());

			else if (iter->value.IsBool())
				obj.SetBool(iter->value.GetBool());

			else if (iter->value.IsNull())
				obj.SetNull();

			else if (iter->value.IsArray())
			{
				int arrSize = iter->value.Size();
				auto newArr = iter->value.GetArray();
			}
			else if (iter->value.IsObject())
			{
				//currently don't support
				cout << "Invalid value type!" << endl;;
				return 0; //fail to parse 
			}
			else
			{
				cout << "Invalid value type!" << endl;;
				return 0; //fail to parse 
			}

		}
		return 1; //success

	}
	//use these when debugging
	bool DeserializeAndPrintConsole(const std::string& filepath);

};

/*  _________________________________________________________________________ */
	/*! DeserializeObject
	@gameObject& obj
	class deserialized into
	@return none
	_________________________________________________________________________ */

template<class gameObject>
void PrintObjectProperties(gameObject& obj) {
	using namespace std;
	cout << obj.GetInt() << endl;
	cout << obj.GetFloat() << endl;
	cout << obj.GetDouble() << endl;
	cout << obj.GetBool() << endl;
	cout << obj.GetNull() << endl;
	cout << obj.GetStr() << std::endl;
}


#endif