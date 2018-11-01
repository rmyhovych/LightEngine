#include <iostream>

#include "baseFunctions.h"
#include "shader.h"

int main()
{
	//	-- START GLFW --
	glfwInit();

	//	Create window
	GLFWwindow* window = windowInit(1000, 600, "OpenGL");

	//	=== CODE ===

	Shader program("Shaders/vertex.txt", "Shaders/fragment.txt");

	//	Triangle vertecies (x, y, z) -> x, y = (-1, 1), (-1, 1)
	float vertecies[] = {
		0.55,	0.75,	0,		1.0,	0.0,	0.0,
		0.55,	-0.75,	0,		0.0,	1.0,	0.0,
		-0.55,	-0.75,	0,		0.0,	0.0,	1.0,
		-0.55,	0.75,	0,		0.5,	0.5,	0.5,
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0,
	};

	float texCoords[] = {
		0.0, 0.0,
		0.5, 0.0,
		0.5, 0.5
	};

	//	-- Vertex Array Object --
	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	//	Bind VAO
	glBindVertexArray(vao);

	//	Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Setting vbo as an active array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
	
	//	Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//		position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//		color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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