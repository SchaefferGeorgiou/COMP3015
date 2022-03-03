#version 430


in vec3 Colour;


layout (location = 0) out vec4 FragColour;


void main()
{

   FragColour = vec4(Colour, 1.0);
    

    
}
