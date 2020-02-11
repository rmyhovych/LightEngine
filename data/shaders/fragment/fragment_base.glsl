#version 330 core
precision highp float;

in vec3 vRotNormal;
in vec3 vFragPos;

uniform vec3 vColor;

out vec4 FragColor;

uniform mat4 mVP;
uniform vec3 vDirLight;

void main()
{
	float ambient = 0.15f;

	vec3 lightDir;
	float fraction;

	float dirLightAngle = dot(vRotNormal, -vDirLight);

    //  directionnal light
    float diffuse = 0.6f * max(dirLightAngle, 0.0f);
	float result = (1.0f - ambient) * diffuse + ambient;

	FragColor = vec4(result * vColor, 1.0);
}