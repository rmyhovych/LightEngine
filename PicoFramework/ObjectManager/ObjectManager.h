#pragma once
#include "ObjectManager/Object/Object.h"

class ObjectManager
{
public:
	ObjectManager();
	virtual ~ObjectManager() = 0;

	virtual void render(ObjectUniforms& uniforms) = 0;
	virtual void renderDepth(GLint modelIndex) = 0;

	virtual Object* createObject(
		btScalar mass = 1.0,
		btScalar restitution = 0.5,
		btScalar friction = 0.5,
		const glm::vec3& position = glm::vec3(0),
		const glm::vec3& color = glm::vec3(1),
		const glm::vec3& scale = glm::vec3(1)) = 0;

protected:

	virtual ObjectRenderer* createGraphicalObject(
		const glm::vec3& scale = glm::vec3(1),
		const glm::vec3& color = glm::vec3(1));

	void initVertexData(const std::string& vertexPath);
	void initElementData(const std::string& vertexPath, const std::string& elementPath);

	std::vector<ObjectRenderer*> m_objects;

	GLuint m_vao;
	GLuint m_ebo;

	GLuint m_glDataSize;
};

