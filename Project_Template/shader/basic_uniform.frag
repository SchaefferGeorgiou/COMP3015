#version 460

in vec4 Position;
in vec3 Normal;

layout (location = 0) out vec4 FragColour;


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
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;

}Material;


vec3 blinnPhongSpot(int index, vec3 position, vec3 normal) 
{

    vec3 ambient = Material.Ka * Lights[index].La ; 
    vec3 s = normalize(((Lights[index].Position).xyz - position)); //calculate s vector
    float cosAng = dot(-s, normalize(Lights[index].Direction)); //cosine of the angle
    float angle = acos( cosAng ); //gives you the actual angle
    float spotScale = 0.0f;

    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    if(angle < Lights[index].Cutoff )
    {
        spotScale = pow( cosAng, Lights[index].Exponent);
        float sDotn = max(dot(s,normal), 0.0f) ; //calculate dot product between s and n
        diffuse = Lights[index].Ld * Material.Kd * sDotn; //calculate the diffuse
        
        specular = vec3(0.0f);
    
        if( sDotn > 0.0 )
        {
            vec3 v = normalize(-position.xyz);
            vec3 h = normalize(v + s);
            specular = Material.Ks * pow(max( dot(h,normal), 0.0), Material.Shininess); 
        }

     }

    return ambient + (spotScale * Lights[index].La) * (diffuse + specular);
}


void main()
{
    
   for (int i = 0; i < 3; i++)
   {
       FragColour += blinnPhongSpot(i, Position.xyz, Normal);
   } 

}
