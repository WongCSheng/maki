#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D textureID;
uniform vec2 gScreenSize;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / gScreenSize;
}

void main()
{
    vec2 TexCoord = CalcTexCoord();
    FragColor = vec4(texture(textureID, TexCoord).xyz, 1.0);

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    {
        BrightColor = vec4(FragColor.rgb, 1.0);
    }

    // Moved to HDR Shader
    //float gamma = 2.2;
	//FragColor = vec4(pow(Color, vec3(1.0 / gamma)), 1.0);
    //FragColor = vec4(Color, 1.0);
}
