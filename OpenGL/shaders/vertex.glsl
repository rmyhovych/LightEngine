#version 300 es
#define MAX_LIGHTING 4

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 vRotNormal;
out vec3 vFragPos;
out vec4 vFragPosLight;

out vec3 color;


layout (std140)	uniform CommonData
{
	vec3 vDirLight;

	mat4 mVP;
	mat4 mLightSpace;
};


layout (std140) uniform UniqueData
{
	uniform mat4 mRotation;
	uniform mat4 mModel;		
	uniform vec3 vColor;
};


void main()
{
	color = vColor;

	vRotNormal = mat3(mRotation) * vNormal;
	vFragPos = vec3(mModel * vec4(vPosition, 1.0));


	vFragPosLight = mLightSpace * mModel * vec4(vPosition, 1.0);

	//  [-1, 1] -> [0, 1]
    vFragPosLight = vFragPosLight * 0.5 + 0.5;

	gl_Position = mVP * mModel * vec4(vPosition, 1.0);

}