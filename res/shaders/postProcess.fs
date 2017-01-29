#version 430

out vec4 outColor;

in vec2 vUV;

layout(location = 0) uniform sampler2D map;
layout(location = 1) uniform sampler2D depthMap;

vec4 sobel(in sampler2D map, in vec2 UV);
vec4 crossBlur(in sampler2D map, in vec2 UV);

void main()
{
	//outColor = sobel(map, vUV);
	if(texture(depthMap, vUV).r >= 1) discard;
	outColor = texture(map, vUV);
}

vec4 crossBlur(in sampler2D map, in vec2 UV)
{
	vec2 sDim = textureSize(map, 0).xy;
	vec4 result = vec4(0,0,0,0);

	for(int i = -9; i <= 9; ++i)
	{
		result += texture(map, UV + vec2(i, 0)/sDim);
		result += texture(map, UV + vec2(0, i)/sDim);
	}

	return result / 36;
}

vec4 sobel(in sampler2D map, in vec2 UV)
{
	vec2 sDim = textureSize(map, 0).xy;
	
	vec4 yColor =
	texture(map, UV + vec2( 1, -1)/sDim) +
	texture(map, UV + vec2( 0, -1)/sDim)*2 +
	texture(map, UV + vec2(-1, -1)/sDim) -
	texture(map, UV + vec2( 1,  1)/sDim) -
	texture(map, UV + vec2( 0,  1)/sDim)*2 -
	texture(map, UV + vec2(-1,  1)/sDim);

	vec4 xColor =
	texture(map, UV + vec2(-1, -1)/sDim) +
	texture(map, UV + vec2(-1,  0)/sDim)*2 +
	texture(map, UV + vec2(-1,  1)/sDim) -
	texture(map, UV + vec2( 1, -1)/sDim) -
	texture(map, UV + vec2( 1,  0)/sDim)*2 -
	texture(map, UV + vec2( 1,  1)/sDim);

	return sqrt(yColor * yColor + xColor * xColor);
}