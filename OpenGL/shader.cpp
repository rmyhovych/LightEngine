#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) :
	vao_(nullptr),
	vbo_(nullptr),
	ebo_(nullptr),
	fbo_(nullptr),
	rbo_(nullptr),
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
	bufferSize_ = bufferSize;

	vao_ = new GLuint;
	vbo_ = new GLuint;

	glGenVertexArrays(1, vao_);
	glGenBuffers(1, vbo_);

	glBindVertexArray(*vao_);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo_);
	glBufferData(GL_ARRAY_BUFFER, bufferSize_ * attributeSize_ * sizeof(float), buffer, GL_STATIC_DRAW);
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

void Shader::addFramebufferObject(int& w, int& h)
{
	int width = w / 3;
	int height = h / 3;
	float fboVertecies[] = {

		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,


		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f,  1.0f,  1.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f
	};

	addBufferObject(fboVertecies, 6, 4);

	fbo_ = new GLuint;
	glGenFramebuffers(1, fbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo_);

	texture_ = new GLuint;
	glGenTextures(1, texture_);
	glBindTexture(GL_TEXTURE_2D, *texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture_, 0);

	rbo_ = new GLuint;
	glGenRenderbuffers(1, rbo_);
	glBindRenderbuffer(GL_RENDERBUFFER, *rbo_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *rbo_);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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


void Shader::uniformMat4Ptr(const char* name, glm::f32* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, matrix);

}

void Shader::uniformVec3(const char* name, glm::vec3& vector)
{
	glUniform3f(glGetUniformLocation(ID, name), vector.x, vector.y, vector.z);
}

void Shader::uniformFloat(const char* name, float number)
{
	glUniform1f(glGetUniformLocation(ID, name), number);
}

void Shader::uniformInt(const char* name, int number)
{
	glUniform1i(glGetUniformLocation(ID, name), number);
}


void Shader::use()
{
	glUseProgram(ID);
	glBindVertexArray(*vao_);

	if (fbo_ != nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT);

	}

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

void Shader::render()
{
	if (fbo_ != nullptr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo_);
		glEnable(GL_DEPTH_TEST);
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