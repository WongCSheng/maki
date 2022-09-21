#pragma once
#include "../include/common_headers.hpp"

namespace Framework
{
	///Serializer for a simple text file format.
	class TextSerializer : public BaseSerializer
	{
	public:
		std::ifstream stream;

		//overwrite BaseSerializer pure virtual functions 
		virtual bool Open(const std::string& file); //open file into stream
		virtual bool IsGood(); //opening file has given no error flags
		virtual void ReadInt(int& i); //use to read int value
		virtual void ReadFloat(float& f); //use to read float value
		virtual void ReadString(std::string& str); //use to read string value
	};

}