#pragma once
/* !
@file		texture.h
@author		louishetong.wang@digipen.edu
@date		5/10/2022

This file implements functionality for texture loading and displaying into the viewport

*//*__________________________________________________________________________*/

#ifndef TEXTURE_H_
#define TEXTURE_H_

struct Texture
{
	int width;
	int height;
	unsigned int ID;
};

class TextureSystem
{
public:
	static TextureSystem* GetInstance();

	static void Generate(const char* filename);

	//void Delete(Texture& obj);

private:
	TextureSystem();

	static TextureSystem* _instance;
};

#endif // !TEXTURE_H_
