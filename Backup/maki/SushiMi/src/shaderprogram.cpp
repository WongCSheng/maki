#include "../include/shaderprogram.h"

int ShaderProgram::Result = GL_FALSE;
int ShaderProgram::Result_log = GL_FALSE;

ShaderProgram::ShaderProgram()
{
	ProgramID = VertexShaderID = FragmentShaderID = NULL;
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

GLboolean ShaderProgram::CompileLinkValidate(std::vector<std::pair<GLenum, std::string>> vec) {
	for (auto& elem : vec) {
		if (GL_FALSE == CompileShaderFromFile(elem.first, elem.second.c_str())) {
			return GL_FALSE;
		}
	}
	if (GL_FALSE == Link()) {
		return GL_FALSE;
	}
	if (GL_FALSE == Validate()) {
		return GL_FALSE;
	}

	return GL_TRUE;
}

GLboolean ShaderProgram::Validate() {
	if (pgm_handle <= 0 || is_linked == GL_FALSE) {
		return GL_FALSE;
	}

	glValidateProgram(pgm_handle);
	GLint status;
	glGetProgramiv(pgm_handle, GL_VALIDATE_STATUS, &status);
	if (GL_FALSE == status) {
		log_string = "Failed to validate shader program for current OpenGL context\n";
		GLint log_len;
		glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_len);
		if (log_len > 0) {
			GLchar* log_str = new GLchar[log_len];
			GLsizei written_log_len;
			glGetProgramInfoLog(pgm_handle, log_len, &written_log_len, log_str);
			log_string += log_str;
			delete[] log_str;
		}
		return GL_FALSE;
	}
	else {
		return GL_TRUE;
	}
}

GLboolean
ShaderProgram::FileExists(std::string const& file_name) {
	std::ifstream infile(file_name); return infile.good();
}

GLuint ShaderProgram::GetHandle() const {
	return pgm_handle;
}

GLboolean ShaderProgram::IsLinked() const {
	return is_linked;
}

std::string ShaderProgram::GetLog() const {
	return log_string;
}

GLboolean
ShaderProgram::CompileShaderFromFile(GLenum shader_type, const std::string& file_name) {
	if (GL_FALSE == FileExists(file_name)) {
		log_string = "File not found";
		return GL_FALSE;
	}
	if (pgm_handle <= 0) {
		pgm_handle = glCreateProgram();
		if (0 == pgm_handle) {
			log_string = "Cannot create program handle";
			return GL_FALSE;
		}
	}

	std::ifstream shader_file(file_name, std::ifstream::in);
	if (!shader_file) {
		log_string = "Error opening file " + file_name;
		return GL_FALSE;
	}
	std::stringstream buffer;
	buffer << shader_file.rdbuf();
	shader_file.close();
	return CompileShaderFromString(shader_type, buffer.str());
}

GLboolean
ShaderProgram::CompileShaderFromString(GLenum shader_type,
	const std::string& shader_src) {
	if (pgm_handle <= 0) {
		pgm_handle = glCreateProgram();
		if (0 == pgm_handle) {
			log_string = "Cannot create program handle";
			return GL_FALSE;
		}
	}

	GLuint shader_handle = 0;
	switch (shader_type) {
	case VERTEX_SHADER: shader_handle = glCreateShader(GL_VERTEX_SHADER); break;
	case FRAGMENT_SHADER: shader_handle = glCreateShader(GL_FRAGMENT_SHADER); break;
	case GEOMETRY_SHADER: shader_handle = glCreateShader(GL_GEOMETRY_SHADER); break;
	case TESS_CONTROL_SHADER: shader_handle = glCreateShader(GL_TESS_CONTROL_SHADER); break;
	case TESS_EVALUATION_SHADER: shader_handle = glCreateShader(GL_TESS_EVALUATION_SHADER); break;
		//case COMPUTE_SHADER: shader_handle = glCreateShader(GL_COMPUTE_SHADER); break;
	default:
		log_string = "Incorrect shader type";
		return GL_FALSE;
	}

	// load shader source code into shader object
	GLchar const* shader_code[] = { shader_src.c_str() };
	glShaderSource(shader_handle, 1, shader_code, NULL);

	// compile the shader
	glCompileShader(shader_handle);

	// check compilation status
	GLint comp_result;
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &comp_result);
	if (GL_FALSE == comp_result) {
		log_string = "Vertex shader compilation failed\n";
		GLint log_len;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_len);
		if (log_len > 0) {
			GLchar* log = new GLchar[log_len];
			GLsizei written_log_len;
			glGetShaderInfoLog(shader_handle, log_len, &written_log_len, log);
			log_string += log;
			delete[] log;
		}
		return GL_FALSE;
	}
	else { // attach the shader to the program object
		glAttachShader(pgm_handle, shader_handle);
		return GL_TRUE;
	}
}

GLboolean ShaderProgram::Link() {
	if (GL_TRUE == is_linked) {
		return GL_TRUE;
	}
	if (pgm_handle <= 0) {
		return GL_FALSE;
	}

	glLinkProgram(pgm_handle); // link the various compiled shaders

	// verify the link status
	GLint lnk_status;
	glGetProgramiv(pgm_handle, GL_LINK_STATUS, &lnk_status);
	if (GL_FALSE == lnk_status) {
		log_string = "Failed to link shader program\n";
		GLint log_len;
		glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_len);
		if (log_len > 0) {
			GLchar* log_str = new GLchar[log_len];
			GLsizei written_log_len;
			glGetProgramInfoLog(pgm_handle, log_len, &written_log_len, log_str);
			log_string += log_str;
			delete[] log_str;
		}
		return GL_FALSE;
	}
	return is_linked = GL_TRUE;
}

unsigned int ShaderProgram::getUniformLocation(const char* location)
{
	return glGetUniformLocation(ProgramID, location);
}

void ShaderProgram::setuniform(GLchar const* name, GLfloat x, GLfloat y)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	float arr[2];
	arr[0] = x;
	arr[1] = y;
	glUniform2fv(location, 1, arr);
}

void ShaderProgram::setuniform(GLchar const* name, gfxMatrix3 mat)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform3fv(location, 1, &mat.a[0]);
	}
	else
	{
	std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}
}

void ShaderProgram::setuniform(GLchar const* name, GLfloat value)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform1f(location, value);
	}
	else
	{
		std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}

}

void ShaderProgram::setuniform(GLchar const* name, GLboolean value)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform1i(location, value);
	}
	else
	{
		std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}

}

void ShaderProgram::setuniform(GLchar const* name, GLint value)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform1i(location, value);
	}
	else
	{
		std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}

}

void ShaderProgram::setuniform(GLchar const* name, gfxVector2 const& value)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform2f(location, value.x, value.y);
	}
	else
	{
		std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}
}

void ShaderProgram::setuniform(GLchar const* name, gfxVector3 const& value)
{
	GLint location = glGetUniformLocation(ProgramID, name);
	if (location >= 0)
	{
		glUniform3f(location, value.x, value.y, value.z);
	}
	else
	{
		std::cout << "uniform variable" << name << " does not exist" << std::endl;
	}
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