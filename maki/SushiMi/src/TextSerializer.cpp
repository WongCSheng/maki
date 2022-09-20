#include "../include/common_headers.hpp"

namespace Framework
{
	bool TextSerializer::Open(const std::string& file)
	{
		//c_str() returns a pointer to an array that contains a null-terminated 
		//sequence of characters representing the current value of the basic_string object
		stream.open(file.c_str());
		return stream.is_open();
	}

	bool TextSerializer::IsGood()
	{
		return stream.good();
	}

	void TextSerializer::ReadInt(int& i)
	{
		stream >> i;
	}

	void TextSerializer::ReadFloat(float& f)
	{
		stream >> f;
	}

	void TextSerializer::ReadString(std::string& str)
	{
		stream >> str;
	}

}