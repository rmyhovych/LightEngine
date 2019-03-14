#include "ObjectHandlerVertex.h"



ObjectHandlerVertex::ObjectHandlerVertex(const char* vertexPath) :
	vao(0),

	nVertices(0)
{
	FileData vertexBuffer(vertexPath);
	nVertices = vertexBuffer.size / (sizeof(float) * 6); // 6 -> vertex size

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


// program is set
void ObjectHandlerVertex::renderDepth()
{
	for (int i = 0; i < objectArray.size(); i++)
	{
		glUniformMatrix4fv(modelHandleShadow, 1, GL_FALSE, glm::value_ptr(mModel));
	}
}
