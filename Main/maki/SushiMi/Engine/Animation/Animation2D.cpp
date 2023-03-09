#include "Animation2D.h"

/*!
@file		Animation2D.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Animation functions that reads the txt file for each animation type and using delta time, loop through the
			spritesheet corresponding to each animation. Eg: For animation type Run, it loops through the 7 running
			sprites in the spritesheet
*//*__________________________________________________________________________*/
#include <string>
#include <sstream>
#include "../Components/Texture/Texture.h"
#include "../Engine/System/Renderer.h"
#include <../glew/include/GL/glew.h>
#include <../glm/glm/vec2.hpp>
#include <../Engine/System/Graphics/glhelper.h>


namespace Core
{
	Animation2D::Animation2D(const char* filename)
		: anim_cursor(0),
		current_frame_indx(0),
		speed(0.5f)
	{
		FILE* fp = nullptr;
		const int bufferlen = 255;
		char line[bufferlen];
		fopen_s(&fp, filename, "r");

		if (fp == nullptr)
		{
			printf("error in reading animation file \n");
		}
		else
		{
			while (fgets(line, bufferlen, fp))
			{
				std::vector<int> result;

				std::stringstream ss(line);
				std::string token;
				while (std::getline(ss, token, ','))
				{
					result.push_back(std::stoi(token));
				}

				glm::vec4 frame = glm::vec4(result[0], result[1], result[2], result[3]);
				frames.push_back(frame);
			}
		}

		frames_count = (int)frames.size();
		if (fp != NULL)
		fclose(fp);
	}

	Animation2D::~Animation2D()
	{

	}

	void Animation2D::play(Texture& spritetexture, Core::vtx rectangle, double deltatime)
	{
		anim_cursor += deltatime;

		if (anim_cursor > speed)
		{
			current_frame_indx = (current_frame_indx + 1) % frames_count;
			anim_cursor = 0;
		}

		glm::vec4 frame = frames[current_frame_indx];

		// normalization
		frame.x /= spritetexture.Texwidth;
		frame.y /= spritetexture.Texheight;
		frame.z /= spritetexture.Texwidth;
		frame.w /= spritetexture.Texheight;

		std::vector<glm::vec2> uv;

		uv = {
			glm::vec2(frame.x,frame.y),
			glm::vec2(frame.x, frame.y + frame.w),
			glm::vec2(frame.x + frame.z, frame.y),

			glm::vec2(frame.x + frame.z, frame.y),
			glm::vec2(frame.x, frame.y + frame.w),
			glm::vec2(frame.x + frame.z, frame.y + frame.w)
		};

		glBindVertexArray(rectangle.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, rectangle.UVBO);

		/*{ //realocation for memory
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_DYNAMIC_DRAW);
		}*/


		// best practice to send data to gpu memory..
		void* gpubuffer = nullptr;
		gpubuffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec2), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		memcpy(gpubuffer, uv.data(), 6 * sizeof(glm::vec2));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Animation2D::set_animation_speed(float newspeed)
	{
		speed = newspeed;
	}

}