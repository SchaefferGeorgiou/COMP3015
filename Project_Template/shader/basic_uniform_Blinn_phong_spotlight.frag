#version 460


//in vec3 Colour;
in vec3 Position;
in vec3 Normal;

layout (location = 0) out vec4 FragColour;


uniform struct SpotLight
{
    vec3 Position;
    vec3 Direction;
	vec3 La;
	vec3 Ld;
	float Exponent;
	float Cutoff;

}Spot;


uniform struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;

}Material;



vec3 binnPhongModel(vec3 position, vec3 n)
{
    
    vec3 ambient = Material.Ka * Spot.La;
    
    vec3 s = normalize(((Spot.Position).xyz - position));

    float sDotn = max(dot(s,n), 0.0);

    
    vec3 diffuse = Light.Ld * Material.Kd * sDotn;

    vec3 specular = vec3(0.0f);

    if (sDotn > 0)
    {

        vec3 v = normalize(-position.xyz);
        vec3 h = normalize(v + s);
        specular = Material.Ks * pow(max( dot(h,n), 0.0), Material.Shininess);        

     }

    return ambient + diffuse + specular;
}


void main()
{

   FragColour = vec4(phongModel((Position).xyz, Normal),0); //+= to deep fry 

    
}
