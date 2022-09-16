#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include <string.h>

#include "ShaderProgram.h"

GLint ShaderProgram::Result = GL_FALSE;
int ShaderProgram::InfoLoglength = 0;

ShaderProgram::ShaderProgram()
{
	ProgramID = VertexShaderID = FragmentShaderID = NULL;
}

ShaderProgram::ShaderProgram(const char * vertex_file_path, const char * fragment_file_path)
{
	VertexShaderID = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
	FragmentShaderID = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

	//if (geometry_file_path != NULL)
	//{
	//	GeometryShaderID = LoadShader(geometry_file_path, GL_GEOMETRY_SHADER);
	//}

	// Link the program
	printf("Linking program\n");
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	//if (geometry_file_path != NULL)
	//{
	//	glAttachShader(ProgramID, GeometryShaderID);
	//}

	glLinkProgram(ProgramID);

// Validate the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);

	// Check for error based on the combination of shaders and whether it can execute 
	// In an application with a lot of shaders, might want to validate before every draw call
	glValidateProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_VALIDATE_STATUS, &Result);

	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLoglength);

	if (InfoLoglength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLoglength + 1);
		glGetProgramInfoLog(ProgramID, InfoLoglength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	// delete shader
	CleanUp();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(ProgramID);
}

GLuint ShaderProgram::LoadShader(const char * file_path, GLenum type)
{
	// Create the shaders
	GLuint ShaderID = glCreateShader(type);

	// Read the Vertex Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(file_path, std::ios::in);

	if (ShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
		getchar();
		return 0;
	}

	// Compile Shader
	printf("Compiling shader : %s\n", file_path);
	char const * ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(ShaderID);

	// Check Shader
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLoglength);
	if (InfoLoglength > 0)
	{
		std::vector<char> ShaderErrorMessage(InfoLoglength + 1);
		glGetShaderInfoLog(ShaderID, InfoLoglength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}

	return ShaderID;
}

void ShaderProgram::Start(void)
{
	glUseProgram(ProgramID);
}

void ShaderProgram::Stop(void)
{
	glUseProgram(0);
}

void ShaderProgram::CleanUp(void)
{
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	//glDetachShader(ProgramID, GeometryShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	//glDeleteShader(GeometryShaderID);
}

unsigned int ShaderProgram::getUniformLocation(const char* uniformName)
{
	return glGetUniformLocation(ProgramID, uniformName);
}

void ShaderProgram::loadU_1f(unsigned int location, float value)
{
	glUniform1f(location, value); // 1f -> 1 float
}

void ShaderProgram::loadU_Vec3f(unsigned int location, Vector3 vec3f)
{
	glUniform3fv(location, 1, &vec3f.x); // 3fv -> 3 float vector
}

void ShaderProgram::loadU_1i(unsigned int location, int value)
{
	glUniform1i(location, value); // 1i -> 1 int
}

void ShaderProgram::loadU_Bool(unsigned int location, bool value)
{
	int toLoad = 0;
	if (value)
	{
		toLoad = 1;
	}

	glUniform1i(location, value);
}

void ShaderProgram::loadU_Mat4f(unsigned int location, Matrix4f matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.a[0]);
}

void ShaderProgram::loadU_Vec2f(unsigned int location, float x, float y)
{
	float arr[2];
	arr[0] = x;
	arr[1] = y;

	glUniform2fv(location, 1, arr);
}