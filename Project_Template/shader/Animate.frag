#version 460


//VARIABLES

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

//OUT
//layout (location = 0) out vec4 FragColour;
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColourData;
layout (location = 4) out vec3 SpecularData;

layout(binding=0) uniform sampler2D PositionTex;
layout(binding=1) uniform sampler2D NormalTex;

//STRUCTS

uniform struct MaterialInfo
{
    vec3 Kd;
    vec3 Ks;

}Material;


//METHODS

void saveData()
{
    vec3 pos = vec3(texture(PositionTex, TexCoord));
    vec3 norm = vec3(texture(NormalTex, TexCoord));

    PositionData = Position.xyz;
    NormalData = normalize(Normal);
    ColourData = Material.Kd;
    SpecularData = Material.Ks;
}



void main()
{
    saveData();

    //FragColour = vec4(1.0,0.0,0.0,1.0);
    
}
