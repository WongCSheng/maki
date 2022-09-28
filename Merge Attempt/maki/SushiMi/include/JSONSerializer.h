#pragma once

#include "../Headers/STL_Header.h"
#include "../Headers/RapidJSON_Header.h"

class Serializer {

public:

	//serialize everything
	void Serialize(const std::string& filepath);
	//set value to gameobject if all property names match
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

//debugging after serializing
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