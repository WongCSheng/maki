#pragma once
#include "include/common_headers.hpp"

namespace Framework
{
	///Serializer for a simple text file format.
	class TextSerializer : public BaseSerializer
	{
	public:
		std::ifstream stream;
		virtual bool Open(const std::string& file);
		virtual bool IsGood();
		virtual void ReadInt(int& i);
		virtual void ReadFloat(float& f);
		virtual void ReadString(std::string& str);
	};

}