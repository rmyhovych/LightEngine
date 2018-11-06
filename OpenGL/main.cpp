#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.h"
#include "shader.h"
#include "window_gl.h"

bool pressed = false;
glm::vec2 cursor;
float inputForce = 0.005;

void mouseInput(WindowGL& window, Camera& camera);

int main()
{
	//	-- START GLFW --
	glfwInit();

	//	Create window
	WindowGL window(1500, 1000);

	//	=== CODE ===

	Shader program("Shaders/vertex.txt", "Shaders/fragment.txt");

	//	Triangle vertecies (x, y, z) -> x, y = (-1, 1), (-1, 1)
	
	/*
	float vertices[] = {
		0.5,	0.5,	0,		1.0,	0.0,	0.0,		1.0,	1.0,
		0.5,	-0.5,	0,		0.0,	1.0,	0.0,		1.0,	0.0,
		-0.5,	-0.5,	0,		0.0,	0.0,	1.0,		0.0,	0.0,
		-0.5,	0.5,	0,		0.5,	0.5,	0.5,		0.0,	1.0
	};
	*/

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	float vertices[] = {
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

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0,
	};


	//	-- Vertex Array Object --
	GLuint vao, vbo, ebo, texture;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenTextures(1, &texture);

	//	Bind VAO
	glBindVertexArray(vao);

	//	Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Setting vbo as an active array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	Bind EBO
	/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	*/

	//	Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load("textures/snow.png", &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	//		position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//		color
	/*
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/

	//		texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//	-- Uniform --
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	GLuint modelLoc = glGetUniformLocation(program.ID, "uModel");
	GLuint viewLoc = glGetUniformLocation(program.ID, "uView");
	GLuint projectionLoc = glGetUniformLocation(program.ID, "uProjection");

	Camera camera(window.getInput());

	projection = glm::perspective(PI/4, ((float)window.width_ / (float)window.height_), 0.1f, 1000.0f);

	//	=== EVENT LOOP ===
	while (!glfwWindowShouldClose(window.window_))
	{
		window.input();
		mouseInput(window, camera);

		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.refresh();

		program.use();
		for (int i = 0; i < 10; i++)
		{
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(0.1f), cubePositions[i])));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		
		//glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(float), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}

	//	-- END GLFW --
	glfwTerminate();
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