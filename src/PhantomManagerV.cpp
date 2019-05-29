#include "PhantomManagerV.h"
#include "PhysicalWorld.h"


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
	const glm::vec3& orientation, 
	const glm::vec3& scale, 
	const glm::vec3& color)
{
	GraphicalObject* parent = createGraphicalObject(position, orientation, scale, color);

	btEmptyShape* emptyShape = new btEmptyShape();

	Object* obj = PhysicalWorld::getInstance()->createObject(parent, emptyShape);

	obj->setPosition({ position.x, position.y, position.z });
	obj->setRotation({ orientation.x, orientation.y, orientation.z });

	return obj;
}
