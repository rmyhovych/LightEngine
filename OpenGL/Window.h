#pragma once

#define GLEW_STATIC	
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "PicoRender/glm/glm.hpp"
#include "PicoRender/glm/gtc/matrix_transform.hpp"
#include "PicoRender/glm/gtc/type_ptr.hpp"


#include "PicoRender/Camera.h"



class Window
{
public:

	Window(int width, int height);
	~Window();


	Camera* createCamera(float zoom = 20, 
		float angleH = 0, float angleV = PI / 2,
		const glm::vec3& focus = glm::vec3(0, 0, 0));


	bool isClosing();

	void swapBuffers();

private:

	GLFWwindow* handle;

	int width;
	int height;

	Camera* camera;
};
