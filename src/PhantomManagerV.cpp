#include "PhantomManagerV.h"


PhantomManagerV::PhantomManagerV(const std::string& vertexPath)
{
	initVertexData(vertexPath);
}

PhantomManagerV::~PhantomManagerV()
{
}

void PhantomManagerV::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->use(uniforms);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

void PhantomManagerV::renderDepth(GLint modelIndex)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->useDepth(modelIndex);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

Object* PhantomManagerV::createObject(
	btScalar mass,
	btScalar restitution,
	btScalar friction,
	const glm::vec3& position,
	const glm::vec3& color,
	const glm::vec3& scale)
{
	GraphicalObject* parent = createGraphicalObject(color, scale);

	btEmptyShape* emptyShape = new btEmptyShape();

	Object* obj = new Object(parent, emptyShape);

	obj->setPosition(btVector3(position.x, position.y, position.z));

	return obj;
}
