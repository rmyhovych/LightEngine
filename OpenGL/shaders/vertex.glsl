#version 300 es
#define MAX_LIGHTING 4

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;


struct sLight							// +
{
	vec3 pos;
	float intensity;
};



layout (std140)	uniform CommonData
{
	vec3 vDirLight;
	
	int uSize;
	sLight pointLights[MAX_LIGHTING];

	mat4 mVP;
	mat4 mLightSpace;
};


out vec3 vRotNormal;
out vec3 vFragPos;
out vec4 vFragPosLight;






uniform mat4 mRotation;
uniform mat4 mModel;		






void main()
{
	vRotNormal = mat3(mRotation) * vNormal;
	vFragPos = vec3(mModel * vec4(vPosition, 1.0));


	vFragPosLight = mLightSpace * mModel * vec4(vPosition, 1.0);

	//  [-1, 1] -> [0, 1]
    vFragPosLight = vFragPosLight * 0.5 + 0.5;

	gl_Position = mVP * mModel * vec4(vPosition, 1.0);

}