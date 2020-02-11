#include "Window.h"

#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int heigth) :
	m_width(width),
	m_height(heigth)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "PicoEngine", NULL, NULL);

	if (m_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glfwMakeContextCurrent(m_window);
	gl3wInit();

	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::isOpen()
{
	return glfwWindowShouldClose(m_window) == 0;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}