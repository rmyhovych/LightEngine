#version 330 core
precision highp float;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 vRotNormal;
out vec3 vFragPos;

uniform mat4 mVP;
uniform vec3 vDirLight;

//	Object Data

uniform mat3 mRotation;
uniform mat4 mModel;	


void main()
{
	vRotNormal = normalize(mRotation * vNormal);

	vec4 mM = mModel * vec4(vPosition, 1.0);

	gl_Position = mVP * mM;
}