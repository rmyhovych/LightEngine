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





ObjectHandlerVertex* ProgramRenderer::addObjectHandler(const char* arrayPath)
{
	ObjectHandlerVertex* oHandler = new ObjectHandlerVertex(arrayPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}

ObjectHandlerVertex* ProgramRenderer::addObjectHandler(const float data[], int size)
{
	return nullptr;
}




ObjectHandlerElement* ProgramRenderer::addObjectHandler(const char* arrayPath, const char* elementPath)
{
	ObjectHandlerElement* oHandler = new ObjectHandlerElement(arrayPath, elementPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}

void ProgramRenderer::createUniforms()
{
}
