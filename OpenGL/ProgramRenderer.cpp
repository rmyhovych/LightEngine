#include "ProgramRenderer.h"

ProgramRenderer::ProgramRenderer(const char* pathVertex, const char* pathFragment) :
	program(pathVertex, pathFragment)
{
	createUniforms();
}

ProgramRenderer::~ProgramRenderer()
{
	for (int i = 0; i < objectHandlerArray.size(); i++)
	{
		delete objectHandlerArray[i];
		objectHandlerArray[i] = nullptr;
	}
}



ObjectHandler* ProgramRenderer::addObjectHandler(const char* arrayPath)
{
	ObjectHandler* oHandler = new ObjectHandlerVertex(arrayPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}




ObjectHandler* ProgramRenderer::addObjectHandler(const char* arrayPath, const char* elementPath)
{
	ObjectHandler* oHandler = new ObjectHandlerElement(arrayPath, elementPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}
