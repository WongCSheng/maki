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
		///Open the serialization serializer from a file.
		virtual bool Open(const std::string& file) = 0;

		///These check if serializer still has data.
		//pure virtual functions, overwrite them in derived class
		virtual bool IsGood() = 0;
		virtual void ReadInt(int& i) = 0;
		virtual void ReadFloat(float& f) = 0;
		virtual void ReadString(std::string& str) = 0;
	};

	//Serialization Operators//
	
	//Serialize the instance of a certain type using base serializer class or derived class
	template<typename type>
	inline void StreamRead(BaseSerializer& serializer, type& typeInstance)
	{
		typeInstance.Serialize(serializer);

		//Serialize function comes from the object itself, e.g.
		/*void GameObject::Serialize(ISerializer& serializer)
		{
			StreamRead(serializer, HP);
			StreamRead(serializer, Speed);
			StreamRead(serializer, Armor);
			StreamRead(serializer, SpriteFile);
		};*/

	}

	//overloaded, float
	//Using opened file serializer, read a float value from it
	inline void StreamRead(BaseSerializer& serializer, float& f)
	{
		serializer.ReadFloat(f);
	}

	//overloaded, int
	//Using opened file serializer, read an int value from it
	inline void StreamRead(BaseSerializer& serializer, int& i)
	{
		serializer.ReadInt(i);
	}

	//overloaded, string
	//Using opened file serializer, read a string value from it
	inline void StreamRead(BaseSerializer& serializer, std::string& str)
	{
		serializer.ReadString(str);
	}
	
	//may need to expand in future (arrays, pointers etc?)

}