#version 430

layout (location = 0) in vec3 VertexPosition;
//layout (location = 1) in vec3 VertexColor;
layout (location = 1) in vec3 VertexNormal;

out vec3 Colour;
out vec3 LightIntensity;
//out vec4 FragVertexPosition;
//out vec3 FragVertexNormal;

uniform struct LightInfo
{
    vec4 Position;
    vec3 La;
    vec3 L;   
    
}Lights[3];

uniform struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;

}Material;




vec3 phongModel(int light, vec3 position, vec3 n)
{
    
    vec3 ambient = Material.Ka * Lights[light].La;
    
    vec3 s = normalize(((Lights[light].Position).xyz - position));

    float sDotn = max(dot(s,n), 0.0);

    vec3 diffuse = Material.Kd * vec3(0.3f,0.2f,0.5f) * sDotn;

    vec3 specular = vec3(0.0f);

    if (sDotn > 0)
    {

        vec3 v = normalize(-position.xyz);
        vec3 r = reflect(-s,n);
        specular = Material.Ks * pow(max( dot(r,v), 0.0), Material.Shininess);        

     }

    return ambient + Lights[light].L * (diffuse + specular);
}


uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;




//out uniform struct MaterialInfo;
//out uniform struct LightInfo;

//void main()
//{
//    
//    FragVertexNormal = normalize( NormalMatrix * VertexNormal);
//
//    FragVertexPosition = ModelViewMatrix * vec4(VertexPosition,1.0);
//
//    gl_Position = MVP * vec4(VertexPosition,1.0);
//}

//GOROUD
void main()
{   

    vec3 n = normalize( NormalMatrix * VertexNormal);

    vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);

    Colour = vec3(0.0f);
    for (int i = 0; i < 3; i++)
    {
        Colour += phongModel(i, pos.xyz, n);
    } 

    gl_Position = MVP * vec4(VertexPosition,1.0);
}