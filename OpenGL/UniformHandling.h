#pragma once

typedef int GLint;

struct ObjectUniforms
{
	GLint mRotation;
	GLint mModel;
	GLint vColor;
};

struct GlobalUniforms
{
	GLint vDirLight;
	GLint mVP;
};