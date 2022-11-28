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
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void Init();
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

		Object::GameObjectProperty* owner;

		//Transform* instance; //Singleton (Don't really need)
	};
}

#endif