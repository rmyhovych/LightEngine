#pragma once


#include "ObjectHandler.h"



class ProgramRenderer
{
public:
	ProgramRenderer(const char* pathVertex, const char* pathFragment);

	~ProgramRenderer();


	ObjectHandlerVertex* addObjectHandler(const char* arrayPath);
	ObjectHandlerVertex* addObjectHandler(const float data[], int size);

	ObjectHandlerElement* addObjectHandler(const char* arrayPath, const char* elementPath);



	void draw();

private:

	void createUniforms();



	Shader program;


	std::vector<ObjectHandler*> objectHandlerArray;

};

