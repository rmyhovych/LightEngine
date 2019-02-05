#include "gl_window.h"

double scroll = 0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = yoffset;
}




GLWindow::GLWindow(int width, int height) :
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
	window_ = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	glfwSetScrollCallback(window_, scroll_callback);

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




	GLWindow::width = width;
	GLWindow::height = height;
}



GLWindow::~GLWindow()
{
	//	-- END GLFW --
	glfwTerminate();
}



bool* GLWindow::getInput()
{
	return keyInput_;
}



void GLWindow::input()
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



void GLWindow::mouseInput(Camera& camera)
{
	double x;
	double y;
	if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !pressed_)
	{
		pressed_ = true;
		glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(window_, &x, &y);
		glfwSetCursorPos(window_, x, y);

		cursorPosition_.x = x;
		cursorPosition_.y = y;
	}
	else if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		pressed_ = false;
		glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (pressed_)
	{
		glfwGetCursorPos(window_, &x, &y);

		camera.rotateCamera(inputForce_*(x - cursorPosition_.x), inputForce_*(y - cursorPosition_.y));
		glfwSetCursorPos(window_, (double)cursorPosition_.x, (double)cursorPosition_.y);
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