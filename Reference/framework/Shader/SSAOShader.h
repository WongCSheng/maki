#ifndef SSAO_SHADER_H
#define SSAO_SHADER_H

#include "ShaderProgram.h"

#include "Matrix4f.h"
#include "Vector3.h"

#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;
using std::string;

class SSAOShader :
	public ShaderProgram
{
public:
	SSAOShader(void);
	~SSAOShader(void);

	void load_ProjectionMatrix(Matrix4f &matrix);
	void load_TextureUnit(int positiondepth, int normal, int noise);
	void load_ScreenSize(float x, float y);

	void load_SampleKernel(vector<Vector3>&samples);
	void load_fov(float fov);


private:
	map<string, unsigned int> m_parameters;

protected:

	// get all the uniform location info into m_parameters[]
	void getAllUniformLocations(void);
};

#endif

