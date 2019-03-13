#pragma once


#include "ObjectHandler.h"

#include "Shader.h"


class ObjectHandlerVertex :
	public ObjectHandler
{
public:
	ObjectHandlerVertex(const char* vertexPath);
	~ObjectHandlerVertex();


	void renderDepth();

	void render();
	

private:

	void initRendering();



	GLuint vao;

	unsigned nVertices;

};

