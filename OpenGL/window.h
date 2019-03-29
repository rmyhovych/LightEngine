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
	GLFWwindow* windowHandle;

	bool* keyInput;


	Window(int width, int height);
	~Window();

	bool* getInput();

	void input();
	void mouseInput(Camera& camera);

private:

	int width;
	int height;


	bool rightClickPressed;

	glm::vec2 cursorPosition_;
	float inputForce_;
};
