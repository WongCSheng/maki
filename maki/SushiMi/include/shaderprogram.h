#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../Headers.h"

#include "../Vector.h"
#include "../Matrix.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vert_FP, const char* frag_FP);
	virtual ~ShaderProgram();

	void start_shader();
	void stop_shader();
	void cleanup();

	unsigned int getUniformLocation(const char* location);
	void loadUniform_1f(unsigned int location, float value); // gluniform1f
	void loadUniform_2v(unsigned int location, float x, float y); // gluniform2f
	void loaduniform_3m(unsigned int location, gfxMatrix3 mat); // gluniform 3fv

	unsigned int ProgramID{}, VertexShaderID{}, FragmentShaderID{};
	static GLuint LoadShader(const char* file_path, GLenum type);
	static int Result;
	static int Result_log;
};

#endif // !SHADER_PROGRAM_H_