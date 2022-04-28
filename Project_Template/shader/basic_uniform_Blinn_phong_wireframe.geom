#version 430


layout (points)  in;
layout (triangle_strip, max_vertices = 3) out;

uniform float Size2;

uniform mat4 ProjectionMatrix;

out vec3 GeomNormal;
out vec3 GeomPosition;

noperspective out vec3 GEdgeDistance;

in vec3 VertexNormal[];
in vec3 VertexPosition[];

uniform mat4 ViewportMatrix;

void main()
{
	vec2 p0 = vec2(ViewportMatrix * (gl_in[0].gl_Position / gl_in[0].gl_Position.w));
	vec2 p1 = vec2(ViewportMatrix * (gl_in[1].gl_Position / gl_in[1].gl_Position.w));
	vec2 p2 = vec2(ViewportMatrix * (gl_in[2].gl_Position / gl_in[2].gl_Position.w)); 

	float a = length(p1 - p2);
	float b = length(p2 - p0);
	float c = length(p1 - p0);

	float alpha = acos((b*b + c*c - a*a) / (2.0*b*c));
	float beta = acos ((a*a + c*c - b*b) / (2.0*a*c));

	float ha = abs(c* sin(beta));
	float hb = abs(c* sin(beta));
	float hc = abs(c* sin(beta));

	GEdgeDistance = vec3(ha, 0, 0);
	GeomNormal = VertexNormal[0];
	GeomPosition = VertexPosition[0];
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	GEdgeDistance = vec3(ha, 0, 0);
	GeomNormal = VertexNormal[1];
	GeomPosition = VertexPosition[1];
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	GEdgeDistance = vec3(ha, 0, 0);
	GeomNormal = VertexNormal[2];
	GeomPosition = VertexPosition[2];
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}
