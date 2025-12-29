#type geometry
#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};
layout (location = 0) in VertexOutput Input;

in struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
	mat4 ViewProjection;
};
void MakeTriangle()
{
	for(int i = 0; i < 3; i++)
	{
		gl_Position = VertexOutput[i].ViewProjection * gl_in[i].gl_Position;
		Color = VertexOutput[i].Color;
		TexCoord = VertexOutput[i].TexCoord;
		TilingFactor = VertexOutput[i].TilingFactor;
		ViewProjection = VertexOutput[i].ViewProjection;
		EmitVertex();
	}
	EndPrimitive();

}

void main()
{
	gl_Layer = 0;
	gl_ViewportIndex = 0;

	MakeTriangle();

}