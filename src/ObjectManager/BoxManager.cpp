#include "BoxManager.h"

BoxManager::BoxManager()
{
	initVertexData("binary/prismBuffer");
}


BoxManager::~BoxManager()
{
}

void BoxManager::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->use(uniforms);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

void BoxManager::renderDepth(GLint modelIndex)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->useDepth(modelIndex);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

Object* BoxManager::createObject(
	btScalar mass,
	btScalar restitution,
	btScalar friction,
	const glm::vec3& position,
	const glm::vec3& color,
	const glm::vec3& scale)
{
	GraphicalObject* parent = createGraphicalObject(color, scale);

	btBoxShape* boxShape = new btBoxShape({scale.x, scale.y, scale.z});

	Object* obj = new Object(parent, Object::Properties(boxShape, mass, restitution, friction));

	obj->setPosition(btVector3(position.x, position.y, position.z));

	return obj;
}
