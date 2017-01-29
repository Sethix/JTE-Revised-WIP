#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 UV;

out vec2 fUV;
out vec4 fPos;

layout(location = 0) uniform mat4 Projection;	
layout(location = 1) uniform mat4 View;		
layout(location = 2) uniform mat4 Model;	
layout(location = 3) uniform sampler2D texMap;


void main()
{
	fUV = UV;
	fPos = position;

	gl_Position = Projection * View * Model * position;
	//gl_Position.x = fUV.x;
}