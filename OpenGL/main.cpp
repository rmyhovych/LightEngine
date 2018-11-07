#define STB_IMAGE_IMPLEMENTATION

#include "camera.h"
#include "shader.h"
#include "window_gl.h"

bool pressed = false;
glm::vec2 cursor;
float inputForce = 0.005;

void mouseInput(WindowGL& window, Camera& camera);

int main()
{
	//	Create window
	WindowGL window(1500, 1000);

	
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
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//==================	COLOR CUBE
	Shader colorCube("shaders/colorVertex.txt", "shaders/colorFragment.txt");

	colorCube.addBufferObject(eVertices, 8, 6);
	colorCube.addElementObject(elements, 36);

	colorCube.addLayout(0, 3, 0);
	colorCube.addLayout(1, 3, 3);

	GLuint cModelLoc = glGetUniformLocation(colorCube.ID, "uModel");
	GLuint cViewLoc = glGetUniformLocation(colorCube.ID, "uView");
	GLuint cProjectionLoc = glGetUniformLocation(colorCube.ID, "uProjection");
	
	//===================	TEXTURE CUBE
	Shader textureCube("shaders/vertex.txt", "shaders/fragment.txt");
	textureCube.addBufferObject(bVertices, 36, 5);
	textureCube.addTexture("textures/rainbow.png");

	textureCube.addLayout(0, 3, 0);
	textureCube.addLayout(2, 2, 3);

	GLuint modelLoc = textureCube.bindUniform("uModel");
	GLuint viewLoc = textureCube.bindUniform("uView");
	GLuint projectionLoc = textureCube.bindUniform("uProjection");
	
	Camera camera(window.getInput(), 15, positions[1]);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(PI/4, ((float)window.width_ / (float)window.height_), 0.1f, 100.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	=== EVENT LOOP ===
	while (!glfwWindowShouldClose(window.window_))
	{
		window.input();
		mouseInput(window, camera);

		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.refresh();

		models[1] = glm::rotate(models[1], 0.01f, glm::normalize(glm::vec3(1, 1, 0)));
		//models[0] = glm::translate(models[0], 0.01f * glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), cos(glfwGetTime())));

		textureCube.use();
		for (int i = 0; i < 5; i++)
		{
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(models[i]));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
			textureCube.draw();

		}

		colorCube.use();
		for (int i = 5; i < 10; i++)
		{
			glUniformMatrix4fv(cModelLoc, 1, GL_FALSE, glm::value_ptr(models[i]));
			glUniformMatrix4fv(cViewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
			glUniformMatrix4fv(cProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
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