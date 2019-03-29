#include "ObjectHandler.h"




////////////////////////////
////	INTERFACE		////
////////////////////////////

ObjectHandler::ObjectHandler()
{
}


ObjectHandler::~ObjectHandler()
{
	for (int i = 0; i < objectArray.size(); i++)
	{
		delete objectArray[i];
		objectArray[i] = nullptr;
	}
}

Object* ObjectHandler::addObject(
	const glm::vec3& position, 
	const glm::vec3& orientation, 
	const glm::vec3& scale, 
	const glm::vec3& color)
{
	Object* objectPtr = new Object(position, orientation, scale, color);

	objectArray.push_back(objectPtr);

	return objectPtr;
}



void ObjectHandler::render()
{
}









////////////////////////
////	VERTEX		////
////////////////////////

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
		
	}
}








////////////////////////
////	ELEMENT		////
////////////////////////

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
