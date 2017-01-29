#version 430

in  vec2 fUV;
in  vec4 fPos;

out vec4  outColor;

layout(location = 3) uniform sampler2D texMap;

void main ()
{ 
	outColor = texture(texMap, fUV);
}