#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <SOIL\SOIL.h>

using std::vector;

class TextureData;

class Texture
{
public:
	Texture(GLenum TextureTarget, const std::string& FileName);
	~Texture(void);

	bool load(bool gamma = false, GLint param_minF = GL_LINEAR_MIPMAP_NEAREST, GLint param_maxF = GL_LINEAR_MIPMAP_NEAREST, GLint param_S = GL_CLAMP_TO_EDGE, GLint param_T = GL_CLAMP);

	bool loadCubemap(vector<const GLchar*> faces);

	void Bind(GLenum textureUnit);

	bool operator<(const Texture* other) const;

private:
	void decodeTextureFile(void);

	TextureData *t_data;
	std::string m_filename;
	GLenum m_textureTarget;	// Usually GL_TEXTURE_2D
	GLuint m_textureID;	// ID of the texture

	unsigned char* image;
};
#endif
