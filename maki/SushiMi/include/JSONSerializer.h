#pragma once

#ifndef JSERIALIZE_H
#define JSERIALIZE_H
class Serializer {

public:
	//void Serialize (const std::string& filepath);
	
	//use when debugging
	bool DeserializeAndPrintConsole(const std::string& filepath); 

	//set value to gameobject if all property names match
	template<typename gameObject>
	bool DeserializeAndSetValues(gameObject& obj, const std::string& filepath);

};


#endif