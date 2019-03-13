#pragma once


#include "ObjectHandler.h"

#include "Shader.h"


class ObjectHandlerElement :
	public ObjectHandler
{
public:
	ObjectHandlerElement(const char* vertexPath, const char* elementPath);
	~ObjectHandlerElement();


	virtual void renderDepth();

	virtual void render();


private:

	virtual void initRendering();

	GLuint vao;
	GLuint ebo;

	unsigned nElements;

};

