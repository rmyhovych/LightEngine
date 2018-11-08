#define STB_IMAGE_IMPLEMENTATION

#include "camera.h"
#include "shader.h"
#include "window_gl.h"

int width = 1200;
int height = 800;

bool pressed = false;
double scroll = 0;
glm::vec2 cursor;
float inputForce = 0.005;
void mouseInput(WindowGL& window, Camera& camera);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = yoffset;
}

int main()
{
	//	Create window
	WindowGL window(width, height);
	glfwSetScrollCallback(window.window_, scroll_callback);

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  0.0f,  -3.0f),
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

	std::vector<glm::mat4> models;

	for (int i = 0; i < positions.size(); i++)
	{
		models.push_back(glm::translate(glm::mat4(1.0f), positions[i]));
	}
	models[0] = glm::scale(models[0], glm::vec3(0.2f));

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	//==================	COLOR CUBES
	Shader colorCube("shaders/vertex.txt", "shaders/fragment.txt");

	colorCube.addBufferObject(vertices, 36, 6);

	colorCube.addLayout(0, 3, 0);
	colorCube.addLayout(1, 3, 3);

	// Fragment
	GLuint cLightPosLoc = colorCube.bindUniform("uLightPos");
	GLuint cLightColorLoc = colorCube.bindUniform("uLightColor");
	GLuint cColorLoc = colorCube.bindUniform("uColor");

	// Vertex
	GLuint cTranslationLoc = colorCube.bindUniform("uModel");
	GLuint cViewLoc = colorCube.bindUniform("uView");
	GLuint cProjectionLoc = colorCube.bindUniform("uProjection");
		
	//==================	LAMP
	Shader lampCube("shaders/vertex.txt", "shaders/fragmentLamp.txt");

	lampCube.addBufferObject(vertices, 36, 6);

	lampCube.addLayout(0, 3, 0);

	// Fragment
	GLuint lColorLoc = lampCube.bindUniform("uColor");

	// Vertex
	GLuint lTranslationLoc = lampCube.bindUniform("uModel");
	GLuint lViewLoc = lampCube.bindUniform("uView");
	GLuint lProjectionLoc = lampCube.bindUniform("uProjection");


	//---
	glm::vec3 lightColor = glm::vec3(1);

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
		models[0] = glm::translate(glm::mat4(1.0f), camera.getFocus());
		models[0] = glm::scale(models[0], glm::vec3(0.1f));
		
		lampCube.use();

		glUniform3f(lColorLoc, lightColor.x, lightColor.y, lightColor.z);
		glUniformMatrix4fv(lTranslationLoc, 1, GL_FALSE, glm::value_ptr(models[0]));
		glUniformMatrix4fv(lViewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
		glUniformMatrix4fv(lProjectionLoc, 1, GL_FALSE, camera.getProjection());
		lampCube.draw();

		colorCube.use();

		models[1] = glm::rotate(models[1], 0.001f, glm::normalize(glm::vec3(1, 1, 0)));
		for (int i = 1; i < models.size(); i++)
		{
			glUniform3f(cLightPosLoc, models[0][3][0], models[0][3][1], models[0][3][2]);
			glUniform3f(cLightColorLoc, lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(cColorLoc, 0.5f, 1.0f, 1.0f);

			glUniformMatrix4fv(cTranslationLoc, 1, GL_FALSE, glm::value_ptr(models[i]));
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