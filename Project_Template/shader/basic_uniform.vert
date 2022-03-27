#version 460

layout (location = 0) in vec4 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec4 Position;
out vec3 Normal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main()
{ 
	 Normal = normalize( NormalMatrix * VertexNormal.xyz);
	 Position = ModelViewMatrix * VertexPosition;

	 gl_Position = MVP * VertexPosition;
}
