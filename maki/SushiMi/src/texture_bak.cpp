/*!
@file		texture.cpp
@author		louishetong.wang@digipen.edu
@date		20/10/2022

This file implements functionality for the texture creation and implementation
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
/*
#include "../include/texture.h"
#include "../src/glslshader.cpp"
*/

/*--------------------------------------------------------------------------- */
/*
GLuint texobj{};
GLSLShader shdr_pgm;
void Texture::init()
{
	texobj = setup_texture("../textures/doge.jpg");
}

GLuint Texture::setup_texture(std::string path)
{
	GLuint width{ 256 }, height{ 256 }, bytes_per_texel{ 4 };

	std::ifstream is;
	//open solution with ios::binary or ios::in
	is.open(path, std::ios::binary | std::ios::in);
	// create new heapy memory pointed by ptr_texels with size of bytes
	char* ptr_texels = new char[width * height * bytes_per_texel];
	is.read(ptr_texels, (static_cast<std::streamsize>(width) * height) * bytes_per_texel);

	GLuint texobj_hdl;
	// define and initialize a handle to texture object that will
	// encapsulate two-dimensional textures
	glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
	// allocate GPU storage for texture image data loaded from file
	glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);
	// copy image data from client memory to GPU texture buffer memory
	glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
		GL_RGBA, GL_UNSIGNED_BYTE, ptr_texels);
	// client memory not required since image is buffered in GPU memory
	delete[] ptr_texels;
	// nothing more to do - return handle to texture object
	is.close();
	return texobj_hdl;
}

GLuint Texture::setup_shdrpgm()
{
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.emplace_back(std::make_pair(
		GL_VERTEX_SHADER,
		"../shaders/Texture.vert"));
	shdr_files.emplace_back(std::make_pair(
		GL_FRAGMENT_SHADER,
		"../shaders/Texture.frag"));
	
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs" << "\n";
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Texture::draw()
{
	glBindTextureUnit(6, texobj);	// bind texture obj to use texture image unit 6
	glTextureParameteri(texobj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texobj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glUseProgram(shdr_pgm.GetHandle());
	// tell fragment shader sampler uTex2d will use texture image unit 6
	GLuint tex_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 6);
}
*/