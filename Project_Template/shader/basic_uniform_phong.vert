#version 460

layout (location = 0) in vec3 VertexPosition;
//layout (location = 1) in vec3 VertexColor;
layout (location = 1) in vec3 VertexNormal;

//out vec3 Color;
out vec3 LightIntensity;






uniform struct LightInfo
{
    vec4 Position;
    vec3 Ld;
    vec3 Ls;   
    
}Light;

uniform struct MaterialInfo
{
    
    vec3 Kd;
    vec3 Ks;
}Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

vec3 diffuse;
vec3 specular;

void main()
{
    //Color = VertexColor;

    vec3 n = normalize( NormalMatrix * VertexNormal);

    vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);
    
    vec3 s = normalize((Light.Position - pos).xyz);

    float sDotn = max(dot(s,n), 0.0);

    diffuse = Material.Kd * Light.Ld * sDotn;

    //vec3 r = normalize( -s + 2*(sDotn)*n); 
    if(sDotn > 0)
    {   
        vec4 r = reflect(vec4(s,1.0),vec4(n,1.0));

        float rDotv = max(dot(r,pos),0.0f);

        specular = Material.Ks * Light.Ls * pow(rDotv,0.9f);  
    }

    LightIntensity =  diffuse + specular;

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
