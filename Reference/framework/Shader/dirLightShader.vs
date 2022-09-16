#version 330 core

layout (location = 0) in vec3 Position;

out mat4 LightProjection;
out mat4 LightView;

uniform mat4 lightView;
uniform mat4 lightProjection;

void main()
{
	gl_Position = vec4(Position, 1.0);
	LightProjection = lightProjection;
	LightView = lightView;
}