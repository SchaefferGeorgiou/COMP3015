#version 430

layout (location = 0) in vec3 VertexPosition;
//layout (location = 1) in vec3 VertexColor;
layout (location = 1) in vec3 VertexNormal;

//out vec3 Color;
out vec3 LightIntensity;

uniform vec4 LightPosition;
uniform vec3 Kd;
uniform vec3 Ld;
uniform vec3 Ks;
uniform vec3 Ls;

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
    
    vec3 s = normalize((LightPosition - pos).xyz);

    float sDotn = max(dot(s,n), 0.0);

    diffuse = Ld * Kd * sDotn;

    //vec3 r = normalize( -s + 2*(sDotn)*n); 
    if(sDotn > 0)
    {   
        vec4 r = reflect(vec4(s,1.0),vec4(n,1.0));

        float rDotv = max(dot(r,pos),0.0f);

        specular = Ks * Ls * pow(rDotv,100.0f);  
    }


    LightIntensity = diffuse + specular;

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
