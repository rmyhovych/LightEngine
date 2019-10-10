#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "gl.h"

#include "FileReaderHandler.h"


class Shader
{


	//=============================================================================================
	//  STATIC
	//=============================================================================================

public:

	static void addVertexBuffer(FileData& vertexBuffer);
	static GLuint addElementBuffer(FileData& elementBuffer);

	static void linkLayout(int index, int size, int attributeSize, int offset);



	static GLuint createProgram(FileData& vertexShaderCode, FileData& fragmentShaderCode);


private:

	static GLuint compileShader(GLuint type, FileData& shaderCode);






	//=============================================================================================
	//  OBJECT
	//=============================================================================================

public:

	Shader(const std::string& vertexCodePath, const std::string& fragmentCodePath);


	int getUniformLocation(const char* name);

	void bindUbo(const char* name, GLuint binding);

	void use();

private:

	GLuint id;

};
