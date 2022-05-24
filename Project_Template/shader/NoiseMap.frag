#version 460

#define PI 3.14159265

//VARIABLES_____________________________________________________________

//IN
in vec2 TexCoord;

uniform sampler2D NoiseTex;

//OUT
layout (location = 5) out vec4 NoiseMap;


uniform vec4 Lower = vec4(0.0,0.0,0.0,1.0);
uniform vec4 Higher = vec4(1.0,1.0,1.0,1.0);


void makeTexture()
{
	vec4 noise = texture(NoiseTex,TexCoord);
	float t = (cos(noise.a * PI) + 1.0) / 2.0;
	vec4 colour = mix(Lower, Higher, t);

	NoiseMap = vec4(colour.rgb, 1.0);
}

void main()
{
	makeTexture();
}
