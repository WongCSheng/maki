#ifndef BLUR_SHADER_H
#define BLUR_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>

#include "Matrix4f.h"

using std::map;
using std::string;

// Simple Blur
class BlurShader : public ShaderProgram
{
public:
	BlurShader(void);
	virtual ~BlurShader(void);

	void load_ColorIndex(unsigned colorIndex);

protected:
	virtual void getAllUniformLocations(void);

private:
	map<string, unsigned int> m_parameters;
};
#endif
