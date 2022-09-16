#version 330 core

out vec4 FragColor;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform vec2 gScreenSize;
uniform bool bloom;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / gScreenSize;
}

uniform float gamma;
uniform float exposure;

void main()
{
    vec2 TexCoord = CalcTexCoord();
    vec3 hdrColor = texture(scene, TexCoord).xyz;
    if(bloom)
    {
        vec3 bloomColor = texture(bloomBlur, TexCoord).rgb;
        hdrColor += bloomColor;
    }
    // Without exposure
    //vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    //mapped = pow(mapped, vec3(1.0 / gamma));

    // Reinhard tone mapping
    //vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    // Gamma Correction
    mapped = pow(mapped, vec3(1.0 / gamma));

    FragColor = vec4(mapped, 1.0);
}