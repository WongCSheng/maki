#include "ShaderProgram.h"

int ShaderProgram::Result = GL_FALSE;
int ShaderProgram::Result_log = GL_FALSE;

ShaderProgram::ShaderProgram()
{
	ProgramID = VertexShaderID = FragmentShaderID = NULL;
}

ShaderProgram::ShaderProgram(const char* vert_FP, const char* frag_FP)
{
	ProgramID = glCreateProgram();
	VertexShaderID = LoadShader(vert_FP, GL_VERTEX_SHADER);
	FragmentShaderID = LoadShader(frag_FP, GL_FRAGMENT_SHADER);

	//attach shaders to program
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	glLinkProgram(ProgramID);

	//validate program
	glValidateProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_VALIDATE_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &Result_log);
	//if have errors
	if (Result_log != NULL)
	{
		std::vector<char> ProgramErrorMessage(Result_log + 1);
		glGetProgramInfoLog(ProgramID, Result_log, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	cleanup();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(ProgramID);
}

void ShaderProgram::start_shader()
{
	glUseProgram(ProgramID);
}

void ShaderProgram::stop_shader()
{
	glUseProgram(0);
}

void ShaderProgram::cleanup()
{
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

unsigned int ShaderProgram::getUniformLocation(const char* location)
{
	return glGetUniformLocation(ProgramID, location);
}

void ShaderProgram::loadUniform_2v(unsigned int location, float x, float y)
{
	float arr[2];
	arr[0] = x;
	arr[1] = y;
	glUniform2fv(location, 1, arr);
}

void ShaderProgram::loaduniform_3m(unsigned int location, gfxMatrix3 mat)
{
	return glUniform3fv(location, 1, &mat.a[0]);
}

void ShaderProgram::loadUniform_1f(unsigned int location, float value)
{
	return glUniform1f(location, value);
}

GLuint ShaderProgram::LoadShader(const char* file_path, GLenum type)
{
	GLuint shaderID = glCreateShader(type);

	std::string shader_input;
	std::ifstream myfile(file_path, std::ios::in);
	if (myfile.is_open())
	{
		std::string line = "";
		while (getline(myfile, line))
		{
			shader_input += "\n" + line;
			myfile.close();
		}
	}
	else
	{
		std::cout << "Unable to open shader files" << std::endl;
	}

	std::cout << "Compiling shaders" << std::endl;
	char const* shaderSource = shader_input.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	//for debugging
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &Result_log);
	//if have errors
	if (Result_log != NULL)
	{
		std::vector<char> ProgramErrorMessage(Result_log + 1);
		glGetProgramInfoLog(shaderID, Result_log, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	return shaderID;
}