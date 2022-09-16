#version 330 core

layout (location = 0) in vec3 Position; 
layout (location = 1) in vec3 Normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT
{
	vec3 WorldPos;
	vec3 Normal;
}	vs_out;

void main()
{          
    gl_Position = projection * view * model * vec4(Position, 1.0);

	// Pos
	vs_out.WorldPos = (model * vec4(Position, 1.0)).xyz;

	// Normals
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vs_out.Normal = (normalMatrix * Normal);
}
