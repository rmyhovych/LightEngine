#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "stb_image.h"
#include "window_gl.h"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void addBufferObject(float* buffer, int bufferSize, int attributeSize);
	void addElementObject(GLuint* elements, int elementSize);
	void addTexture(const char* name);

	void addLayout(int location, int size, int position);

	GLuint bindUniform(const char* name);

	void use();

	void draw();

private:
	void checkCompileErrors(unsigned int shader, std::string type);

private:
	GLuint* vao_;
	GLuint* vbo_;
	GLuint* ebo_;
	GLuint* texture_;

	int bufferSize_;
	int elementSize_;
	int attributeSize_;
};