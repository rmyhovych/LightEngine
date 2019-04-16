#include "window.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height) :
	width(width),
	height(height),

	camera(nullptr)
{
	//	-- START GLFW --
	glfwInit();


	//	Version 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);


	//	Core profile OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//	Forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	//	Window creation + OpenGL Context
	handle = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(handle);
	glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);



	//	Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);
	
}



Window::~Window()
{
	//	-- END GLFW --
	glfwTerminate();

	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}
}

Camera* Window::createCamera(float zoom, float angleH, float angleV, const glm::vec3& focus)
{
	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}

	camera = new Camera(width, height, zoom, angleH, angleV, focus);

	return camera;
}

bool Window::isClosing()
{
	return glfwWindowShouldClose(handle);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(handle);
	glfwPollEvents();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}