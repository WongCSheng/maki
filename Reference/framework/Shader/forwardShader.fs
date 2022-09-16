#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform bool colorEnabled;
uniform vec3 viewPos;

uniform samplerCube skybox;

in VS_OUT
{
    vec3 WorldPos;
    vec3 Normal;
}   fs_in;

void main()
{
    if(colorEnabled)
    {
        FragColor = vec4(color.x, color.y, color.z, 1.0);
    }
    else
    {
        float ratio = 1.00 / 1.52;
        vec3 I = normalize(fs_in.WorldPos - viewPos);
        //vec3 R = reflect(I, normalize(fs_in.Normal));
        vec3 R = refract(I, normalize(fs_in.Normal), ratio);
        FragColor = texture(skybox, R);
    }
}