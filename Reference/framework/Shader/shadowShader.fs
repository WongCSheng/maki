#version 330 core

out vec4 FragColor;

in vec2 TexCoordOut;
uniform sampler2D gShadowMap;

void main()
{
    //float Depth = texture(gShadowMap, TexCoordOut).x;
    //Depth = 1.0 - (1.0 - Depth) * 25.0;
    //FragColor = vec4(vec3(Depth), 1.0);
}