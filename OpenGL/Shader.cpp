#include "Shader.h"


//=============================================================================================
//  STATIC
//=============================================================================================



void Shader::addVertexBuffer(FileData& vertexBuffer)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size, vertexBuffer.data, GL_STATIC_DRAW);
}


GLuint Shader::addElementBuffer(FileData& elementBuffer)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size, elementBuffer.data, GL_STATIC_DRAW);

	return ebo;
}



void Shader::linkLayout(int index, int size, int attributeSize, int offset)
{
	glVertexAttribPointer(index, size, GL_FLOAT, false, attributeSize * 4, (void*)(offset * 4));
	glEnableVertexAttribArray(index);
}








GLuint Shader::createProgram(FileData& vertexShaderCode, FileData& fragmentShaderCode)
{
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);


	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);


	//	Linking error
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}







GLuint Shader::compileShader(GLuint type, FileData& shaderCode)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, (GLchar**)&shaderCode.data, (GLint*)&shaderCode.size);
	glCompileShader(shader);


	//	Compile error
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << type + "COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}





//=============================================================================================
//  OBJECT
//=============================================================================================


Shader::Shader(const char* vertexCodePath, const char* fragmentCodePath)
{
	FileData vertexShaderCode(vertexCodePath);
	FileData fragmentShaderCode(fragmentCodePath);

	id = createProgram(vertexShaderCode, fragmentShaderCode);
}



int Shader::getUniformLocation(const char* name)
{
	return glGetUniformLocation(id, name);
}



void Shader::use()
{
	glUseProgram(id);
}


