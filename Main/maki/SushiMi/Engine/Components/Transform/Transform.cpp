/*
File: Transform.cpp
Author:		Wong Chong Sheng 35%
email:		w.chongsheng@digipen.edu
co-Author:  Chong Rui Xuan Aurelia 65%
email:		fei.x@digipen.edu
Description: Contains data for every type of transform. From meshes, bounding boxes, camera etc.
*/

#include "Transform.h"
#include "../Engine/Components/Component.h"
#include "../Engine/System/Transform/Transformer.h"

namespace Core
{
	Transform::Transform()
	{
		
	}


	Transform::~Transform()
	{
	}

	void Transform::Init()
	{
		
	}

	void Transform::Serialize(const std::string name)  
	{
	}

	void Transform::Deserialize(const rapidjson::Value& jsonObj) 
	{
		if (!jsonObj.HasMember("position") || !jsonObj["position"].IsArray() || jsonObj["position"].Size() < 2)
			std::cout << "Component of type Transform must have key 'position' with an array of size 2" << std::endl;
		//std::cout << "this line means i can read the json obj : " << jsonObj["position"].GetString() << std::endl;

		const rapidjson::Value& posArr = jsonObj["position"];

		for (int i = 0; i < 2; i++)
		{
			// here read json object data here using jsondoc parameter
			// jsonDoc["position"][0].GetDouble();
			if (!posArr[i].IsNumber())
				std::cout << "component of type Transform" << jsonObj["position"].GetString() << std::endl /* "position[" + std::to_string(i) + "]", "number" */;
			//std::cout << "JSONSerializer DeserializeLevel: " << filepath << " does not start with a JSON object" << std::endl;
			//ok so position is a number. then how can i read it?
			//it seems like im unable to get a single string from the file?

			float value = posArr[i].GetFloat();
			if (i == 0)
				Position.x = value; //rmb to uncomment
			else
				Position.y = value; //rmb to uncomment
		}

		std::cout << "Pos X: " << Position.x << "        " << "Pos Y: " << Position.y << "\n";

		if (!jsonObj.HasMember("rotation") || !jsonObj["rotation"].IsNumber())
			std::cout << "Component of type Transform must have key 'rotation' with a number value." << std::endl;

		 angle = jsonObj["rotation"].GetFloat(); //rmb to uncomment

		if (!jsonObj.HasMember("scale") || !jsonObj["scale"].IsArray() || jsonObj["scale"].Size() < 2)
			std::cout << "Component of type Transform must have key 'scale' with an array of size 2" << std::endl;

		const rapidjson::Value& scaleArr = jsonObj["scale"];
		for (int i = 0; i < 2; i++) {
			if (!scaleArr[i].IsNumber())
			{

				std::cout << "component of type Transform" << jsonObj["scale"].GetString() << "scale[" + std::to_string(i) + "]", "number";
			}

			float value = scaleArr[i].GetFloat();
			if (i == 0)
				Scale.x = value;
			else
				Scale.y = value;
		}

		std::cout << "Deserializing Tranform Component! \n";
	}



	void Transform::Set(glm::vec2  position, glm::vec2  scale, float rotation)
	{
		this->Position = position;
		this->Scale = scale;
		this->angle = rotation;
	}

	void Transform::SetPosition(glm::vec2 position)
	{
		this->Position = position;
	}

	void Transform::SetScale(glm::vec2 scale)
	{
		this->Scale = scale;
	}

	void Transform::SetRotation(float rotation)
	{
		this->angle = rotation;
	}

	void Transform::Translating(glm::vec2 translate)
	{
		this->Position += translate;
	}

	void Transform::Rotating(float rotate)
	{
		angle *= rotate;
	}

	void Transform::Scaling(float scale)
	{
		angle *= scale;
	}
}