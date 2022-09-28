/*!
@file		JSONSerializer.cpp
@author		p.tzechengjennifer@digipen.edu
@date		28/09/2022

This file contains a Serializer class that can parse json files.
You can choose to print to console or directly deserialize into your
chosen game object.

*//*__________________________________________________________________________*/



#pragma once
#include "../include/common_headers.hpp"

//LOADING
//FUNCTIONAL BUT NOT IMPLEMENTED

/*  _________________________________________________________________________ */
/*! DeserializeAndPrintConsole
@param const std::string& filepath
json file name
@return bool
returns 0 if failed, 1 if success

Takes in a json file and prints contents to console
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
/*! SetDocument
@param none
@return none

Set a documennt file that will contain all game objects, do before serializing
*/

void SetDocument() { 
	using namespace rapidjson;
	Document doc;
	doc.SetObject();
}

/*  _________________________________________________________________________ */
/*! MakeJsonVal
@param none
@return rapidjson::Value

to call before serializing any object or child object, returns a rapidjson val to insert properties into
*/

rapidjson::Value MakeJsonVal() {
	using namespace rapidjson;
	Value object(rapidjson::kObjectType);
	return object;
}


/*  _________________________________________________________________________ */
/*! Serialize
@param gameObj object
pass in game object
@param rapidjson::Value objInfo
pass in json value to add property to
@param const char* propertyName
property name
@paramrapidjson::Document& targetFile
to pass in for getallocator()
@return rapidjson::Value
returns original rapidjson value but with added property
//serialise property name and value, to call for every property in game object
*/

template <typename gameObj>
rapidjson::Value Serialize(
	gameObj object, 
	rapidjson::Value objInfo,
	const char* propertyName,
	rapidjson::Document& targetFile) 
{
	using namespace rttr;
	//find type
	type type = object.get_type();

	//get data from this member
	variant propertyVal = type.get_property(propertyName).get_value(object);

	//add into json value
	objInfo.AddMember(propertyName, propertyVal.get_value<type>(), targetFile.GetAllocator());

	return objInfo; //return the json value after property has been added in
}


/*  _________________________________________________________________________ */
/*! GetNameForJson
@param gameObj object 
class we are serializing
@param rapidjson::Document targetFile
for getallocator
@return rapidjson::Value
this return value has the copy string

makes a copy string using object.name (pls set a name property) to use as name of object when serialising
so when desrialising we know what object this is
*/
template <typename gameObj>
rapidjson::Value GetNameForJson(gameObj object, rapidjson::Document targetFile) {

	//makes a copy string using object.name (pls set a name property) to use as name of object when serialising
	//so when desrialising we know what object this is
	using namespace std;
	using namespace rapidjson;
	string name = object.name;
	Value tempVal(name.c_str(), name.length(), targetFile.GetAllocator());
}

/*  _________________________________________________________________________ */
/*! AddToDoc
@param gameObj object
class we're serialising
@param rapidjson::Document targetFile
doc we set earlier
@param rapidjson::Value objInfo
value we going to insert into file
@return none

//use when all properties have been added to jsonval
*/
template <typename gameObj> 
void AddToDoc(gameObj object, rapidjson::Document targetFile, rapidjson::Value objInfo) {
	targetFile.AddMember(GetNameForJson(object, targetFile), objInfo, targetFile.GetAllocator());
}

