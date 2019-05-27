#include "PhantomManagerE.h"
#include "PhysicalWorld.h"


PhantomManagerE::PhantomManagerE(const std::string& vertexPath, const std::string& elementPath)
{
	initElementData(vertexPath, elementPath);
}


PhantomManagerE::~PhantomManagerE()
{
}

void PhantomManagerE::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->use(uniforms);
		glDrawElements(GL_TRIANGLES, m_glDataSize, GL_UNSIGNED_INT, 0);
	}
}

void PhantomManagerE::renderDepth(GLint modelIndex)
{
}

Object* PhantomManagerE::createObject(
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

	Object* obj = PhysicalWorld::getInstance()->createObject(parent, Object::Properties(emptyShape, 0, 0, 0));

	obj->setPosition({ position.x, position.y, position.z });
	obj->setRotation({ orientation.x, orientation.y, orientation.z });

	return obj;
}
