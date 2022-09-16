#version 330 core

out vec4 FragColor;

struct PointLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Position;
    float Constant;
    float Linear;
    float Exp;
};

uniform PointLight pointLights;
uniform bool lighting;
uniform vec3 viewPos;
uniform float SpecularIntensity;
uniform float SpecularPower;
uniform vec3 color;
uniform vec2 gScreenSize;
uniform mat4 gInverseView;

// Textures
uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform sampler2D gSpecMap;
//uniform sampler2D ssao;

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / gScreenSize;
}

vec4 CalcLightInternal(PointLight Light, vec3 WorldPos, vec3 LightDirection, vec3 Normal, vec3 DiffuseColorIn, vec4 Specular)
{
    vec3 ambient = Light.AmbientIntensity * DiffuseColorIn * Light.Color;

    // Diffuse
    vec3 lightDir = LightDirection; // normalized
    float diff = max(dot(lightDir, Normal), 0.0);
    vec3 diffuse = diff * Light.Color * Light.DiffuseIntensity * DiffuseColorIn;

    // Specular
    vec3 viewDir = normalize(viewPos - WorldPos);
    float spec = 0.0;

    // Blinn Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0);    // shininess behind

    vec3 specular = spec * Light.Color;   // intensity

    return vec4(vec3(ambient + diffuse + specular), 1.0);
}

vec4 CalcPointLight(vec3 WorldPos, vec3 Normal, vec3 DiffuseColor, vec4 SpecularColor)
{
    vec3 LightDirection = pointLights.Position - WorldPos;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 Color = CalcLightInternal(pointLights, WorldPos, LightDirection, Normal, DiffuseColor, SpecularColor);
    float Attenuation = 1.0 / (pointLights.Constant + pointLights.Linear * Distance + pointLights.Exp * (Distance));

    Color.xyz *= Attenuation;
    return Color;
}

void main()
{
    vec2 TexCoord = CalcTexCoord();
    vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
    vec3 Color = texture(gColorMap, TexCoord).xyz;
    vec3 Normal = texture(gNormalMap, TexCoord).xyz;
    vec4 Specular = texture(gSpecMap, TexCoord);
    Normal = normalize(Normal);

    float AmbientOcclusion = 1.0;
    
    //AmbientOcclusion = texture(ssao, CalcTexCoord()).r;

    vec4 result = CalcPointLight(WorldPos, Normal, Color, Specular);
    FragColor = result * vec4(vec3(AmbientOcclusion), 1.0);
}