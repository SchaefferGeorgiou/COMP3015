#version 460

#define PI 3.14159265

//VARIABLES_____________________________________________________________

//IN
in vec2 TexCoord;

uniform sampler2D NoiseTex;

//OUT
layout (location = 4) out vec4 NewTex;


uniform vec4 SkyColour = vec4(0.3,0.3,0.9,1.0);
uniform vec4 CloudColour = vec4(1.0,1.0,1.0,1.0);


void makeTexture()
{
	vec4 noise = texture(NoiseTex,TexCoord);
	float t = (cos(noise.a * PI) + 1.0) / 2.0;
	vec4 colour = mix(SkyColour, CloudColour, t);

	NewTex = vec4(colour.rgb, 1.0);
}

void main()
{

}
