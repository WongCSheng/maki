#include "Texture.h"
#include "TextureData.h"
#include <fstream>
#include <iostream>

Texture::Texture(GLenum TextureTarget, const std::string& FileName) : m_textureTarget(TextureTarget), m_filename(FileName), t_data(NULL)
{
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &m_textureID);
}

bool Texture::load(bool gamma, GLint param_minF, GLint param_maxF, GLint param_S, GLint param_T)
{
	int width, height;
	
	image = SOIL_load_image(m_filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &m_textureID);
	//m_textureID = SOIL_load_OGL_texture(m_filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (m_textureID == 0)
	{
		std::cout << "SOIL LOADING ERROR" << std::endl;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_minF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_maxF);

	float maxAnisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param_S);       // try change to GL_CLAMP or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param_T);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(image);
	return true;

	// Old TGA Loader
	/*
	decodeTextureFile();

	glGenTextures(1, &m_textureID);
	t_data->setTextureData(m_textureID);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	GLint interform = GL_RGB;
	GLint interform2 = GL_RGBA;

	if (gamma)
	{
		interform = GL_SRGB;
		interform = GL_SRGB_ALPHA;
	}

	if (t_data->getBytesPerPixel() == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, interform, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
	}

	else //bytesPerPixel == 4
	{
		// try change the BGRA to RGBA     // data is the buffer that thin matrix is talking about
		glTexImage2D(GL_TEXTURE_2D, 0, interform2, t_data->getWidth(), t_data->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, t_data->getBuffer());
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_minF);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_maxF);

	float maxAnisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param_S);       // try change to GL_CLAMP or GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param_T);

	glGenerateMipmap(GL_TEXTURE_2D);

	t_data->cleanUpBuffer();

	glBindTexture(GL_TEXTURE_2D, 0);
	
	return true;
	*/
}

bool Texture::loadCubemap(vector<const GLchar*> faces)
{
	glGenTextures(1, &m_textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return m_textureID;
}

void Texture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(m_textureTarget, m_textureID);
}

void Texture::decodeTextureFile(void)
{

	
	/*
	// use string is ok de
	std::ifstream fileStream(m_filename, std::ios::binary);
	if (!fileStream.is_open())
	{
		std::cout << "Impossible to open " << m_filename << ". Are you in the right directory ?\n";
		return;
	}

	GLubyte		header[18];									// first 6 useful header bytes
	GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
	GLuint		imageSize;									    // for setting memory
	GLubyte *	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

	if (width <= 0 ||								// is width <= 0
		height <= 0 ||								// is height <=0
		(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
	{
		fileStream.close();							// close file on failure
		std::cout << "File header error.\n";
		return;
	}

	bytesPerPixel = header[16] / 8;						//divide by 8 to get bytes per pixel
	imageSize = width * height * bytesPerPixel;	// calculate memory required for TGA data

	data = new GLubyte[imageSize];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();

	t_data = new TextureData(texture, width, height, data, bytesPerPixel);
	*/
}

bool Texture::operator<(const Texture* other) const
{
	//compare memory
	return memcmp((void*)this, (void*)&other, sizeof(Texture))>0;
}