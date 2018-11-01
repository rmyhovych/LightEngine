#include <iostream>

#include "baseFunctions.h"
#include "shader.h"

char* loadShader(std::string filename);

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
		0.75,	0.75,	0,		1.0,	0.0,	0.0,
		0.75,	-0.75,	0,		0.0,	1.0,	0.0,
		-0.75,	-0.75,	0,		0.0,	0.0,	1.0,
		-0.75,	0.75,	0,		0.5,	0.5,	0.5
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
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

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
	//	=== EVENT LOOP ===
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		program.use();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//	-- END GLFW --
	glfwTerminate();
	return 0;
}