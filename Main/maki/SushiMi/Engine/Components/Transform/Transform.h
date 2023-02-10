/*
File: Transform.h
Author: w.chongsheng@digipen.edu
<<<<<<< HEAD
=======
co-Author:  Aurelia Chong 
email:		fei.x@digipen.edu
>>>>>>> M3-submission-branch
Description: Header for Transform.cpp
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

<<<<<<< HEAD
#include "../Component.h"
#include "../Headers/Math_Header.h"
#include <vector>

namespace Core
{
	class Transform : public Component
=======
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
>>>>>>> M3-submission-branch
	{
	public:
		Transform();
		~Transform();

		void Init();
<<<<<<< HEAD
		void Serialise(const std::string name);

		const gfxMatrix3 TransformMat();
		void Set(gfxVector2 position = gfxVector2(0.f, 0.f), gfxVector2 scale = gfxVector2(1.f, 1.f), gfxMatrix3 rotation = gfxMatrix3());
		void SetPosition(gfxVector2 position);
		void SetScale(gfxVector2 scale);
		void SetRotation(gfxMatrix3 rotation);
		void SetForward(gfxVector2 forward);

		void Translate(gfxVector2 translate);
		void Rotate(gfxMatrix3 rotate);
		void Scale(float scale);

		const gfxVector2& Forward(const double dt);

		gfxVector2 localposition;
		gfxMatrix3 localrotation;
		gfxVector2 localscale;
		gfxVector2 worldposition;
		gfxMatrix3 worldrotation;
		gfxVector2 worldscale;

	private:
		gfxVector2 forward;

		gfxMatrix3 T, R, S;
=======

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
>>>>>>> M3-submission-branch

		Object::GameObjectProperty* owner;

		//Transform* instance; //Singleton (Don't really need)
	};
}

#endif