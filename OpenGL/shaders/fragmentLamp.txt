#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 uColor;

void main()
{
	FragColor = vec4(uColor, 1.0f);
}