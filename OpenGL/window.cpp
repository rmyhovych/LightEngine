#include "window.h"


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



	//	Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//glCullFace(GL_FRONT);
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

Camera* Window::createCamera(float zoom, const glm::vec3& focus, const glm::vec3& direction)
{
	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}

	camera = new Camera(width, height, zoom, focus, direction);

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
