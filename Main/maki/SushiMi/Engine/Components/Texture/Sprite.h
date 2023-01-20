#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_


/*!
@file		Sprite.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Drawing of the sprite and animating of it is here
*//*__________________________________________________________________________*/
#include "../Engine/Components/Texture/Texture.h"
#include "../Engine/System/Renderer.h"
#include "../Engine/Components/Transform/sTransform.h"
#include "../Engine/Animation/Animation2D.h"

namespace Core
{
	class Sprite : public Component
	{
	public:
		Sprite(const char* filename);

		~Sprite();

		void draw();

		void draw(double deltatime, AnimationType type);

		void Add_animation(const char* filename);

		void Init();
		void Serialise(const std::string name);

		bool IsActive();
		void Activate();
		void Deactivate();
		void Remove();

		Transform transformation;

	private:
		Texture texture;
		vtx rectangle;

		std::vector<Animation2D*> anims;
	};
}
#endif
