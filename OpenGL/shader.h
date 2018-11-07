#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

#include "window_gl.h"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void addBufferObject(float* buffer, int bufferSize);
	void addElementObject();

	void use();


private:
	void checkCompileErrors(unsigned int shader, std::string type);

private:
	GLuint* vao_;
	GLuint* vbo_;
	GLuint* ebo_;
	GLuint* texture_;
};