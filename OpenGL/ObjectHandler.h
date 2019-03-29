#pragma once

#include <vector>

#include "Object.h"
#include "ObjectUniforms.h"


#include "Shader.h"




class ObjectHandler
{
public:
	ObjectHandler();

	~ObjectHandler();

	Object* addObject(
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& orientation = glm::vec3(0),
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1));


	virtual void renderDepth() = 0;

	virtual void render() = 0;

protected:

	virtual void initRendering() = 0;

	std::vector<Object*> objectArray;


};







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




