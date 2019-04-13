#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include "FileData.h"



class Shader
{


	//=============================================================================================
	//  STATIC
	//=============================================================================================

public:

	static void addVertexBuffer(FileData& vertexBuffer);
	static void addVertexBuffer(const float data[], int size);

	static void addElementBuffer(FileData& elementBuffer);

	static void linkLayout(int index, int size, int attributeSize, int offset);



	GLuint createProgram(FileData& vertexShaderCode, FileData& fragmentShaderCode);


		


	//	USE DIRECTLY IN CODE
	static void drawArrays(int size);
	static void renderElements(int size);



private:

	GLuint compileShader(GLuint type, FileData& shaderCode);






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
