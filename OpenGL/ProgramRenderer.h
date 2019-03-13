#pragma once

#include "ObjectHandlerVertex.h"
#include "ObjectHandlerElement.h"

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

