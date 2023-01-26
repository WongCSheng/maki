/*
File: Transform.h
Author: w.chongsheng@digipen.edu
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
		
		glm::vec2 position = glm::vec2(1);
		glm::vec2 scale = glm::vec2(1);
		float angle =0; //chong sheng louis help! //angle = rotation, suppose to be mat3 but we previously used float. plse hlp make consistent 
		void Set(glm::vec2 position = glm::vec2(0.f, 0.f), glm::vec2 scale = glm::vec2(1.f, 1.f), float rotation = 0);
		void SetPosition(glm::vec2 position);
		void SetScale(glm::vec2 scale);
		void SetRotation(float rotation);

		void Translating(glm::vec2 translate);
		void Rotating(float rotate);
		void Scaling(float scale);

		

		glm::mat4 Get()
		{

			glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

			return translation * scal * rotation;
		}

	private:
		/*gfxVector2 Position;
		gfxMatrix3 Rotation;
		gfxVector2 Scale;*/
		glm::vec2 testpostion;
		Object::GameObjectProperty* owner;

		//Transform* instance; //Singleton (Don't really need)
	};
}

#endif