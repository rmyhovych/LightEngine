#include "SphereManager.h"
#include "PhysicalWorld.h"


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

PhysicalObject* SphereManager::createObject(
	btScalar mass, 
	btScalar restitution, 
	btScalar friction,
	const glm::vec3& position, 
	const glm::vec3& orientation,
	const glm::vec3& scale,
	const glm::vec3& color)
{
	GraphicalObject* parent = createGraphicalObject(position, orientation, scale, color);

	btSphereShape* sphereShape = new btSphereShape(scale.x);

	PhysicalObject* obj = PhysicalWorld::getInstance()->createObject(parent, PhysicalObject::Properties(sphereShape, mass, restitution, friction));

	obj->setPosition({position.x, position.y, position.z});
	obj->setRotation({orientation.x, orientation.y, orientation.z});

	return obj;
}
