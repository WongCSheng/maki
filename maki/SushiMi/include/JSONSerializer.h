#pragma once

#ifndef JSERIALIZE_H
#define JSERIALIZE_H
class Serializer {

public:
	//void Serialize (const std::string& filepath);

	bool Deserialize(const std::string& filepath);


};

//void WriteToConsole(rapidjson::Document& doc)
//{
//	rapidjson::StringBuffer sb;
//	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
//	writer.SetFormatOptions(rapidjson::PrettyFormatOptions::kFormatSingleLineArray);
//
//	doc.Accept(writer);
//	std::cout << sb.GetString() << std::endl;
//}
#endif