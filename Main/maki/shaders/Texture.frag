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