#version 460

//VARIABLES

//IN
in vec2 TexCoord;

layout(binding=0) uniform sampler2D PositionTex;
layout(binding=1) uniform sampler2D NormalTex;
layout(binding=2) uniform sampler2D ColourTex;

//OUT
layout (location = 0) out vec4 FragColour;


//STRUCTS

uniform struct LightInfo
{
    vec4 Position;
    float Intensity;

}Light;

uniform struct MaterialInfo
{
    float Shininess;

}Material;

//METHODS
vec3 blinnPhong(vec3 position, vec3 n, vec3 colour) 
{
    
    vec3 diffuse = vec3(0.0f);
        
    vec3 specular = vec3(0.0f);

    vec3 s = normalize(((Light.Position).xyz - position)); //calculate s vector       
    
    float sDotn = max(dot(s,n), 0.0f) ; //calculate dot product between s and n
    
    diffuse = colour * sDotn; //calculate the diffuse

    if( sDotn > 0.0 )
    {
        vec3 v = normalize(-position.xyz);
        vec3 h = normalize(v + s);
        specular = colour * pow(max( dot(h,n), 0.0), Material.Shininess); 
    }     

    return (diffuse + specular);
}

void main()
{
    vec3 pos = vec3(texture(PositionTex, TexCoord));
    vec3 n = vec3(texture(NormalTex, TexCoord));
    vec3 lighting = vec3(texture(ColourTex,TexCoord));

    FragColour = vec4(blinnPhong(pos, n, lighting),1.0);
}
