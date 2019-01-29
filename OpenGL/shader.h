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
#include "window.h"




class Shader
{


	//=============================================================================================
	//  STATIC
	//=============================================================================================

public:

	static GLuint vao;
	static GLuint ebo;

	static int vertexDataSize;
	static int elementDataSize;



	static void addVertexArray();

	static void addVertexBuffer(const char* path);

	static void addElementBuffer(const char* path);

	static void linkLayout(int index, int size, int attributeSize, int offset);

		
	static void render(int size, bool ebo);







	//=============================================================================================
	//  OBJECT
	//=============================================================================================

public:

	Shader(const char* vertexCodePath, const char* fragmentCodePath);


	int getUniformLocation(const char* name);

	void use();

private:

	GLuint id;

};






struct ByteBuffer
{
	uint8_t* data;
	unsigned size;
};


ByteBuffer loadFile(const char* path);



GLuint compileShader(GLuint type, ByteBuffer shaderCode);

GLuint createProgram(ByteBuffer vertexShaderCode, ByteBuffer fragmentShaderCode);