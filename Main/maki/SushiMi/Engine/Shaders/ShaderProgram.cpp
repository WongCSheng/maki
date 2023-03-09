#include "ShaderProgram.h"
/*!
@file		ShaderProgram.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Redesigned Shader program that compiles the shaders, create them and
			attach them to the shader programs using their IDs. SendMat4 will
			set uniform location for their uniform variables(model_matrx or projection).
*//*__________________________________________________________________________*/
#include "../../glew/include/GL/glew.h"
ShaderProgram::ShaderProgram(std::string vertex_shader, std::string fragment_shader)
{
	// compile shader ..
	unsigned int vertex, fragment;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vtx_source_ptr = vertex_shader.c_str();
	glShaderSource(vertex, 1, &vtx_source_ptr, NULL);
	glCompileShader(vertex);
	checkerorr(vertex, "VERTEX");

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fs_source_ptr = fragment_shader.c_str();
	glShaderSource(fragment, 1, &fs_source_ptr, NULL);
	glCompileShader(fragment);
	checkerorr(vertex, "FRAGMENT");

	// shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);

	glLinkProgram(ID);
	checkerorr(ID, "PROGRAM");


	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(ID);
}

GLuint ShaderProgram::get_hdl()
{
	return ID;
}

void ShaderProgram::use()
{
	glUseProgram(ID);
}

void ShaderProgram::Send_Mat4(const char* name, glm::mat4 mat)
{
	auto location = glGetUniformLocation(ID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::Send_Alpha(const char* name, float alpha)
{
	auto location = glGetUniformLocation(ID, name);
	glUniform1f(glGetUniformLocation(location, "alpha"), alpha);
}

void ShaderProgram::checkerorr(unsigned int shader_id, std::string type)
{
	int success;
	char infolog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader_id, 1024, NULL, infolog);
			std::cout << "ERORR type : " << type << std::endl;
			std::cout << "ERORR : " << infolog << std::endl;
			std::cout << "==================================" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader_id, 1024, NULL, infolog);
			std::cout << "ERORR type : " << type << std::endl;
			std::cout << "ERORR : " << infolog << std::endl;
			std::cout << "==================================" << std::endl;
		}
	}
}
