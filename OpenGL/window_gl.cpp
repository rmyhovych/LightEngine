#include "window_gl.h"



WindowGL::WindowGL(int width, int height) :
	width_(width),
	height_(height),
	keyInput_(new bool[6])
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


	//	Window creation + OpenGL Context
	window_ = glfwCreateWindow(width_, height_, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

	//	Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 6; i++)
	{
		keyInput_[i] = false;
	}
}

WindowGL::~WindowGL()
{
	//	-- END GLFW --
	glfwTerminate();
}

bool* WindowGL::getInput()
{
	return keyInput_;
}

void WindowGL::input()
{
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, GL_TRUE);
	}


	if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
	{
		keyInput_[0] = true;
	}
	else if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_RELEASE)
	{
		keyInput_[0] = false;
	}

	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
	{
		keyInput_[1] = true;
	}
	else if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_RELEASE)
	{
		keyInput_[1] = false;
	}

	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
	{
		keyInput_[2] = true;
	}
	else if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_RELEASE)
	{
		keyInput_[2] = false;
	}

	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
	{
		keyInput_[3] = true;
	}
	else if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_RELEASE)
	{
		keyInput_[3] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
