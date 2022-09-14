#pragma once
#include "include/common_headers.hpp"

namespace Framework
{
	//Base serializer interface. 
	//Concrete serializers (Text, Xml, Binary) will implement this interface. 
	//This separates the serialization PROCESS from the serialization FORMAT.
	//The serializers only need to implement the serialization of fundamental
	//type to be used by the engine.

	class BaseSerializer
	{
	public:
		///Open the serialization stream from a file.
		virtual bool Open(const std::string& file) = 0;

		///These check if stream still has data.
		//pure virtual functions, overwrite them in derived class
		virtual bool IsGood() = 0;
		virtual void ReadInt(int& i) = 0;
		virtual void ReadFloat(float& f) = 0;
		virtual void ReadString(std::string& str) = 0;
	};

	//Serialization Operators 




	//Serialize the instance of a certain type using opened file stream
	template<typename type>
	inline void StreamRead(BaseSerializer& stream, type& typeInstance)
	{
		typeInstance.Serialize(stream);
	}

	//Using opened file stream, read a float value from it
	inline void StreamRead(BaseSerializer& stream, float& f)
	{
		stream.ReadFloat(f);
	}

	//Using opened file stream, read an int value from it
	inline void StreamRead(BaseSerializer& stream, int& i)
	{
		stream.ReadInt(i);
	}

	//Using opened file stream, read a string value from it
	inline void StreamRead(BaseSerializer& stream, std::string& str)
	{
		stream.ReadString(str);
	}


}