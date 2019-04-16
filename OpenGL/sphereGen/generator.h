#include <iomanip>
#include <string>

void generateSphere(std::string path)
{
	const int meridianSize = 50;
	const int parallelSize = 50;
	



	//	vec3 vertex buffer

	int topAndBottom = 2;
	int vectorSize = 3;

	float* vertexBuffer = new float[(parallelSize * meridianSize + topAndBottom) * vectorSize];


	//	generate angles for each meridian and parallel
	float* meridians = new float[meridianSize];
	float* parallels = new float[parallelSize];

	for (int i = 0; i < meridianSize; i++)
	{
		meridians[i] = i * (2 * PI / meridianSize);
	}

	for (int i = 0; i < parallelSize; i++)
	{
		parallels[i] = (i + 1) * (PI / (parallelSize + 1));
	}






	//	filling the buffer with 
	int bufferCounter = 0;

	float* top = new float[3] {0, 1, 0}; //	top vector
	for (int i = 0; i < 3; i++)
	{
		vertexBuffer[bufferCounter++] = top[i];
	}
	delete[] top;

	for (int y = 0; y < parallelSize; y++)
	{
		for (int x = 0; x < meridianSize; x++)
		{
			//	spherical coordinates
			vertexBuffer[bufferCounter++] = sin(parallels[y]) * cos(meridians[x]);
			vertexBuffer[bufferCounter++] = cos(parallels[y]);
			vertexBuffer[bufferCounter++] = sin(parallels[y]) * sin(meridians[x]);
		}
	}

	float* bottom = new float[3]{ 0, -1, 0 }; // bottom vector
	for (int i = 0; i < 3; i++)
	{
		vertexBuffer[bufferCounter++] = bottom[i];
	}
	delete[] bottom;


	delete[] meridians;
	delete[] parallels;








	//	unsigned int element buffer to index each vertex to make triangles with them (CCW)
	unsigned int* elementBuffer = new GLuint[3 * 2 * (meridianSize) * (parallelSize)];


	int eCount = 0;
	for (int i = 0; i < meridianSize; i++)
	{
		elementBuffer[eCount++] = 0;
		elementBuffer[eCount++] = (i + 1);
		elementBuffer[eCount++] = ((i + 1) % meridianSize) + 1;
	}
	for (int i = 0; i < parallelSize - 1; i++)
	{
		for (int j = 0; j < meridianSize; j++)
		{
			//	need a visual representation for this sh*t... it works tho
			elementBuffer[eCount++] = (i * meridianSize + j + 1);
			elementBuffer[eCount++] = ((i + 1) * meridianSize + j + 1);
			elementBuffer[eCount++] = (((i + 1) * meridianSize) + ((1 + j) % meridianSize) + 1);
			elementBuffer[eCount++] = (i * meridianSize + j + 1);
			elementBuffer[eCount++] = (((i + 1) * meridianSize) + ((1 + j) % meridianSize) + 1);
			elementBuffer[eCount++] = (i * meridianSize + ((j + 1) % meridianSize) + 1);
		}
	}
	int bufferSize = bufferCounter / 3;
	for (int i = bufferSize - meridianSize; i < bufferSize; i++)
	{
		elementBuffer[eCount++] = bufferSize - 1;
		elementBuffer[eCount++] = (((i - (bufferSize - meridianSize) + 1) % meridianSize) + (bufferSize - meridianSize)) - 1;
		elementBuffer[eCount++] = i - 1;
	}



	//	write every vertex in a binary file (number of floats first)
	std::ofstream sphereBuffer(path + "sphereBuffer", std::ios::binary);
	//sphereBuffer.write((char*)&bufferCounter, sizeof(bufferCounter));
	for (int i = 0; i < bufferCounter; i++)
	{
		sphereBuffer.write((char*)&(vertexBuffer[i]), sizeof(float));
	}
	sphereBuffer.close();


	//	write every element in a binary file (number of elements first)
	std::ofstream sphereElements(path + "sphereElements", std::ios::binary);
	//sphereElements.write((char*)&eCount, sizeof(eCount));
	for (int i = 0; i < eCount; i++)
	{
		sphereElements.write((char*)&(elementBuffer[i]), sizeof(GLuint));
	}
	sphereElements.close();


	//	clear memory
	delete[] vertexBuffer;
	delete[] elementBuffer;
}
