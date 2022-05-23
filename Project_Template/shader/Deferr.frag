#version 460


//VARIABLES

//IN
in vec3 Position;
in vec3 Normal;

//OUT
layout (location = 1) out vec3 PositionData;
layout (location = 2) out vec3 NormalData;
layout (location = 3) out vec3 ColourData;



//STRUCTS

uniform struct MaterialInfo
{
    vec3 Kd;

}Material;


//METHODS

void pass1()
{
    PositionData = Position.xyz;
    NormalData = normalize(Normal);
    ColourData = Material.Kd;
}



void main()
{
    pass1();

    //FragColour = vec4(0.0,1.0,0.0,1.0);
    
}
