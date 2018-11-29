#version 330 core
#define MAX_LIGHTING 10

struct Light
{
	vec3 color;
	vec3 pos;
	float intensity;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//	Lights
uniform int uSize;
uniform Light uLights[MAX_LIGHTING];

//	Object
uniform vec3 uColor;
uniform vec3 uViewPos;

void main()
{
	float ambient = 0.001;

	vec3 lightDir;
	float fraction;

	vec3 reflectDir;
	vec3 halfwayDir;
	vec3 viewDir = normalize(uViewPos - FragPos);

	float diffuse;
	float specular;

	vec3 result = vec3(0, 0, 0);
	for (int i = 0; i < uSize; i++)
	{
		lightDir = uLights[i].pos - FragPos;
		fraction = 1/(1 + dot(lightDir, lightDir) / uLights[i].intensity);
		lightDir = normalize(lightDir);

		//reflectDir = reflect(-lightDir, Normal);
		halfwayDir = normalize(viewDir + lightDir);

		diffuse = fraction * max(dot(Normal, lightDir), 0.0);
		specular = fraction * pow(max(dot(halfwayDir, Normal), 0.0), 64);

		result += (uColor - result) * (diffuse + specular) * uLights[i].color;
	}

	vec3 gamma = vec3(0.4545);
	FragColor.rgb = pow(result.rgb, gamma);
}