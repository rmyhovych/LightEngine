#include "window.h"

#include "camera.h"

double scroll = 0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = yoffset;
}




Window::Window(int width, int height) :
	keyInput(new bool[6]),
	rightClickPressed(false),
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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	//	Window creation + OpenGL Context
	windowHandle = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(windowHandle);
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
		keyInput[i] = false;
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
	return keyInput;
}



void Window::input()
{
	if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(windowHandle, GL_TRUE);
	}


	if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
	{
		keyInput[0] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_RELEASE)
	{
		keyInput[0] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
	{
		keyInput[1] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_RELEASE)
	{
		keyInput[1] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
	{
		keyInput[2] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_RELEASE)
	{
		keyInput[2] = false;
	}

	if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
	{
		keyInput[3] = true;
	}
	else if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_RELEASE)
	{
		keyInput[3] = false;
	}
}



void Window::mouseInput(Camera& camera)
{
	double x;
	double y;

	if (glfwGetMouseButton(windowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !rightClickPressed)
	{
		rightClickPressed = true;
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(windowHandle, &x, &y);
		glfwSetCursorPos(windowHandle, x, y);

		cursorPosition_.x = x;
		cursorPosition_.y = y;
	}
	else if (glfwGetMouseButton(windowHandle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		rightClickPressed = false;
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (rightClickPressed)
	{
		glfwGetCursorPos(windowHandle, &x, &y);

		camera.rotateCamera(inputForce_*(x - cursorPosition_.x), inputForce_*(y - cursorPosition_.y));
		glfwSetCursorPos(windowHandle, (double)cursorPosition_.x, (double)cursorPosition_.y);
	}

	if (scroll != 0)
	{

		if (scroll == 1)
		{
			camera.zoom /= 1.1;
		}
		else
		{
			camera.zoom *= 1.1;
		}

		scroll = 0;
	}
}