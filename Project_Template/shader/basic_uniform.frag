#version 460

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColour;

//layout (binding = 0) uniform sampler2D Floor;
//layout (binding = 1) uniform sampler2D Rock;
//layout (binding = 2) uniform sampler2D Thingy;

layout (binding = 0) uniform sampler2D Base;
layout (binding = 1) uniform sampler2D Alpha;

uniform struct FogInfo
{
    float MaxDist; //max distance
    float MinDist; //min distance
    vec3 Colour; //colour of the fog
} Fog;

uniform struct LightInfo
{
    vec4 Position;
    vec3 La;
    vec3 Ld;
    vec3 Direction;
    float Exponent;
    float Cutoff;
    
}Lights[3];

uniform struct MaterialInfo
{

    vec3 Ks;
    float Shininess;

}Material;

//For fluctuating
uniform float AlphaCutoff;

vec3 shadeColour;

vec3 blinnPhongSpot(int index, vec3 position, vec3 normal) 
{

    vec3 texColour = texture(Base, TexCoord).rgb;

    vec3 ambient = texColour * Lights[index].La ; 
    vec3 s = normalize(((Lights[index].Position).xyz - position)); //calculate s vector

    float cosAng = dot(-s, normalize(Lights[index].Direction)); //cosine of the angle
    float angle = acos( cosAng ); //gives you the actual angle

    float spotScale = 1.0f;

    float intensity =10.0f;

    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    if(angle < Lights[index].Cutoff )
    {
        spotScale = pow( cosAng, Lights[index].Exponent);
        float sDotn = max(dot(s,normal), 0.0f) ; //calculate dot product between s and n
        diffuse = Lights[index].Ld * texColour * sDotn; //calculate the diffuse
        
        specular = vec3(0.0f);
    
        if( sDotn > 0.0 )
        {
            vec3 v = normalize(-position.xyz);
            vec3 h = normalize(v + s);
            specular = Material.Ks * pow(max( dot(h,normal), 0.0), Material.Shininess); 
        }

     }

    return ambient + intensity *((spotScale * Lights[index].La) * (diffuse + specular));
}

////Phong for testing
//vec3 phongModel(vec3 position, vec3 n)
//{
//    
//    vec3 ambient = Material.Ka * Lights[0].La;
//    
//    vec3 s = normalize(((Lights[0].Position).xyz - position));
//
//    float sDotn = max(dot(s,n), 0.0);
//
//    vec3 diffuse = Lights[0].Ld * Material.Kd * sDotn;
//
//    vec3 specular = vec3(0.0f);
//
//    if (sDotn > 0)
//    {
//
//        vec3 v = normalize(-position.xyz);
//        vec3 r = reflect(-s,n);
//        specular = Material.Ks * pow(max( dot(r,v), 0.0), Material.Shininess);        
//
//     }
//
//    return ambient + diffuse + specular;
//}


void main()
{

    float dist = abs( Position.z ); //distance

    float fogFactor = (Fog.MaxDist - dist) / (Fog.MaxDist - Fog.MinDist);

    fogFactor = clamp( fogFactor, 0.0, 1.0 );

    vec4 alphaMap = texture(Alpha, TexCoord).rgba;

    if(alphaMap.a < AlphaCutoff)
    {
        discard;
    }
    else
    {
        if(gl_FrontFacing)
        {
            for(int i = 0; i < 3; i++)
            {
                //get colour for each light
                shadeColour += blinnPhongSpot(i, Position, Normal);       
         
            }
        }
        else
        {
            for(int i = 0; i < 3; i++)
            {
                 //get colour for each light
                shadeColour += blinnPhongSpot(i, Position, Normal);       
         
            }
        }
        
    }

    //mix it all together
    vec3 colour = mix( Fog.Colour, shadeColour, fogFactor);

    FragColour = vec4(colour,1.0f);    

}
