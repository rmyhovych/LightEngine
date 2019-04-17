#version 300 es


out vec4 vFragColor;


in vec2 TexCoords;
uniform vec3 palette[5];

uniform sampler2D tScreenTexture;


mat3 sobelX = mat3(
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1);

mat3 sobelY = mat3(
    -1, -2, -1,
    0, 0, 0,
    1, 2, 1);



void main()
{
    float lightIntensity = texture(tScreenTexture, TexCoords).r;


    float gx = 0.0, gy = 0.0;

    float tempIntensity;

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            tempIntensity = texture(tScreenTexture, TexCoords + vec2(x, y)).r;

            gx += tempIntensity * sobelX[y + 1][x + 1];
            gy += tempIntensity * sobelY[y + 1][x + 1];
        }
    }

    float edge = sqrt(gx * gx + gy * gy);


    lightIntensity += edge;

    lightIntensity = pow(lightIntensity, 0.6);

    vec3 col;

    if (lightIntensity > 0.9f)
    {
        col = palette[4];
    }
    else if (lightIntensity > 0.8f)
    {
        col = (palette[4] + palette[3]) / 2.0f;
    }
    else if (lightIntensity > 0.7f)
    {
        col = palette[3];
    }
    else if (lightIntensity > 0.6f)
    {
        col = (palette[3] + palette[2]) / 2.0f;
    }
    else if (lightIntensity > 0.5f)
    {
        col = palette[2];
    }
    else if (lightIntensity > 0.4f)
    {
        col = (palette[2] + palette[1]) / 2.0f;
    }
    else if (lightIntensity > 0.3f)
    {
        col = palette[1];
    }
    else if (lightIntensity > 0.2f)
    {
        col = (palette[1] + palette[0]) / 2.0f;
    }
    else if (lightIntensity > 0.1f)
    {
        col = (palette[0] + vec3(0)) / 2.0f;
    }
    else
    {
        col = vec3(0);
    }


    vFragColor = vec4(lightIntensity * col, 1.0);
}