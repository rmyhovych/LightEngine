#pragma once

#include <vector>

#include "Object.h"


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


	virtual void render(ObjectUniforms& uniforms) = 0;

protected:

	std::vector<Object*> objectArray;


	GLuint vao;
};







class ObjectHandlerVertex :
	public ObjectHandler
{
public:
	ObjectHandlerVertex(const char* vertexPath);
	~ObjectHandlerVertex();


	virtual void render(ObjectUniforms& uniforms);


private:


	unsigned nVertices;

};








class ObjectHandlerElement :
	public ObjectHandler
{
public:
	ObjectHandlerElement(const char* vertexPath, const char* elementPath);
	~ObjectHandlerElement();


	virtual void render(ObjectUniforms& uniforms);


private:

	unsigned nElements;

};




