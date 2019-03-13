#pragma once

#include "ObjectHandler.h"
#include "GLShader.h"


class ProgramRenderer
{
public:
	ProgramRenderer(const char* vPathRender, const char* fPathRender);

	~ProgramRenderer();



private:

	void createUniforms();

	GLShader program;





};

