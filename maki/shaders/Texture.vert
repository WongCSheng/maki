#version 450 core

layout (location=0) in vec2 aVertexPosition;

layout (location=1) in vec3 aVertexColor;

layout (location=2) in vec2 aTexturePosition;

layout (location=0) out vec3 vColor;

layout (location=8) out vec2 vTexture;

void main(void)
{
	gl_Position = vec4(aVertexPosition, 0.0, 1.0);
	gl_Position = sign(gl_Position);
	vColor = aVertexColor;

	vTexture = aTexturePosition * 4.0;
}