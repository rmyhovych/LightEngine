#version 300 es
precision highp float;

#define MAX_LIGHTING 4


in vec3 vRotNormal;
in vec3 vFragPos;
//in vec4 vFragPosLight;

in vec3 color;



out vec4 FragColor;


//	Global Data

uniform vec3 vDirLight;

uniform mat4 mVP;
//mat4 mLightSpace;





//  Depth Map
//uniform sampler2DShadow depthMap;








/*	=== SHADOW MAPPING ===

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
*/



void main()
{
	float ambient = 0.15f;

	vec3 lightDir;
	float fraction;

    //  directionnal light
    float diffuse = 0.6f * max(dot(vRotNormal, -vDirLight), 0.0f);
	float result = (1.0f - ambient) * diffuse + ambient;// * shadow();

	FragColor = vec4(result * color, 1.0);
}