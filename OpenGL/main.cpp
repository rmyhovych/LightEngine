#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"
#include "baseFunctions.h"
#include "shader.h"

int main()
{
	//	-- START GLFW --
	glfwInit();

	//	Create window
	GLFWwindow* window = windowInit(800, 600, "OpenGL");

	//	=== CODE ===

	Shader program("Shaders/vertex.txt", "Shaders/fragment.txt");

	//	Triangle vertecies (x, y, z) -> x, y = (-1, 1), (-1, 1)
	float vertecies[] = {
		0.75,	0.75,	0,		1.0,	0.0,	0.0,		1.0,	1.0,
		0.75,	-0.75,	0,		0.0,	1.0,	0.0,		1.0,	0.0,
		-0.75,	-0.75,	0,		0.0,	0.0,	1.0,		0.0,	0.0,
		-0.75,	0.75,	0,		0.5,	0.5,	0.5,		0.0,	1.0
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

	//	Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//		color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//		texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//	=== EVENT LOOP ===
	while (!glfwWindowShouldClose(window))
	{
		windowInput(window);

		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		program.use();

		glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(float), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//	-- END GLFW --
	glfwTerminate();
	return 0;
}