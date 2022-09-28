#pragma once

#include "../include/JSONSerializer.h"


//LOADING
//FUNCTIONAL BUT NOT IMPLEMENTED
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

//do before serializing
void SetDocument() { //set a documennt file that will contain all game objects
	rapidjson::Document doc;
	doc.SetObject();
}

//to call before serializing any object or child object
rapidjson::Value MakeJsonVal() {
	rapidjson::Value object(rapidjson::kObjectType);
	return object;
}

//serialise property name and value, to call for every property in game object
template <typename gameObj>
rapidjson::Value Serialize(
	gameObj object, //pass in game object
	rapidjson::Value objInfo, //pass in json value to add property to
	const char* propertyName, //property name
	rapidjson::Document& targetFile) //to pass in for getallocator()
{
	//find type
	rttr::type type = object.get_type();

	//get data from this member
	rttr::variant propertyVal = type.get_property(propertyName).get_value(object);

	//add into json value
	objInfo.AddMember(propertyName, propertyVal.get_value<type>(), targetFile.GetAllocator());

	return objInfo; //return the json value after property has been added in
}

template <typename gameObj>
rapidjson::Value GetNameForJson(gameObj object, rapidjson::Document targetFile) {

	//makes a copy string using object.name (pls set a name property) to use as name of object when serialising
	//so when desrialising we know what object this is
	std::string name = object.name;
	rapidjson::Value tempVal(name.c_str(), name.length(), targetFile.GetAllocator());
}

template <typename gameObj> //use when all properties have been added to jsonval
void AddToDoc(gameObj object, rapidjson::Document targetFile, rapidjson::Value objInfo) {
	targetFile.AddMember(GetNameForJson(object, targetFile), objInfo, targetFile.GetAllocator());
}

void Serializer::Serialize(const std::string& filepath)
{
	SetDocument();
	MakeJsonVal();
}