#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../include/common_headers.hpp"

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

	GLboolean CompileLinkValidate(std::vector<std::pair<GLenum, std::string>>);
  
  // This function does the following:
  // 1) Create a shader program object if one doesn't exist
  // 2) Using first parameter, create a shader object
  // 3) Load shader source code from file specified by second parameter to
  //    shader object
  // 4) Compile shader source by calling CompileShaderFromString
  // 5) Check compilation status and log any messages to data member 
  //    "log_string"
  // 6) If compilation is successful, attach this shader object to previously
  //    created shader program  object
  	GLboolean CompileShaderFromFile(GLenum shader_type, std::string const& file_name);

  // This function does the following:
  // 1) Create a shader program object if one doesn't exist
  // 2) Using first parameter, create a shader object
  // 3) Load the shader code from 2nd parameter to shader object
  // 4) Compile the shader source
  // 5) Check compilation status and log any messages to data member "log_string"
  // 6) If compilation is successful, attach this shader object to previously
  //    created shader program object ...
  	GLboolean CompileShaderFromString(GLenum shader_type, std::string const& shader_src);

  // Link shader objects attached to handle pgm_handle. This member function
  // will also verify the status of the link operation (successful or not?).
  // If the shader objects did not link into a program object, then the
  // member function must retrieve and write the program object's information
  // log to data member log_string. 
 	GLboolean Link();

	// check whether the executable shader program object can execute given the
  // current OpenGL state ...
  // See the glValidateProgram() reference page for more information
  // The function returns true if validatation succeeded 
	GLboolean Validate();

	// return the handle to the shader program object
	GLuint GetHandle() const;

	// have the different object code linked into a shader program?
	GLboolean IsLinked() const;

	// return logged information from the GLSL compiler and linker and
	// validation information obtained after calling Validate() ...
	std::string GetLog() const;
	unsigned int getUniformLocation(const char* location);
	void setuniform(GLchar const* name, GLfloat value); // gluniform1f
	void setuniform(GLchar const* name, GLboolean value); // gluniform2f
	void setuniform(GLchar const* name, GLint value); // gluniform 3fv
	void setuniform(GLchar const* name, GLfloat x, GLfloat y);
	void setuniform(GLchar const* name, gfxVector2 const& value);
	void setuniform(GLchar const* name, gfxVector3 const& value);
	void setuniform(GLchar const* name, gfxMatrix3 mat);

	enum ShaderType {
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
	};

	unsigned int ProgramID{}, VertexShaderID{}, FragmentShaderID{};
	static GLuint LoadShader(const char* file_path, GLenum type);\
	GLuint pgm_handle = 0;  // handle to linked shader program object
	GLboolean is_linked = GL_FALSE; // has the program successfully linked?
	std::string log_string; // log for OpenGL compiler and linker messages
	static int Result;
	static int Result_log;
	static std::map<std::string, ShaderProgram> shdrpgms; // singleton
private:

	// return true if file (given in relative path) exists, false otherwise
	GLboolean FileExists(std::string const& file_name);
};

#endif // !SHADER_PROGRAM_H_