#define STB_IMAGE_IMPLEMENTATION

#include "camera.h"
#include "shader.h"
#include "window_gl.h"

int width = 1200;
int height = 800;

bool pressed = false;
glm::vec2 cursor;
float inputForce = 0.005;
void mouseInput(WindowGL& window, Camera& camera);

int main()
{
	//	Create window
	WindowGL window(width, height);

	
	float eVertices[] = {
		0.5,	0.5,	0.5,		1.0,	0.0,	0.0,
		-0.5,	0.5,	0.5,		0.0,	1.0,	0.0,
		0.5,	-0.5,	0.5,		0.0,	0.0,	1.0,
		-0.5,	-0.5,	0.5,		1.0,	1.0,	1.0,
		0.5,	0.5,	-0.5,		1.0,	0.0,	0.0,
		-0.5,	0.5,	-0.5,		0.0,	1.0,	0.0,
		0.5,	-0.5,	-0.5,		0.0,	0.0,	1.0,
		-0.5,	-0.5,	-0.5,		0.0,	0.0,	0.0
	};
	
	GLuint elements[] = {
		0, 1, 2, 
		3, 1, 2,
		4, 5, 6, 
		7, 5, 6,
		2, 0, 6,
		4, 0, 6,
		1, 5, 0, 
		4, 5, 0,
		1, 5, 3, 
		7, 5, 3,
		3, 7, 2, 
		6, 7, 2 
	};

	float pVertices[] = {
		0.5,	0.0,	0.5,		0.2,	0.4,	0.3,
		-0.5,	0.0,	0.5,		0.2,	0.4,	0.3,
		0.5,	0.0,	-0.5,		0.2,	0.4,	0.3,
		-0.5,	0.0,	-0.5,		0.2,	0.4,	0.3
	};

	GLuint pElements[] = {
		0, 1, 2,
		3, 1, 2,
	};

	glm::vec3 positions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f,  0.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 models[10];

	for (int i = 0; i < 10; i++)
	{
		glm::mat4 matrix(1.0f);
		models[i] = glm::translate(matrix, positions[i]);
	}

	float bVertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
	};

	//==================	COLOR CUBES
	Shader colorCube("shaders/vertex.txt", "shaders/fragment.txt");

	colorCube.addBufferObject(bVertices, 36, 3);

	colorCube.addLayout(0, 3, 0);

	GLuint cColorLoc = colorCube.bindUniform("uColor");
	GLuint cModelLoc = colorCube.bindUniform("uModel");
	GLuint cViewLoc = colorCube.bindUniform("uView");
	GLuint cProjectionLoc = colorCube.bindUniform("uProjection");
		


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//	=== EVENT LOOP ===

	Camera camera(width, height, window.getInput(), 10, positions[0]);
	while (!glfwWindowShouldClose(window.window_))
	{
		camera.adjust(window.window_);

		window.input();
		mouseInput(window, camera);

		glClearColor(0.07f, 0.10f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.refresh();




		colorCube.use();

		models[1] = glm::rotate(models[1], 0.001f, glm::normalize(glm::vec3(1, 1, 0)));
		for (int i = 1; i < 10; i++)
		{
			glUniform3f(cColorLoc, 0.5f, 1.0f, 1.0f);
			glUniformMatrix4fv(cModelLoc, 1, GL_FALSE, glm::value_ptr(models[i]));
			glUniformMatrix4fv(cViewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
			glUniformMatrix4fv(cProjectionLoc, 1, GL_FALSE, camera.getProjection());
			colorCube.draw();
		}
		
		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}

	return 0;
}

void mouseInput(WindowGL& window, Camera& camera)
{
	double x;
	double y;
	if (glfwGetMouseButton(window.window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !pressed)
	{
		pressed = true;
		glfwSetInputMode(window.window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(window.window_, &x, &y);
		glfwSetCursorPos(window.window_, x, y);

		cursor.x = x;
		cursor.y = y;
	}
	else if (glfwGetMouseButton(window.window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		pressed = false;
		glfwSetInputMode(window.window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (pressed)
	{		
		glfwGetCursorPos(window.window_, &x, &y);

		camera.rotateCamera(inputForce*(x - cursor.x), inputForce*(y - cursor.y));
		glfwSetCursorPos(window.window_, (double)cursor.x, (double)cursor.y);
	}
}