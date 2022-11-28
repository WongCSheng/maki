#pragma once
/* !
@file		fonts.h
@author		louishetong.wang@digipen.edu
@date		5/10/2022

This file implements functionality for fonts using freetype for showing words on screen

*//*__________________________________________________________________________*/

#include "../lib/glm-0.9.9.8/glm/glm/glm.hpp"
#include <map>
#include "../include/glslshader.h"

#ifndef FONT_H_
#define FONT_H_

class Font
{
public:
	struct Character
	{
		unsigned int	TextureID;			// ID handle of the glyph texture
		glm::ivec2		Size;				// Size of glyph
		glm::ivec2		Bearing;			// Offset from baseline to left/top of glyph
		unsigned int	Advance;			// Offset to advance to next glyph
	};
	static std::map<char, Character> Characters;	// Singleton
	static int init();
	static void RenderText(GLSLShader& s, std::string text, float x, float y, float scale, glm::vec3 color);

	class TextRenderer
	{
	public:
		// holds a list of pre-compiled Characters
		std::map<char, Character> Characters;
		// shader used for text rendering
		GLSLShader TextShader;
		// constructor
		TextRenderer(unsigned int width, unsigned int height);
		// pre-compiles a list of characters from the given font
		void Load(std::string font, unsigned int fontSize);
		// renders a string of text using the precompiled list of characters
		void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
	};
};



extern unsigned int VAO, VBO;

#endif // !FONT_H_
