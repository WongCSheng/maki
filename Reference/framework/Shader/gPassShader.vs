#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMatrix;

uniform int normalMapEnable;

uniform int tessel;

// Send data to the FS
out VS_OUT
{
	vec2 TexCoord;
	vec3 Normal;
	vec3 NormalView;
	vec3 ViewPos;	// for ssao
	vec3 WorldPos;
	flat int normalMapEnable;
	mat3 TBN;
}	vs_out;

void main()
{
	// Vertex Position
	vec4 viewPos = view * model * vec4(Position, 1.0);
	vs_out.ViewPos = viewPos.xyz;

	vec4 worldPos = model * vec4(Position, 1.0);
	vs_out.WorldPos = worldPos.xyz;

	gl_Position = projection * viewPos;

	// Tex Coords
	vs_out.TexCoord = TexCoord * tessel;
	
	// Normals
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vs_out.Normal = (normalMatrix * Normal);
	
	mat3 normalViewMatrix = transpose(inverse(mat3(view * model)));
	vs_out.NormalView = (normalViewMatrix * Normal);

	if(normalMapEnable == 1)
	{
		vec3 T = normalize(normalMatrix * tangent);
		vec3 N = normalize(normalMatrix * Normal);
		//vec3 B = normalize(normalMatrix * bitangent);
		// re orthogonalize with respect to N
		T = normalize(T - dot(T, N) * N);
		// retrieve B with cross
		vec3 B = cross(T, N);

		vs_out.TBN = mat3(T, B, N);
	}

	vs_out.normalMapEnable = normalMapEnable;
}