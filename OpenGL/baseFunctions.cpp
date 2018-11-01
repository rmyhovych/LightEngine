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