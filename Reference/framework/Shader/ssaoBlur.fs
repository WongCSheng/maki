#version 330 core

out float fragColor;

uniform sampler2D ssaoInput;
uniform vec2 gScreenSize;

const int blurSize = 4; // use size of noise texture (4x4)

void main()
{
	vec2 texelSize = 1.0 / vec2(textureSize(ssaoInput, 0));
	vec2 TexCoords = gl_FragCoord.xy / gScreenSize;

	float result = 0.0;
	for (int x = 0; x < blurSize; ++x) 
	{
		for (int y = 0; y < blurSize; ++y) 
		{
			vec2 offset = (vec2(-2.0) + vec2(float(x), float(y))) * texelSize;
			result += texture(ssaoInput, TexCoords + offset).r;
		}
	}
 
	fragColor = result / float(blurSize * blurSize);
}

