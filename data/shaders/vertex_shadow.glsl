#version 300 es

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 mLightSpace;
uniform mat4 mModel;


void main()
{
    gl_Position = mLightSpace * mModel * vec4(vPos, 1.0);
}

