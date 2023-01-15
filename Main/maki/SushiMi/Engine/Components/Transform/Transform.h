/*
File: Transform.h
Author: w.chongsheng@digipen.edu
Description: Header for Transform.cpp
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../Component.h"
#include "../Headers/Math_Header.h"
#include <vector>

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
		void Serialise(const std::string name);

		void Set(gfxVector2 position = gfxVector2(0.f, 0.f), gfxVector2 scale = gfxVector2(1.f, 1.f), gfxMatrix3 rotation = gfxMatrix3(0.f));
		void SetPosition(gfxVector2 position);
		void SetScale(gfxVector2 scale);
		void SetRotation(gfxMatrix3 rotation);

		void Translating(gfxVector2 translate);
		void Rotating(gfxMatrix3 rotate);
		void Scaling(float scale);

	private:
		gfxVector2 Position;
		gfxMatrix3 Rotation;
		gfxVector2 Scale;

		Object::GameObjectProperty* owner;

		//Transform* instance; //Singleton (Don't really need)
	};
}

#endif