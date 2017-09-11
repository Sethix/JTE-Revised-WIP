#version 430
layout (location = 0) in vec4 position;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;

out vec3 vUV;

void main()
{
	//view[0][3] = 0;
	//view[1][3] = 0;
	//view[2][3] = 0;
	vec4 pos = proj * view * position;
	gl_Position = pos.xyww;
	vUV = vec3(position.xyz);
}