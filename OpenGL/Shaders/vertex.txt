#version 330 core

layout (location = 0) in vec3 position_;
layout (location = 1) in vec3 normal_;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	Normal = mat3(uModel) * normal_;
	FragPos = vec3(uModel * vec4(position_, 1.0));

	gl_Position = uProjection * uView * uModel * vec4(position_, 1.0);
}