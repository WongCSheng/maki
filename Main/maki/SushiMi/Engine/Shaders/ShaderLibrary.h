#pragma once
/*!
@file		ShaderLibrary.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Shader Library contains the vert and frag shaders for texture and colour shaders respectively.
			When shader programs are created, they will use the respective shader library
*//*__________________________________________________________________________*/
#include "ShaderProgram.h"
#include <map>
#include <memory>
//using namespace std;


class ShaderLibrary
{
public:
	ShaderLibrary();

	~ShaderLibrary();

	ShaderProgram* Textured_Shader();

	ShaderProgram* Colored_Shader();

private:

	std::map<std::string, ShaderProgram*> programs;
};

static std::unique_ptr<ShaderLibrary> Shaders;