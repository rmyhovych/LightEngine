#include "shader.h"




//=============================================================================================
//  STATIC
//=============================================================================================



void Shader::addVertexArray()
{
	glGenVertexArrays(1, &vao);
}



void Shader::addVertexBuffer(const char* path)
{
	ByteBuffer vertexBuffer = loadFile(path);
	vertexDataSize = vertexBuffer.size;


	glGenBuffers(1, &vao);


	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size, vertexBuffer.data, GL_STATIC_DRAW);
}



void Shader::addElementBuffer(const char* path)
{
	ByteBuffer elementBuffer = loadFile(path);
	vertexDataSize = elementBuffer.size / 4;


	glGenBuffers(1, &ebo);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size, elementBuffer.data, GL_STATIC_DRAW);

}



void Shader::linkLayout(int index, int size, int attributeSize, int offset)
{
	glVertexAttribPointer(index, size, GL_FLOAT, false, attributeSize * 4, (void*)(offset * 4));
	glEnableVertexAttribArray(index);
}



void Shader::render(int size, bool eboRender)
{
	if (!eboRender)
	{
		glDrawArrays(GL_TRIANGLES, 0, size);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}
}







//=============================================================================================
//  OBJECT
//=============================================================================================


Shader::Shader(const char* vertexCodePath, const char* fragmentCodePath)
{
	ByteBuffer vertexShaderCode = loadFile(vertexCodePath);
	ByteBuffer fragmentShaderCode = loadFile(fragmentCodePath);

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





















ByteBuffer loadFile(const char* path)
{
	ByteBuffer buffer;



	std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);

	buffer.size = file.tellg();



	buffer.data = new uint8_t[buffer.size];

	file.seekg(0, file.beg);




	file.read((char*)buffer.data, buffer.size);

	file.close();


	return buffer;
}





GLuint compileShader(GLuint type, ByteBuffer shaderCode)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, (GLchar**)&shaderCode.data, (GLint*)&shaderCode.size);
	glCompileShader(shader);

	return shader;
}

GLuint createProgram(ByteBuffer vertexShaderCode, ByteBuffer fragmentShaderCode)
{
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);


	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
