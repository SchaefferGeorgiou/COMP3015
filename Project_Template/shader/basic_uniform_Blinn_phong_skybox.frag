#version 430



in vec3 Vertices;



layout (location = 0) out vec4 FragColour;
layout(binding=0) uniform samplerCube SkyboxTex;


uniform struct LightInfo
{
    vec4 Position;
    vec3 La;
    vec3 Ld;  
    
}Light;


uniform struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;

}Material;



vec3 blinnPhong() 
{

    
    

    vec3 ambient = Light.La ; 
        
   

    return  ambient;// + diffuse + specular;// + specular;
}


void main()
{

    vec3 texColor = texture(SkyboxTex, normalize(Vertices)).rgb;

    FragColour = vec4(texColor,1.0f);  

    
    
}
