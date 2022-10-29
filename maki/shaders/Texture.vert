#version 450 core
layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;

layout (location=0) out vec3 ourColor;
layout (location=8) out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aVertexPosition, 0.0, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
