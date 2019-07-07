#version 300 es
precision highp float;

layout (location = 0) in vec3 vPosition;


uniform mat4 mVP;
uniform mat4 mModel;		

void main()
{
	gl_Position = mVP * mModel * vec4(vPosition, 1.0);
}