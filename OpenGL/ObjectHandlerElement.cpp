#include "ObjectHandlerElement.h"



ObjectHandlerElement::ObjectHandlerElement(const char* vertexPath, const char* elementPath) :
	vao(0),
	ebo(0),

	nElements(0)
{
	FileData vertexBuffer(vertexPath);
	FileData elementBuffer(elementPath);
	nElements = elementBuffer.size / sizeof(int);


	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);


	Shader::addVertexBuffer(vertexBuffer);
	Shader::addElementBuffer(elementBuffer);


	Shader::linkLayout(0, 3, 3, 0);
	Shader::linkLayout(1, 3, 3, 0);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


ObjectHandlerElement::~ObjectHandlerElement()
{
}
