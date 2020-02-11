#version 300 es
precision highp float;

out float fragmentdepth; 

void main()
{
	fragmentdepth = gl_FragCoord.z;
}