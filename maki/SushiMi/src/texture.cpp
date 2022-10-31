/*!
@file		texture.cpp
@author		louishetong.wang@digipen.edu
@date		20/10/2022

This file implements functionality for the texture creation and implementation
*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "../include/common_headers.hpp"
#include "../include/texture.h"
#include "../include/glapp.h"
#define STB_IMAGE_IMPLEMENTATION
#include <../stb-master/stb_image.h>
#include "../fonts.h"

/*--------------------------------------------------------------------------- */
GLuint texture;
int width, height, nrChannels;
void Texture::generateTexture()
{
	unsigned char* data = stbi_load("../textures/doge.jpg", &width, &height, &nrChannels, 0);		// load image
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}
	else
	{
		std::cout << " Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

void Texture::drawTexture()
{
	GLApp::shdrpgms["texture"].Use();
	//GLApp::shdrpgms["texture"].SetUniform("ourTexture", texture);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	/*
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(GLApp::shdrpgms["shdrpgm"].GetHandle());
	GLint utexture = glGetUniformLocation(GLApp::shdrpgms["shdrpgm"].GetHandle(), "ourTexture");
	*/
	
	glBindVertexArray(VAO);		// could it be this???

	glBindTextureUnit(GL_TEXTURE_2D, texture);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	//incorrectly enabled vertex attribute arrays
	glBindVertexArray(0);
	GLApp::shdrpgms["texture"].UnUse();
}