#version 430

layout (location = 0) in vec4 position;
layout (location = 3) in vec2 texCoord;

layout (location = 0) in mat4 model;
layout (location = 1) in mat4 view;
layout (location = 2) in mat proj;

out vec2 vUV;

void main()
{
	vUV = texCoord * 0.5 + 0.5;
	gl_Position = proj * view * model * position;
}