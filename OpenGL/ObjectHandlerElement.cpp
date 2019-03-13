#include "ObjectHandlerVertex.h"



ObjectHandlerVertex::ObjectHandlerVertex(const char* vertexPath) :
	vao(0),
	nVertices(0)
{
	FileData vertexBuffer(vertexPath);
	nVertices = vertexBuffer.size;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	Shader::addVertexBuffer(vertexBuffer);
	Shader::linkLayout(0, 3, 6, 0);
	Shader::linkLayout(1, 3, 6, 3);


	glBindVertexArray(0);
}


ObjectHandlerVertex::~ObjectHandlerVertex()
{
}
