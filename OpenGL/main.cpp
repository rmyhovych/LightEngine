#include <iostream>

#include "baseFunctions.h"

char* loadShader(std::string filename);

int main()
{
	//	-- START GLFW --
	glfwInit();

	//	Create window
	GLFWwindow* window = windowInit(800, 600, "OpenGL");

	//	=== CODE ===

	//	Triangle vertecies (x, y, z) -> x, y = (-1, 1), (-1, 1)
	float vertecies[] = {
		0.75, 0.75, 1.0, 0, 0,
		0.75, -0.75, 0, 1.0, 0,
		-0.75, -0.75, 0, 0, 1.0,
		-0.75, 0.75, 0.5, 0.5, 0.5
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	//	-- Vertex Array Object --
	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	//	-- Vertex Buffer Object --
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Setting vbo as an active array buffer

	//	Copy vertex data to array buffer on the graphics card
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
	
	//	-- Element Array Object --
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);

	//	--- VERTEX SHADER ---
	//	Compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = loadShader("vertex.txt");
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//	Shader code compilation error
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//	--- FRAGMENT SHADER ---
	//	Compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = loadShader("fragment.txt");
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//	Shader code compilation error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	

	//	Combining shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//	Linking vertex data to attributes
	GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	GLuint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

	//	=== EVENT LOOP ===
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//	-- END GLFW --
	glfwTerminate();
	return 0;
}