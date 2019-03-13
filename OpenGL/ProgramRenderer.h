#pragma once

#include "ObjectHandler.h"
#include "GLShader.h"


class ProgramRenderer
{
public:
	ProgramRenderer(const char* pathVertex, const char* pathFragment);

	~ProgramRenderer();


	void draw();

private:

	void createUniforms();



	GLShader program;


	std::vector<ObjectHandler*> objectHandlerArray;



};

