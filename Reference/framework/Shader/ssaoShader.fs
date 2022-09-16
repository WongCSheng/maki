#version 330 core
out float FragColor;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 uSampleKernel[128];
uniform vec2 gScreenSize;

// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
int kernelSize = 32;
float radius = 2.0;

uniform mat4 Projection;

void main()
{
	// tile noise texture over screen based on screen dimensions divided by noise size
	vec2 noiseScale = vec2(gScreenSize.x/4.0, gScreenSize.y/4.0); 
	vec2 TexCoords = gl_FragCoord.xy / gScreenSize;

	// Get input for SSAO algorithm
    vec3 origin = texture(gPositionDepth, TexCoords).xyz;
    vec3 normal = (texture(gNormal, TexCoords).xyz);
    vec3 randomVec = texture(texNoise, TexCoords * noiseScale).xyz;

	// Create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);


	// Iterate over the sample kernel and calculate occlusion factor
	float occlusion = 0.0;
	for (int i = 0; i < kernelSize; ++i) 
	{
		// get sample position:
		vec3 sample = TBN * uSampleKernel[i]; // from tangent to view - space
		sample = sample * radius + origin;
  
		// project sample position:
		vec4 offset = vec4(sample, 1.0);
		offset = Projection * offset;  // from view to clip-space
		offset.xyz /= offset.w;  // perspective divide
		offset.xyz = offset.xyz * 0.5 + 0.5;  // transform to range 0.0 - 1.0
  
		// get sample depth:
		float sampleDepth = -texture(gPositionDepth, offset.xy).a; // Get depth value of kernel sample

		// (learnOpengl)
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(origin.z - sampleDepth ));
        occlusion += (sampleDepth >= sample.z ? 1.0 : 0.0) * rangeCheck;       
	}

	occlusion = 1.0 - (occlusion / kernelSize);

	float strength = 2.0;
	FragColor = pow(occlusion, strength);

    //FragColor = vec4(normal, 1.0);
}

