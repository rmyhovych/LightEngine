#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) :
	vao_(nullptr),
	vbo_(nullptr),
	ebo_(nullptr),
	texture_(nullptr)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::addBufferObject(float* buffer, int bufferSize, int attributeSize)
{
	attributeSize_ = attributeSize;
	bufferSize_ = bufferSize * attributeSize;

	vao_ = new GLuint;
	vbo_ = new GLuint;

	glGenVertexArrays(1, vao_);
	glGenBuffers(1, vbo_);

	glBindVertexArray(*vao_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_);
	glBufferData(GL_ARRAY_BUFFER, bufferSize_ * sizeof(float), buffer, GL_STATIC_DRAW);
}

void Shader::addElementObject(GLuint* elements, int elementSize)
{
	glBindVertexArray(*vao_);

	elementSize_ = elementSize;

	ebo_ = new GLuint;
	glGenBuffers(1, ebo_);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize * sizeof(float), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Shader::addTexture(const char* name)
{
	glBindVertexArray(*vao_);

	texture_ = new GLuint;

	glGenTextures(1, texture_);

	glBindTexture(GL_TEXTURE_2D, *texture_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Shader::addLayout(int location, int size, int position)
{
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, attributeSize_ * sizeof(float), (void*)(position * sizeof(float)));
	glEnableVertexAttribArray(location);
}

GLuint Shader::bindUniform(const char* name)
{
	return (glGetUniformLocation(ID, name));
}


void Shader::use()
{
	glUseProgram(ID);
	glBindVertexArray(*vao_);
	if (texture_ != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, *texture_);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (ebo_ != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo_);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Shader::draw()
{
	if (ebo_ == nullptr)
	{
		glDrawArrays(GL_TRIANGLES, 0, bufferSize_);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, elementSize_, GL_UNSIGNED_INT, 0);
	}
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}