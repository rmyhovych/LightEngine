#include "BoxManager.h"
#include "PhysicalWorld.h"


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

PhysicalObject* BoxManager::createObject(
	btScalar mass, 
	btScalar restitution, 
	btScalar friction,
	const glm::vec3& position, 
	const glm::vec3& orientation, 
	const glm::vec3& scale,
	const glm::vec3& color)
{
	GraphicalObject* parent = createGraphicalObject(position, orientation, scale, color);

	btBoxShape* boxShape = new btBoxShape({scale.x, scale.y, scale.z});

	PhysicalObject* obj = PhysicalWorld::getInstance()->createObject(parent, PhysicalObject::Properties(boxShape, mass, restitution, friction));

	obj->setPosition({ position.x, position.y, position.z });
	obj->setRotation({ orientation.x, orientation.y, orientation.z });

	return obj;
}
