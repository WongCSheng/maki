/* !
@file		fonts.h
@author		louishetong.wang@digipen.edu
@date		5/10/2022

This file implements functionality for fonts using freetype for showing words on screen

*//*__________________________________________________________________________*/
#include <../freetype/include/ft2build.h>
#include FT_FREETYPE_H

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
	std::map<char, Character> Characters;
	void init();
	
};