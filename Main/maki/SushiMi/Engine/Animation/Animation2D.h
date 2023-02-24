#pragma once
/*!
@file		Animation2D.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Animation functions that reads the txt file for each animation type and using delta time, loop through the
			spritesheet corresponding to each animation. Eg: For animation type Run, it loops through the 7 running
			sprites in the spritesheet
*//*__________________________________________________________________________*/
#include "../Engine/System/Renderer.h"
#include <../glm/glm/vec4.hpp>
#include <vector>

namespace Core
{
	struct Texture;
	//using namespace std;
	enum class AnimationType
	{
		Idle,
		Run,
		Jump
	};

	class Animation2D
	{
	public:
		Animation2D(const char* filename);

		~Animation2D();


		void play(Texture& spritetexture, Core::vtx rectangle, double deltatime);

		void set_animation_speed(float newspeed);


	private:
		double anim_cursor;
		int current_frame_indx;
		int frames_count;
		float speed;

		std::vector<glm::vec4> frames;
	};

}