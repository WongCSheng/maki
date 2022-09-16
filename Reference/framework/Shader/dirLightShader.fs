#version 330 core

out vec4 FragColor;

in mat4 LightProjection;
in mat4 LightView;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
    vec3 Direction;
    float DiffuseIntensity;
};

uniform DirectionalLight directionalLight;
uniform bool lighting;
uniform vec3 viewPos;

uniform vec2 gScreenSize;
uniform mat4 gInverseView;
uniform bool gEnableShadow;
uniform bool gEnableAO;

// Textures
uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform sampler2D gSpecMap;
uniform sampler2DShadow gShadowMap;
uniform sampler2D gAOMap;

uniform vec3 color;

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / gScreenSize;
}

float CalcShadowFactor(vec4 LightSpacePos, float bias)
{
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    ProjCoords = ProjCoords * 0.5 + 0.5;
    float currentDepth = ProjCoords.z;
    //float Depth = texture(gShadowMap, ProjCoords.xy).x; // closest depth

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(gShadowMap, 0);

    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            vec2 Offsets = vec2(x, y) * texelSize;
            vec3 UVC = vec3(ProjCoords.xy + Offsets, ProjCoords.z - bias);
            shadow += texture(gShadowMap, UVC);
            //float pcfDepth = texture(gShadowMap, ProjCoords.xy + vec2(x, y) * texelSize).r;
            //shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow = 0.5 + (shadow / 18.0);
    
    if(currentDepth > 1.0)
    {
        shadow = 1.0;
    }

    return shadow;
}

vec4 CalcDirectionalLight(vec3 WorldPos, vec3 Normal, vec4 LightSpacePos, vec3 DiffuseColorIn, vec4 SpecColor)
{
    vec3 ambient = directionalLight.AmbientIntensity * DiffuseColorIn * directionalLight.Color;

     // Diffuse
    vec3 lightDir = normalize(-directionalLight.Direction); // normalized
    float diff = max(dot(lightDir, Normal), 0.0);
    vec3 diffuse = diff * directionalLight.Color * DiffuseColorIn * directionalLight.DiffuseIntensity;

    // Specular
    vec3 viewDir = normalize(viewPos - WorldPos);
    float spec = 0.0;

    // Blinn Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);

    spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0);    // shininess behind

    vec3 specular = 0.3 * spec * directionalLight.Color;   // intensity

    if(gEnableShadow)
    {
        //float bias = max(0.05 * (1.0 - dot(Normal, -directionalLight.Direction)), 0.005);
        float bias = 0.005 * tan(acos(dot(Normal, -directionalLight.Direction)));
        bias = clamp(bias, 0, 0.01);
        float ShadowFactor = CalcShadowFactor(LightSpacePos, bias);
        return vec4(vec3(ambient + ShadowFactor * (diffuse + specular)), 1.0);
    }
    else
    {
        return vec4(vec3(ambient + diffuse + specular), 1.0);
    }
}

void main()
{
    vec2 TexCoord = CalcTexCoord();
    vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
    vec3 DiffuseColor = texture(gColorMap, TexCoord).xyz;
    vec3 Normal = texture(gNormalMap, TexCoord).xyz;
    vec4 SpecularColor = texture(gSpecMap, TexCoord);
    Normal = normalize(Normal);

    float AmbientOcclusion = 1.0;
    if(gEnableAO)
    {
        AmbientOcclusion = texture(gAOMap, CalcTexCoord()).r;
    }

    vec4 LightSpacePos = LightProjection * LightView * vec4(WorldPos, 1.0);
    vec4 result = CalcDirectionalLight(WorldPos, Normal, LightSpacePos, DiffuseColor, SpecularColor);
    FragColor = result * vec4(vec3(AmbientOcclusion), 1.0);
}
