#pragma once
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