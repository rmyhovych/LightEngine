#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"
#include "window_gl.h"

struct Uniform
{
	GLuint id;
	std::string name;
};

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void addBufferObject(float* buffer, int bufferSize, int attributeSize);
	void addElementObject(GLuint* elements, int elementSize);
	void addTexture(const char* name);

	void addLayout(int location, int size, int position);

	void uniformMat4Ptr(const char* name, glm::f32* matrix);
	void uniformVec3(const char* name, glm::vec3& vector);
	void uniformFloat(const char* name, float number);
	void uniformInt(const char* name, int number);

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