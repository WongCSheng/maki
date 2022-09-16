#pragma once
#include <rttr/property.h>
#include <rttr/variant.h>
#include <rttr/type.h>
#include <fstream>
#include <filesystem>
#include <document.h>
#include <istreamwrapper.h>
#include <filereadstream.h>
#include <reader.h>

struct vec3
{
	float x = 0;
	float y = 0;
	float z = 0;
};

class DemoClass
{
public://methods
	DemoClass();
	~DemoClass();
	vec3 GetPosition();
	void SetPosition(vec3 pos);
public://variables
	int health = 0;
	int damage = 0;
	//need to declare your rttr macro here in public
	//RTTR_ENABLE();
private://variables
	vec3 position;

};

void FileLoadingCode(DemoClass& demo, const std::filesystem::path& p) {}
//{
//	//step 0. load your file into the document.
//	rapidjson::Document doc;
//	/*
//	rapidjson::OStreamWrapper ;
//	rapidjson::IStreamWrapper;
//	rapidjson::FileReadStream;*/
//	//doc.ParseStream();
//
//	//step 1. read the data
//	//if we want to directly just get the DemoClass data
//	//doc["DemoClass"] will get the job done
//	//the code below will showcase the power of rttr
//	for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
//	{
//		//iter->value.GetString(); <- something i can do
//		//1.1 rttr can get the type if you know the name
//		//using rttr::type::get_by_name(std::string)
//		//remember to check the type is valid
//		//rttr::type t = rttr::type::get_by_name(iter->name.GetString()); //impt, v fast, only occurs on loadtime
//		//if (t.is_valid() == false)
//		//	continue;
//
//		//1.2 since there should only be 1 valid data for democlass
//		//remember that DemoClass is saved as an object so we need to do another for loop
//
//		{//loop here
//			//1.2.1 you can obtain the property by name too 
//			//using t.get_property(std::string)
//			//remember to check for validity
//
//			//1.2.2 you can check the property type by using
//			//property.get_type() if the type is the same
//			//you can set their property value.
//			//an easy way to compare them is by using type.get_id()
//			//e.g if you want to check if the type is an int
//			//you can get it's rttr::type by rttr::type::get<int>()
//
//				//1.2.2.1
//				//if the type is the same
//				//set the property value using
//				//property.set_value()
//				//the function takes in rttr::instance and rttr::arguments
//				//instance is like a reference.
//				//arguements are just variables passed.
//				//so they can be anything
//
//				//1.2.2.2
//				//remember you need to save them in the way you serialized them
//				//since you saved the vec3 as an array you will need to get the array from rapidjson
//				//with the GetArray() function
//
//			/*rttr::property somep = t.get_property("Health");
//			somep.set_value(demo, iter->value.GetInt());*/
//		}
//	}

//}