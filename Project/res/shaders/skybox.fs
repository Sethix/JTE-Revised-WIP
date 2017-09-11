#version 430

in vec3 vUV;

layout (location = 2) uniform samplerCube skyBox;

out vec4 color;

void main()
{
	color = texture(skyBox, vUV);
}