#version 430

in vec3 Position;
in vec3 LightDir;
in vec2 TexCoord;
in vec3 ViewDir;


layout (location = 0) out vec4 FragColour;
layout(binding=0) uniform sampler2D ColorTex;
layout(binding=1) uniform sampler2D NormalMapTex;

uniform struct LightInfo
{
    vec3 Position;
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

vec3 blinnPhong(vec3 position, vec3 n) 
{

    
    vec3 s = normalize(((Light.Position).xyz - position)); //calculate s vector

    
    
    vec3 colour = texture(ColorTex, TexCoord).rgb;
   

    vec3 ambient = Light.La * colour; 
    
    float sDotn = max(dot(s,n), 0.0f) ; //calculate dot product between s and n
    
    vec3 diffuse = Light.Ld * colour * sDotn; //calculate the diffuse
        
    vec3 specular = vec3(0.0f);
    
    if( sDotn > 0.0 )
    {
        vec3 v = normalize(-position.xyz);
        vec3 h = normalize(v + s);
        specular = Material.Ks * pow(max( dot(h,n), 0.0), Material.Shininess); 
    }     

    return ambient + diffuse + specular;
}


void main()
{
    vec3 norm = texture(NormalMapTex, TexCoord).xyz;
                        norm.xy = 2.0 * norm.xy - 1.0;

    FragColour = vec4(blinnPhong(ViewDir.xyz, norm),1.0f);  

    
    
}
