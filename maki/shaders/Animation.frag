#version 450 core

uniform sampler2D imgTexture;
uniform float uv_x;
uniform float uv_y;
uniform_float nx_frames;
uniform float ny_frames;

in vec2 TexCoord;
out vec4 frag_colour;

void main()
{
    float x = 1.0 / nx_frames;
    float y = 1.0 / ny_frames;
    frag_color = texture(imgTexture, vec2(TexCoord.x * x, TexCoord.y * y) + vec2(x * uv_x, y * uv_y));
}