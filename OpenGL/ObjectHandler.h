#pragma once

#include "GLShader.h"



class ObjectHandler
{
public:
	ObjectHandler(const char* vPathRender, const char* fPathRender);

	~ObjectHandler();



	void draw();

	void drawDepth();



protected:

	void createUniforms();

	GLShader program;






};

