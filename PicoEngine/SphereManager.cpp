#include "SphereManager.h"


SphereManager::SphereManager()
{
	initElementData("binary/sphereBuffer", "binary/sphereElements");
}


SphereManager::~SphereManager()
{
}

void SphereManager::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->use(uniforms);
		glDrawElements(GL_TRIANGLES, m_glDataSize, GL_UNSIGNED_INT, 0);
	}
}

void SphereManager::renderDepth(GLint modelIndex)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->useDepth(modelIndex);
		glDrawElements(GL_TRIANGLES, m_glDataSize, GL_UNSIGNED_INT, 0);
	}
}

Object* SphereManager::createObject(
	btScalar mass,
	btScalar restitution,
	btScalar friction,
	const glm::vec3& position,
	const glm::vec3& color,
	const glm::vec3& scale)
{
	GraphicalObject* parent = createGraphicalObject(color, scale);

	btSphereShape* sphereShape = new btSphereShape(scale.x);

	Object* obj = new Object(parent, Object::Properties(sphereShape, mass, restitution, friction));

	obj->setPosition(btVector3(position.x, position.y, position.z));

	return obj;
}
