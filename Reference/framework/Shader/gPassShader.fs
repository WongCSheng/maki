#version 330 core

layout (location = 0) out vec4 WorldPosOut;
layout (location = 1) out vec4 ViewPosOut;
layout (location = 2) out vec4 DiffuseOut;
layout (location = 3) out vec3 NormalOut;
layout (location = 4) out vec3 NormalViewOut;
layout (location = 5) out vec4 SpecularOut;

in VS_OUT
{
    vec2 TexCoord;
    vec3 Normal;
    vec3 NormalView;
    vec3 ViewPos;
    vec3 WorldPos;
    flat int normalMapEnable;
    mat3 TBN;
}   fs_in;

uniform vec3 gDiffuseColor;
uniform bool gDiffuseColorOnly;
uniform bool parallax;
uniform bool specular;
uniform vec3 viewPos;
uniform float gamma;
uniform float shininess;

// Textures
uniform sampler2D texture_diffuse; // Texture 0, diffuse map
uniform sampler2D texture_normal;   // Texture 1
uniform sampler2D texture_displacement; // texture 2
uniform sampler2D texture_specular; // texture3

uniform float NEAR;
uniform float FAR;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

void main()
{
    vec2 texCoords = fs_in.TexCoord;

    if(parallax)
	{
		vec3 viewDir = fs_in.TBN * normalize(viewPos - fs_in.WorldPos);
		texCoords = ParallaxMapping(fs_in.TexCoord,  viewDir);
        if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
            discard;
	}

    WorldPosOut.xyz = fs_in.WorldPos;
    WorldPosOut.a = LinearizeDepth(gl_FragCoord.z);

    ViewPosOut.xyz = fs_in.ViewPos;
    ViewPosOut.a = WorldPosOut.a;

    //float gamma = 2.2;
    if(!gDiffuseColorOnly)
    {
        // transform from srgb space to linear space
        DiffuseOut.xyz = pow(texture(texture_diffuse, texCoords).xyz, vec3(gamma));
        //DiffuseOut.xyz = texture(texture_diffuse, fs_in.TexCoord).xyz;    // old diffuse that is not in linear space
        DiffuseOut.a = 1.0;
    }
    else
    {
        DiffuseOut.xyz = pow(gDiffuseColor, vec3(gamma));
        //DiffuseOut.xyz = gDiffuseColor;
        DiffuseOut.a = 0.0;
    }

    vec3 normal = vec3(0, 0, 0);

    if(fs_in.normalMapEnable == 0)
    {
        normal = normalize(fs_in.Normal);
    }
    else
    {
        normal = texture(texture_normal, texCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        normal = normalize(fs_in.TBN * normal);
    }
    
    NormalOut = normalize(normal);
    NormalViewOut = normalize(fs_in.NormalView);

    if(specular)
    {
        //SpecularOut.rgb = texture(texture_specular, texCoords).rgb;
    }
    else
    {
        //SpecularOut = vec4(1.0, 1.0, 1.0, shininess);
    }

    SpecularOut.rgb = vec3(1, 1, 1);
    SpecularOut.a = 32.0;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
    const float minLayers = 10;
    const float maxLayers = 20;

    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  

    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * 0.1; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(texture_displacement, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(texture_displacement, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // -- parallax occlusion mapping interpolation from here on
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(texture_displacement, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}