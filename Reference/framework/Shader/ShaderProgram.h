#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Vector3.h"
#include "Matrix4f.h"

class ShaderProgram
{
public:
	ShaderProgram(void);
	//vertex -> vertices points, etc. fragment -> color stuff, lighting stuff, etc
	ShaderProgram(const char* vertex_file_path, const char* fragment_file_path); //, char* geometry_file_path = NULL
	virtual ~ShaderProgram(void);

	void Start(void);
	void Stop(void);
	void CleanUp(void);

protected:
	unsigned int getUniformLocation(const char* uniformName);
	virtual void getAllUniformLocations(void) = 0;

	//loadU -> Load Uniform
	void loadU_1f(unsigned int location, float value); //glUniform1f
	void loadU_Vec3f(unsigned int location, Vector3 vec3df); //glUniform3f
	void loadU_1i(unsigned int location, int value); //glUniform1i
	void loadU_Bool(unsigned int location, bool value);
	void loadU_Mat4f(unsigned int location, Matrix4f matrix); //glUniformMatrix4fv
	void loadU_Vec2f(unsigned int location, float x, float y);

private:
	unsigned int ProgramID, VertexShaderID, FragmentShaderID;
	static GLuint LoadShader(const char* file_path, GLenum type);

	static int Result;
	static int InfoLoglength; //variable used to validate program
};
#endif