#include "ShaderLibrary.h"
/*!
@file		ShaderLibrary.cpp
@author		louishetong.wang@digipen.edu
@date		20/11/2022

@brief		Shader Library contains the vert and frag shaders for texture and colour shaders respectively.
			When shader programs are created, they will use the respective shader library
*//*__________________________________________________________________________*/

std::unique_ptr<ShaderLibrary> Shaders = nullptr;

ShaderLibrary::ShaderLibrary()
{
	const char* vs = R"CODE(
			#version 450 core
			layout(location = 0) in vec3 point;
			layout(location = 1) in vec4 color;
			layout(location = 2) in vec2 uv;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;
			out vec2 vertex_uv;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y,point.z, 1.0);
				vertex_color = color;
				vertex_uv = uv;
			};
)CODE";

	const char* fs = R"CODE(

			#version 450 core
			out vec4 finalcolor;

			in vec4 vertex_color;
			in vec2 vertex_uv;

			uniform sampler2D sprite;
			uniform float alpha;

			void main()
			{
				finalcolor = vertex_color * texture(sprite,vertex_uv);
				finalcolor.a = finalcolor.a *alpha;
				if(finalcolor.a < 0.0000016) discard;

			};
)CODE";

	programs.insert(std::pair<std::string, ShaderProgram*>("Textured", new ShaderProgram(vs, fs)));


	//////////////////////////////////////// colored shader
	vs = R"CODE(
			#version 450 core
			layout(location = 0) in vec3 point;
			layout(location = 1) in vec4 color;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, point.z, 1.0);
				vertex_color = color;
			};
)CODE";

	fs = R"CODE(

			#version 450 core
			out vec4 finalcolor;

			in vec4 vertex_color;
			in vec2 vertex_uv;

			void main()
			{
				finalcolor = vertex_color;
			};
)CODE";

	programs.insert(std::pair<std::string, ShaderProgram*>("Colored", new ShaderProgram(vs, fs)));


	//////////////////////////////////////// For Fonts

	vs = R"CODE(
		#version 450 core
		layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
		out vec2 TexCoords;

		uniform mat4 projection;

		void main()
		{
		    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
		    TexCoords = vertex.zw;
		}
	)CODE";

	fs = R"CODE(
		#version 450 core
		in vec2 TexCoords;
		out vec4 color;

		uniform sampler2D text;
		uniform vec3 textColor;
		uniform float alpha;
		void main()
		{    
		    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
		    color = vec4(textColor, 1.0) * sampled;
		}
	)CODE";

	programs.insert(std::pair<std::string, ShaderProgram*>("Font", new ShaderProgram(vs, fs)));


}
ShaderLibrary::~ShaderLibrary()
{
	for (auto& x : programs)
	{
		delete x.second; //memory leak 3
	}
}

ShaderProgram* ShaderLibrary::Textured_Shader()
{
	return programs["Textured"];
}

ShaderProgram* ShaderLibrary::Font_Shader()
{
	return programs["Font"];
}

ShaderProgram* ShaderLibrary::Colored_Shader()
{
	return programs["Colored"];
}
