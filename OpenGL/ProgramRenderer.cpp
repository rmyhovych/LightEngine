#include "ProgramRenderer.h"

ProgramRenderer::ProgramRenderer(const char* pathVertex, const char* pathFragment) :
	program(pathVertex, pathFragment)
{
	createUniforms();
}

ProgramRenderer::~ProgramRenderer()
{
	for (uint32_t i = 0; i < objectHandlerArray.size(); i++)
	{
		delete objectHandlerArray[i];
		objectHandlerArray[i] = nullptr;
	}
}
