#pragma once
<<<<<<< HEAD
#include <string>
#include <iostream>
using namespace std;
struct fakemat4;
=======
/*!
@file		ShaderProgram.h
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Redesigned Shader program that compiles the shaders, create them and
			attach them to the shader programs using their IDs. SendMat4 will
			set uniform location for their uniform variables(model_matrx or projection).
*//*__________________________________________________________________________*/
#include <string>
#include <iostream>
//using namespace std;
#include "../../glm/glm/mat4x4.hpp"
>>>>>>> M3-submission-branch
class ShaderProgram
{
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader);

	~ShaderProgram();

	void use();

<<<<<<< HEAD
	void Send_Mat4(const char* name, fakemat4& mat);
=======
	void Send_Mat4(const char* name, glm::mat4 mat);
>>>>>>> M3-submission-branch

private:
	void checkerorr(unsigned int shader_id, std::string type);
	unsigned int ID;
};