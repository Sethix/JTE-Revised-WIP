#version 430

layout(location = 0) uniform mat4 view;

layout(location = 1) uniform sampler2D albedoMap;
layout(location = 2) uniform sampler2D normalMap;
layout(location = 3) uniform sampler2D specularMap;
layout(location = 4) uniform sampler2D positionMap;

layout(location = 5) uniform sampler2D shadowMap;

layout(location = 6) uniform vec4 lCol;
layout(location = 7) uniform mat4 lightView;
layout(location = 8) uniform mat4 lightProj;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpecular;

in vec2 vUV;

float shadowBias = 0.1f;

mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.5f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.5f, 0.0f,
					 0.5f, 0.5f, 0.5f, 1.0f);


void main()
{
	vec3 L = normalize((view * lightView[2]).xyz);
	vec3 N = normalize(texture(normalMap, vUV).xyz);
	vec3 P = texture(positionMap, vUV).xyz;

	vec4 sUV = clipToUV * lightProj * lightView * inverse(view) * vec4(P.xyz,1);

	if(texture(shadowMap, sUV.xy).r < sUV.z - shadowBias) discard;

	vec3 R = reflect(L,N);
	vec3 E = normalize(view[3].xyz + P.xyz);

	float sP = 2;
	float lamb = max(0, -dot(L,N));
	float spec = max(0, -dot(E,R));

	if(spec > 0) spec = pow(spec, sP);

	if(lamb > .75) lamb = 1;
	else if(lamb > .5) lamb = .75;
	else if(lamb > .25) lamb = .5;
	else if(lamb > 0) lamb = .25;
	else lamb = 0;

	float angleToScreen = dot(N, vec3(0,0,1));

	//if(angleToScreen < .33f)
	//spec = lamb = 0;

	outAlbedo = texture(albedoMap, vUV) * lamb * lCol;
	outSpecular = texture(specularMap, vUV) * spec * lCol;
	outColor = outAlbedo + outSpecular;

	//outColor = vec4(N,1);
}