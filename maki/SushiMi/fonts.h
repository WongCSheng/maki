#pragma once
/* !
@file		fonts.h
@author		louishetong.wang@digipen.edu
@date		5/10/2022

This file implements functionality for fonts using freetype for showing words on screen

*//*__________________________________________________________________________*/
/*#ifndef FONT_H_
#define FONT_H_


#include <../freetype/include/ft2build.h>
#include <../glm/glm/glm.hpp>
#include <map>
#include <string>
#include FT_FREETYPE_H

class Font
{
public:
	struct Character
	{
		unsigned int	TextureID;			// ID handle of the glyph texture
		glm::vec2		Size;				// Size of glyph
		glm::vec2		Bearing;			// Offset from baseline to left/top of glyph
		unsigned int	Advance;			// Offset to advance to next glyph
	};
	static std::map<char, Character> Characters;	// Singleton
	void init();

}; */
//#endif // !FONT_H_
