#include "ObjectHandler.h"




////////////////////////////
////	INTERFACE		////
////////////////////////////

ObjectHandler::ObjectHandler() :
	vao(0)
{
}


ObjectHandler::~ObjectHandler()
{
	for (int i = 0; i < objectArray.size(); i++)
	{
		delete objectArray[i];
		objectArray[i] = nullptr;
	}

	glDeleteVertexArrays(1, &vao);
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





////////////////////////
////	VERTEX		////
////////////////////////

ObjectHandlerVertex::ObjectHandlerVertex(const char* vertexPath) :

	nVertices(0)
{
	FileData vertexBuffer(vertexPath);
	nVertices = vertexBuffer.size / (sizeof(float) * 6); // 6 -> vertex size

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	Shader::addVertexBuffer(vertexBuffer);


	Shader::linkLayout(0, 3, 6, 0);
	Shader::linkLayout(1, 3, 6, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


ObjectHandlerVertex::ObjectHandlerVertex(FileData& vertexData) :
	nVertices(vertexData.size / (sizeof(float) * 6))
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	Shader::addVertexBuffer(vertexData);


	Shader::linkLayout(0, 3, 6, 0);
	Shader::linkLayout(1, 3, 6, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


ObjectHandlerVertex::~ObjectHandlerVertex()
{
}



void ObjectHandlerVertex::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(vao);

	for (int i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->use(uniforms);
		glDrawArrays(GL_TRIANGLES, 0, nVertices);
	}
}








////////////////////////
////	ELEMENT		////
////////////////////////

ObjectHandlerElement::ObjectHandlerElement(const char* vertexPath, const char* elementPath) :

	nElements(0)
{
	FileData vertexBuffer(vertexPath);
	FileData elementBuffer(elementPath);
	nElements = elementBuffer.size / sizeof(int);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Shader::addVertexBuffer(vertexBuffer);
	ebo = Shader::addElementBuffer(elementBuffer);


	Shader::linkLayout(0, 3, 3, 0);
	Shader::linkLayout(1, 3, 3, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ObjectHandlerElement::ObjectHandlerElement(FileData& vertexData, FileData& elementData) :
	nElements(elementData.size / sizeof(int)),
	ebo(0)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Shader::addVertexBuffer(vertexData);
	ebo = Shader::addElementBuffer(elementData);


	Shader::linkLayout(0, 3, 3, 0);
	Shader::linkLayout(1, 3, 3, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


ObjectHandlerElement::~ObjectHandlerElement()
{
}


void ObjectHandlerElement::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	for (int i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->use(uniforms);
		glDrawElements(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, 0);
	}
}
