#version 300 es
#define MAX_LIGHTING 4
precision mediump float;


struct sLight							// +
{
	vec3 pos;
	float intensity;
};





in vec3 vRotNormal;
in vec3 vFragPos;
in vec4 vFragPosLight;

out vec4 FragColor;



//  Depth Map
uniform sampler2DShadow depthMap;


uniform float vColor;








float lookup(float x, float y)
{

    float pixelSize = 0.001f;

    vec4 pixel = vec4(x * pixelSize * vFragPosLight.w,
                       y * pixelSize * vFragPosLight.w,
                       0.0, 0.0);

    return textureProj(depthMap, vFragPosLight + pixel);
}


float shadow()
{

    float sum = 0.0;

    float shadowDistortion = 1.0;

    for (float x = -shadowDistortion; x <= shadowDistortion; x += shadowDistortion)
    {
        for (float y = -shadowDistortion; y <= shadowDistortion; y += shadowDistortion)
        {
            sum += lookup(x, y);
        }
    }


    return sum * 0.11;
}




void main()
{
	float ambient = 0.15f;

	vec3 lightDir;
	float fraction;


	float diffuse;

    float result = 0.0f;



    //  point lights
	for (int i = 0; i < uSize; i++)
	{
		lightDir = lights[i].pos - vFragPos;

		fraction = 1.0f / (1.0f + dot(lightDir, lightDir) / lights[i].intensity);

		lightDir = normalize(lightDir);


		diffuse = fraction * max(dot(vRotNormal, lightDir), 0.0f);
		result += (1.0f - result) * diffuse;
	}



    //  directionnal light
    diffuse = 0.6f * max(dot(vRotNormal, -vDirLight), 0.0f);
	result += (1.0f - result) * diffuse * shadow();



    //  ambient light
    result *= 1.0f - ambient;
    result += ambient;


	FragColor = vec4(result * vec3(vColor), 1.0);
}