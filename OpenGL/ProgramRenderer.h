#pragma once

#include "VBOHandler.h"
#include "EBOHandler.h"

#include "Shader.h"


class ProgramRenderer
{
public:
	ProgramRenderer(const char* pathVertex, const char* pathFragment);

	~ProgramRenderer();


	void draw();

private:

	void createUniforms();



	Shader program;


	std::vector<ObjectHandler*> objectHandlerArray;

};

