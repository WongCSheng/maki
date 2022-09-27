#pragma once
#include "../include/common_headers.hpp"

//LOADING
bool Serializer::Deserialize(const std::string& filepath){
	using namespace rapidjson;

	Document doc;
	std::ifstream ifs(filepath);
	IStreamWrapper isw(ifs);
	
	ParseResult result = doc.ParseStream(isw);
	//check if parsing succedded
	if (!result) {
	
		printf("JSON parse error: %s (%zu)\n", GetParseError_En(result.Code()), result.Offset());
		return 1;
	}

	for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
	{
		std::cout << iter->name.GetString() << ":";
		
		//std::cout << iter->value.GetInt() << std::endl;
		if (iter->value.IsInt())
			std::cout << iter->value.GetInt() << std::endl;
		else if (iter->value.IsString())
			std::cout << iter->value.GetString() << std::endl;
		else if (iter->value.IsDouble())
			std::cout << iter->value.GetDouble() << std::endl;
		else if (iter->value.IsFloat())
			std::cout << iter->value.GetFloat() << std::endl;
		else if (iter->value.IsBool()) //may want to convert to true or false
			std::cout << iter->value.GetBool() << std::endl;
		else if (iter->value.IsNull())
			std::cout << "null" << std::endl;
		else if (iter->value.IsArray())
		{
			//further go in?for loop?
		}
		else if (iter->value.IsObject())
		{
			//further go in?for loop?
		}
		else
			std::cout << "Invalid value type!" << std::endl;;
		
	}
	return 0;
}


//SAVING
//NOT IMPLEMENTED


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
