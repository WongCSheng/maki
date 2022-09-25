#pragma once
#include <../include/common_headers.hpp>
#include "../include/JSONSerializer.h"

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
	rttr::variant c = type.get_property(propertyName).get_value(object);
		//add into json value
	objInfo.AddMember(propertyName, objInfo/*propertyVal.get_value<type>()*/, targetFile.GetAllocator());

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
