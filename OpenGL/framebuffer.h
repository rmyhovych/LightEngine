#pragma once

#include "shader.h"
#include <vector>


class Framebuffer
{

	//=============================================================================================
	//  STATIC
	//=============================================================================================


public:

	static void addFramebuffer(float whRatio);



private:
	
	static const int resolution = 200;

	static int width;
	static int height;

	

	static GLuint vao;
	static int vboSize;

	static GLuint fbo;
	static GLuint texture;



	//=============================================================================================
	//  OBJECT
	//=============================================================================================

public:

	Framebuffer(int paletteNumber);

	void createUniforms();

	void renderOn();

	void draw();


private:

	Shader program;

	GLuint paletteTexture;


};

