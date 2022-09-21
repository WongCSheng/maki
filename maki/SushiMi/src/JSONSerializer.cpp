#pragma once
#include "include\common_headers.hpp"

//another function
rapidjson::Value CreateObjectFunction(rapidjson::Document& doc)
{
	rapidjson::Value object(rapidjson::kObjectType);

	rapidjson::Value name;
	rapidjson::Value data;

	std::string nam = "some random text 123";
	std::string dat = "some random text 456";

	name.SetString(nam.c_str(), nam.size(), doc.GetAllocator());
	data.SetString(dat.c_str(), dat.size(), doc.GetAllocator());

	object.AddMember(name, data, doc.GetAllocator());
	return object;

}
rapidjson::Value Serialize(DemoClass& object, rapidjson::Document& doc)
{
	//0. declare your rapidjson value
	rapidjson::Value DemoObjectValue(rapidjson::kObjectType);

	rttr::type type = object.get_type();

	//1. Get all the data of the object

	rttr::variant health_value = type.get_property("Health").get_value(object);
	rttr::variant damage_value = type.get_property("Damage").get_value(object);
	rttr::variant position_value = type.get_property("Position").get_value(object);

	//shld check if isvalid, if doing dynamically



	//2. write them into the document
	DemoObjectValue.AddMember("Health", health_value.get_value<int>(), doc.GetAllocator());
	DemoObjectValue.AddMember("Damage", damage_value.get_value<int>(), doc.GetAllocator());

	rapidjson::Value arr(rapidjson::kArrayType);
	vec3 avalue = position_value.get_value<vec3>();
	arr.PushBack(avalue.x, doc.GetAllocator());
	arr.PushBack(avalue.y, doc.GetAllocator());
	arr.PushBack(avalue.z, doc.GetAllocator());

	DemoObjectValue.AddMember("Position", arr, doc.GetAllocator());




	return DemoObjectValue;
}

int main()
{
	DemoClass demo;//ignore this if in part 1.
	demo.SetPosition(vec3{ 5.0f,3.0f,55.0f });
	demo.damage = 100;
	demo.health = 100;

	//uncomment when in part 3
	std::cout << "Type in some data to show that your data is saved(damage , health , position)\n" << std::endl;
	std::cin >> demo.damage;
	std::cin >> demo.health;
	vec3 temp;
	std::cin >> temp.x;
	std::cin >> temp.y;
	std::cin >> temp.z;
	demo.SetPosition(temp);

	//step 0. declare your document
	rapidjson::Document doc;
	//step 1. Set document as object
	doc.SetObject();

	//step 2. Write some values into the document
	doc.AddMember("Member1", "data1", doc.GetAllocator());
	doc.AddMember("Member2", "data2", doc.GetAllocator());


	//step 3. create an array in rapidjson
	rapidjson::Value arr(rapidjson::kArrayType);
	arr.PushBack(1, doc.GetAllocator());
	arr.PushBack(2, doc.GetAllocator());
	arr.PushBack(3, doc.GetAllocator());
	arr.PushBack(4, doc.GetAllocator());
	arr.PushBack(5, doc.GetAllocator());

	doc.AddMember("Array", arr, doc.GetAllocator());

	//step 3.1 you can have an array inside another array

	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("child", "datachild", doc.GetAllocator());

	doc.AddMember("Child object", object, doc.GetAllocator());

	//step 3.2 add child array to main array


	//step 3.3 add the array to the doc (don't forget to name it)


	//step 4. Create Another Object




	//step 4.1 add the new object back to the document


	//step 5. Creating Object using a function
	rapidjson::Value object2 = CreateObjectFunction(doc);
	doc.AddMember("member2", object2, doc.GetAllocator());


	{//ignore this in part 1
		rapidjson::Value value = Serialize(demo, doc);
		doc.AddMember("DemoClass", value, doc.GetAllocator());
	}

	//last step fill up this function
	WriteToFile(doc, "test.json");


	WriteToConsole(doc);
	//for part 3
	DemoClass newDemoClass;
	FileLoadingCode(newDemoClass, "test.json");
	std::cout << "Demo Damage: " << newDemoClass.damage << std::endl;
	std::cout << "Demo Health: " << newDemoClass.health << std::endl;
	std::cout << "Demo Position x: " << newDemoClass.GetPosition().x << std::endl;
	std::cout << "Demo Position y: " << newDemoClass.GetPosition().y << std::endl;
	std::cout << "Demo Position z: " << newDemoClass.GetPosition().z << std::endl;
}