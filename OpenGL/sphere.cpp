#include "sphere.h"



Sphere::Sphere(const char* vertexPath, const char* fragmentPath) :
	shader_(Shader(vertexPath, fragmentPath))
{
	const int meridianSize = 20;
	const int parallelSize = 10;
	float* buffer = new float[(parallelSize * meridianSize + 2) * 3];

	float* meridians = new float[meridianSize];
	float* parallels = new float[parallelSize];

	for (int i = 0; i < meridianSize; i++)
	{
		meridians[i] = i * (2 * PI / meridianSize);
	}

	for (int i = 0; i < parallelSize; i++)
	{
		parallels[i] = (i + 1) * (PI / (parallelSize + 2));
	}

	int count = 0;
	float* top = new float[3] {0, 1, 0};
	for (int i = 0; i < 3; i++)
	{
		buffer[count++] = top[count];
	}
	delete[] top;

	for (int y = 0; y < parallelSize; y++)
	{
		for (int x = 0; x < meridianSize; x++)
		{
			buffer[count++] = sin(meridians[x]) * cos(parallels[y]);
			buffer[count++] = cos(meridians[x]);
			buffer[count++] = sin(meridians[x]) * sin(parallels[y]);
		}
	}

	float* bot = new float[3]{ 0, -1, 0 };
	for (int i = 0; i < 3; i++)
	{
		buffer[count++] = bot[count];
	}
	delete[] bot;
	delete[] meridians;
	delete[] parallels;

}

