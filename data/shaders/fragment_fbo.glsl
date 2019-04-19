#version 300 es


out vec4 vFragColor;


in vec2 TexCoords;
uniform vec3 palette[5];

uniform sampler2D tScreenTexture;

void main()
{
    vec3 color = texture(tScreenTexture, TexCoords).rgb;


    float lightIntensity = color.r;


    int minColor = int(floor(lightIntensity * 4.0f));

    color = palette[minColor];

    if (minColor != 4)
    {
        float deltaIntensity = lightIntensity - float(minColor) / 4.0f;

        vec3 deltaColor = (palette[minColor + 1] - palette[minColor]) * (4.0f * deltaIntensity);

        color += deltaColor;
    }


    vFragColor = vec4(color, 1.0);
   // vFragColor = texture(tScreenTexture, TexCoords);
} 