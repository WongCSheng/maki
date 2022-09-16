#include "SSAOShader.h"
#include <sstream>

SSAOShader::SSAOShader(void) : ShaderProgram("Shader//ssaoShader.vs", "Shader//ssaoShader.fs")
{
	getAllUniformLocations();
}

SSAOShader::~SSAOShader(void)
{
}

void SSAOShader::getAllUniformLocations(void)
{
	m_parameters["U_PROJECTION"] = getUniformLocation("Projection");

	m_parameters["U_TEXTUREUNIT_POS"] = getUniformLocation("gPositionDepth");
	m_parameters["U_TEXTUREUNIT_NORMAL"] = getUniformLocation("gNormal");
	m_parameters["U_TEXTUREUNIT_NOISE"] = getUniformLocation("texNoise");

	m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");

	for (int i = 0; i < 128; ++i)
	{
		std::ostringstream paramName;
		paramName << "U_SAMPLEKERNEL[" << i << "]";

		std::ostringstream kernalName;
		kernalName << "uSampleKernel[" << i << "]";

		m_parameters[paramName.str()] = getUniformLocation(kernalName.str().c_str());
	}
}

void SSAOShader::load_ProjectionMatrix(Matrix4f & matrix)
{
	loadU_Mat4f(m_parameters["U_PROJECTION"], matrix);
}

void SSAOShader::load_TextureUnit(int positiondepth, int normal, int noise)
{
	loadU_1i(m_parameters["U_TEXTUREUNIT_POS"], positiondepth);
	loadU_1i(m_parameters["U_TEXTUREUNIT_NORMAL"], normal);
	loadU_1i(m_parameters["U_TEXTUREUNIT_NOISE"], noise);

}

void SSAOShader::load_ScreenSize(float x, float y)
{
	loadU_Vec2f(m_parameters["U_SCREENSIZE"], (int)x, (int)y);
}

void SSAOShader::load_SampleKernel(vector<Vector3>& samples)
{
	int i = 0;
	for (vector<Vector3>::iterator it = samples.begin(); it != samples.end(); ++it)
	{
		std::ostringstream paramName;
		paramName << "U_SAMPLEKERNEL[" << i << "]";

		loadU_Vec3f(m_parameters[paramName.str()], samples[i]);

		i++;
	}
}