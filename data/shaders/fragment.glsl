#version 300 es
precision highp float;

in vec3 vRotNormal;
in vec3 vFragPos;
in vec4 vFragPosLight;

in vec3 color;

out vec4 FragColor;


layout(std140) uniform GlobalData
{
	uniform vec3 vDirLight;
	uniform mat4 mVP;
	uniform mat4 mLightSpace;
};





//  Depth Map
uniform sampler2D depthMap;








const vec2 poissonDisk[4] = vec2[](
    vec2( -0.94201624, -0.39906216),
    vec2( 0.94558609, -0.76890725),
    vec2( -0.094184101, -0.92938870),
    vec2( 0.34495938, 0.29387760)
);



float shadow(float bias)
{
    float visibility = 1.0;
	
    for (int i = 0; i < 4; i++)
    {
        if (texture(depthMap, vFragPosLight.xy + poissonDisk[i] / 3000.0).x < (vFragPosLight.z - bias))
        {
            visibility -= 0.22;
        }
    }
	
	return visibility;
}




void main()
{
	float ambient = 0.15f;

	vec3 lightDir;
	float fraction;

	float dirLightAngle = dot(vRotNormal, -vDirLight);

	float bias = 0.0004 * tan(acos(dirLightAngle));

    //  directionnal light
    float diffuse = 0.6f * max(dirLightAngle, 0.0f);
	float result = (1.0f - ambient) * diffuse * shadow(bias) + ambient;

	FragColor = vec4(result * color, 1.0);
}