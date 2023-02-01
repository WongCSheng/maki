/*
File: Transform.h
Author: w.chongsheng@digipen.edu
co-Author:  Aurelia Chong 
email:		fei.x@digipen.edu
Description: Header for Transform.cpp
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <../glm/glm/glm.hpp>
#include <../glm/glm/gtc/matrix_transform.hpp>
#include "../Component.h"
#include "../Headers/Math_Header.h"
//#include <vector>
//#include "../Engine/Serialiser/JSONSerializer.h"

namespace Core
{
	enum class Trans_Type
	{
		Local = 1,
		World
	};
	
	class Transform : public Component 
	{
	public:
		Transform();
		~Transform();

		void Init();

		//transform functions, derived from parent component
		 void Serialize (const std::string name) /*override*/; //write to json
		 void Deserialize(const rapidjson::Value& jsonObj) /*override*/; //parse in json(read from)
		
		float angle =0; //chong sheng louis help! //angle = rotation, suppose to be mat3 but we previously used float. plse hlp make consistent 
		void Set(glm::vec2 Position = glm::vec2(0.f, 0.f), glm::vec2 Scale = glm::vec2(1.f, 1.f), float Rotation = 0);
		void SetPosition(glm::vec2 position);
		void SetScale(glm::vec2 scale);
		void SetRotation(float rotation);

		void Translating(glm::vec2 translate);
		void Rotating(float rotate);
		void Scaling(float scale);

		

		glm::mat4 Get()
		{
			TranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 1.0f));
			RotationMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
			ScaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(Scale, 1.0f));

			return TranslateMat * RotationMat * ScaleMat;
		}

		glm::vec2 Position;
		glm::mat3 Rotation;
		glm::vec2 Scale;

		std::pair<int, int> grid_pos;
		/*glm::vec2 position = glm::vec2(1);
		glm::vec2 scale = glm::vec2(1);*/
	private:

		glm::mat4 TranslateMat;
		glm::mat4 RotationMat;
		glm::mat4 ScaleMat;

		Object::GameObjectProperty* owner;

		//Transform* instance; //Singleton (Don't really need)
	};
}

#endif