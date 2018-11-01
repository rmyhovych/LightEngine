#include "baseFunctions.h"

GLFWwindow* windowInit(int width, int height, const char* name)
{
	//	Version 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	//	Core profile OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//	Forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//	Resizable window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//	Window creation + OpenGL Context
	GLFWwindow* window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//	Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}

char* loadShader(std::string filename)
{
	std::ifstream file;
	file.open("Shaders/" + filename);
	int filesize = 0;

	char* source = new char[1000];

	int charMax;
	for (charMax = 0; charMax < 1000 && !file.eof(); charMax++)
	{
		file.get(source[charMax]);
	}
	source[charMax - 1] = '\0';

	char* sourceCpy = new char[charMax];

	for (int ch = 0; ch < charMax; ch++)
	{
		sourceCpy[ch] = source[ch];
	}

	delete[] source;
	source = sourceCpy;

	file.close();

	return source;
}