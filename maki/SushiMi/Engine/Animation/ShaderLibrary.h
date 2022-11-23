#pragma once
#include "ShaderProgram.h"
#include "../include/common_headers.hpp"
using namespace std;


class ShaderLibrary
{
public:
	ShaderLibrary();

	~ShaderLibrary();

	ShaderProgram* Textured_Shader();

	ShaderProgram* Colored_Shader();

private:

	map<string, ShaderProgram*> programs;
};

static unique_ptr<ShaderLibrary> Shaders;