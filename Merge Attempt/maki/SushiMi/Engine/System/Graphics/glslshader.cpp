/* !
@file    glslshader.h
@author  louishetong.wang@digipen.edu
@date    20/09/2022

This file contains definitions of member functions of class GLShader.
There are many functions to get the location of the uniform and linking to
the pgmhandler

*//*__________________________________________________________________________*/
#include <../Engine/System/Graphics/glslshader.h>
#include <iomanip>

GLint
GLSLShader::GetUniformLocation(GLchar const* name) {    //return location of uniform variable
    return glGetUniformLocation(pgm_handle, name);
}

GLboolean
GLSLShader::FileExists(std::string const& file_name) {  //check if file exists
    std::ifstream infile(file_name); return infile.good();
}

void
GLSLShader::DeleteShaderProgram() {                     //delete program handler
    if (pgm_handle > 0) {
        glDeleteProgram(pgm_handle);
    }
}

GLboolean
GLSLShader::CompileLinkValidate(std::vector<std::pair<GLenum, std::string>> vec) {

    pgm_handle = glCreateProgram();                                                 //creates a program object if no handle is found
    if (0 == pgm_handle) {//pgm_handle <= 0
        //std::cout <<"Program error: " << std::hex << x << std::endl;
        log_string = "Cannot create program handle";
        return GL_FALSE;
    }

    std::cout << "Program created " << vec[0].second << "[ " << pgm_handle << "]\n";
    m_name = vec[0].second;
    for (auto& elem : vec) {
        if (GL_FALSE == CompileShaderFromFile(elem.first, elem.second.c_str())) {       //if not able to compile from file
            return GL_FALSE;
        }
    }
    is_linked = false;
    if (GL_FALSE == Link()) {                                                           //if not able to link
        return GL_FALSE;
    }
    if (GL_FALSE == Validate()) {                                                       //if not able to validate
        return GL_FALSE;
    }
    PrintActiveAttribs();
    PrintActiveUniforms();

    return GL_TRUE;
}

GLboolean
GLSLShader::CompileShaderFromFile(GLenum shader_type, const std::string& file_name) {   //compiles the shader from file
    if (GL_FALSE == FileExists(file_name)) {                                            //if file not found, return false with err_log
        log_string = "File not found";
        return GL_FALSE;
    }
    //if (pgm_handle <= 0) {
        //pgm_handle = glCreateProgram();                                                 //creates a program object if no handle is found
        //if (0 == pgm_handle) {
        //    log_string = "Cannot create program handle";
        //    return GL_FALSE;
        //}
    //}

    std::ifstream shader_file(file_name, std::ifstream::in);
    if (!shader_file) {
        log_string = "Error opening file " + file_name;
        return GL_FALSE;
    }
    std::stringstream buffer;
    buffer << shader_file.rdbuf();                                                     //returns pointer to the object to speed up file operations
    shader_file.close();
    return CompileShaderFromString(shader_type, buffer.str());                         //create shader depending on the shader type
}

GLboolean
GLSLShader::CompileShaderFromString(GLenum shader_type,
    const std::string& shader_src) {
    //if (pgm_handle <= 0) {
    //    pgm_handle = glCreateProgram();
    //    if (0 == pgm_handle) {
    //        log_string = "Cannot create program handle";
    //        return GL_FALSE;
    //    }
    //}

    GLuint shader_handle = 0;
    switch (shader_type) {
    case VERTEX_SHADER: shader_handle = glCreateShader(GL_VERTEX_SHADER); break;
    case FRAGMENT_SHADER: shader_handle = glCreateShader(GL_FRAGMENT_SHADER); break;

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

GLboolean GLSLShader::Link() {
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
// glUseProgram installs the program object specified by program as part of current rendering state. 
// One or more executables are created in a program object by successfully attaching shader objects to it with glAttachShader, 
// successfully compiling the shader objects with glCompileShader, and successfully linking the program object with glLinkProgram.
void GLSLShader::Use() {
    if (pgm_handle > 0 && is_linked == GL_TRUE) {
        glUseProgram(pgm_handle);
    }
}
// make sure that the last used shader is not active anymore, and it will use the fixed-function pipeline
void GLSLShader::UnUse() {
    glUseProgram(0);
}
// to validate if there is program handler existed and is linked to the program
GLboolean GLSLShader::Validate() {
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
// get program handler
GLuint GLSLShader::GetHandle() const {
    return pgm_handle;
}
// check if is linked or not
GLboolean GLSLShader::IsLinked() const {
    return is_linked;
}
// get the output log
std::string GLSLShader::GetLog() const {
    return log_string;
}
// associate a generic vertex attribute index with a named attribute variable
void GLSLShader::BindAttribLocation(GLuint index, GLchar const* name) {
    glBindAttribLocation(pgm_handle, index, name);
}
//bind a user-defined varying out variable to a fragment shader color number
void GLSLShader::BindFragDataLocation(GLuint color_number, GLchar const* name) {
    glBindFragDataLocation(pgm_handle, color_number, name);
}
//Specify the value of a uniform variable for the current program object(boolean)
void GLSLShader::SetUniform(GLchar const* name, GLboolean val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1i(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(int)
void GLSLShader::SetUniform(GLchar const* name, GLint val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    std::cout << "getting unifrom location for " << m_name << "@ " << loc << std::endl;
    if (loc >= 0) {
        glUniform1i(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(GLuint)
void GLSLShader::SetUniform(GLchar const* name, GLuint val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1ui(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(float)
void GLSLShader::SetUniform(GLchar const* name, GLfloat val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1f(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(2 floats)
void GLSLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform2f(loc, x, y);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(vec2)
void GLSLShader::SetUniform(GLchar const* name, glm::vec2 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform2f(loc, val.x, val.y);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}
//Specify the value of a uniform variable for the current program object(vec3)
void GLSLShader::SetUniform(GLchar const* name, glm::vec3 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform3f(loc, val.x, val.y, val.z);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}


//Specify the value of a uniform variable for the current program object(mat3)
void GLSLShader::SetUniform(GLchar const* name, glm::mat3 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &val[0][0]);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

//Specify the value of a uniform variable for the current program object(vec4)
void GLSLShader::SetUniform(GLchar const* name, glm::vec4 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform4f(loc, val.x, val.y, val.z, val.w);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

// display the list of active vertex attributes used by vertex shader
void GLSLShader::PrintActiveAttribs() const {
#if 1
    GLint max_length, num_attribs;
    glGetProgramiv(pgm_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length);
    glGetProgramiv(pgm_handle, GL_ACTIVE_ATTRIBUTES, &num_attribs);
    GLchar* pname = new GLchar[max_length];
    std::cout << "Index\t|\tName\n";
    std::cout << "----------------------------------------------------------------------\n";
    for (GLint i = 0; i < num_attribs; ++i) {
        GLsizei written;
        GLint size;
        GLenum type;
        glGetActiveAttrib(pgm_handle, i, max_length, &written, &size, &type, pname);
        GLint loc = glGetAttribLocation(pgm_handle, pname);
        std::cout << loc << "\t\t" << pname << std::endl;
    }
    std::cout << "----------------------------------------------------------------------\n";
    delete[] pname;

#else
    GLint numAttribs;
    glGetProgramInterfaceiv(pgm_handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);
    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
    std::cout << "Active attributes:" << std::endl;
    for (GLint i = 0; i < numAttribs; ++i) {
        GLint results[3];
        glGetProgramResourceiv(pgm_handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

        GLint nameBufSize = results[0] + 1;
        GLchar* pname = new GLchar[nameBufSize];
        glGetProgramResourceName(pgm_handle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, pname);
        //   std::cout << results[2] << " " << pname << " " << getTypeString(results[1]) << std::endl;
        std::cout << results[2] << " " << pname << " " << results[1] << std::endl;
        delete[] pname;
    }
#endif
}
// display the list of active uniform variables
void GLSLShader::PrintActiveUniforms() const {
    GLint max_length;
    glGetProgramiv(pgm_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
    GLchar* pname = new GLchar[max_length];
    GLint num_uniforms;
    glGetProgramiv(pgm_handle, GL_ACTIVE_UNIFORMS, &num_uniforms);
    std::cout << "Location\t|\tName\n";
    std::cout << "----------------------------------------------------------------------\n";
    for (GLint i = 0; i < num_uniforms; ++i) {
        GLsizei written;
        GLint size;
        GLenum type;
        glGetActiveUniform(pgm_handle, i, max_length, &written, &size, &type, pname);
        GLint loc = glGetUniformLocation(pgm_handle, pname);
        std::cout << loc << "\t\t" << pname << std::endl;
    }
    std::cout << "----------------------------------------------------------------------\n";
    delete[] pname;
}
