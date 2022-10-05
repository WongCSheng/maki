
/*                                                                   includes
----------------------------------------------------------------------------- */
#include "fonts.h"
#include <iostream>
/*--------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
/*
void Font::init()
{
	FT_Library ft;	//init the freetype library ft
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR: Unable to init freetype library." << std::endl;
	}
	FT_Face face;	//load font as a face
	if (FT_New_Face(ft, "fonts/arial.tff", 0, &face))	//try to load arial font here
	{
		std::cout << "ERROR: Arial not found!" << std::endl;
	}
}
*/