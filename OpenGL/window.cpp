#include "window.h"

double scroll = 0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = yoffset;
}




Window::Window(int width, int height) :
	keyInput_(new bool[6]),
	pressed_(false),
	inputForce_(0.005)
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
	windowHandle = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(windowHandle);
	glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
	glfwSetScrollCallback(windowHandle, scroll_callback);


	//	Setup GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	
	for (int i = 0; i < 6; i++)
	{
		keyInput_[i] = false;
	}






	Window::width = width;
	Window::height = height;
}



Window::~Window()
{
	//	-- END GLFW --
	glfwTerminate();
}



bool* Window::getInput()
{
	return keyInput_;
}



void Window::input()
{
	if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(windowHandle, GL_TRUE);
	}


	if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
	{
		keyInput_[0] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_RELEASE)
	{
		keyInput_[0] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
	{
		keyInput_[1] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_RELEASE)
	{
		keyInput_[1] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
	{
		keyInput_[2] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_RELEASE)
	{
		keyInput_[2] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
	{
		keyInput_[3] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_RELEASE)
	{
		keyInput_[3] = false;
	}
}



void Window::mouseInput(Camera& camera)
{
	double x;
	double y;
	if (glfwGetMouseButton(windowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !pressed_)
	{
		pressed_ = true;
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(windowHandle, &x, &y);
		glfwSetCursorPos(windowHandle, x, y);

		cursorPosition_.x = x;
		cursorPosition_.y = y;
	}
	else if (glfwGetMouseButton(windowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		pressed_ = false;
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (pressed_)
	{
		glfwGetCursorPos(windowHandle, &x, &y);

		camera.rotateCamera(inputForce_*(x - cursorPosition_.x), inputForce_*(y - cursorPosition_.y));
		glfwSetCursorPos(windowHandle, (double)cursorPosition_.x, (double)cursorPosition_.y);
	}

	if (scroll != 0)
	{

		if (scroll == 1)
		{
			camera.zoom_ /= 1.1;
		}
		else
		{
			camera.zoom_ *= 1.1;
		}

		scroll = 0;
	}
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}