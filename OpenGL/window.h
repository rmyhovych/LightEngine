#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Camera;

class Window
{
public:

	Window(int width, int height);
	~Window();

	bool isClosing();

	void swapBuffers();

private:

	GLFWwindow* handle;


	int width;
	int height;
};
