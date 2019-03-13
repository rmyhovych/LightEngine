#pragma once


#include "ObjectHandler.h"

#include "Shader.h"


class ObjectHandlerVertex :
	public ObjectHandler
{
public:
	ObjectHandlerVertex(const char* vertexPath);
	~ObjectHandlerVertex();


	virtual void renderDepth();

	virtual void render();
	

private:

	virtual void initRendering();



	GLuint vao;

	unsigned nVertices;

};

