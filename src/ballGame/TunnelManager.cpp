#include "TunnelManager.h"
#include <cmath>

#define PI 3.14159265359

TunnelManager::TunnelManager(int nSides, btScalar length, btScalar width) :
	m_nBoxes(nSides / 2)
{
	initVertexData("binary/tunnel" + std::to_string(nSides));

	m_rotAngle = btScalar(2.0 * PI) / btScalar(nSides);

	btScalar x = width * btScalar(sin(m_rotAngle / 2));
	btScalar y = width * btScalar(cos(m_rotAngle / 2));
	btScalar z = length;

	m_boxSize.setValue(x, y, z);
}


TunnelManager::~TunnelManager()
{
}

void TunnelManager::render(ObjectUniforms& uniforms)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->use(uniforms);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

void TunnelManager::renderDepth(GLint modelIndex)
{
	glBindVertexArray(m_vao);

	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		m_objects[i]->useDepth(modelIndex);
		glDrawArrays(GL_TRIANGLES, 0, m_glDataSize);
	}
}

Object* TunnelManager::createObject(
	btScalar mass,
	btScalar restitution,
	btScalar friction,
	const glm::vec3& position,
	const glm::vec3& color,
	const glm::vec3& scale)
{
	GraphicalObject* parent = createGraphicalObject(color, scale);

	btCompoundShape* compoundShape = new btCompoundShape();
	

	btBoxShape* boxShape = new btBoxShape(m_boxSize);
	
	
	for (int i = 0; i < m_nBoxes; i++)
	{
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin({position.x, position.y, position.z});
		transform.setRotation(btQuaternion({ 0, 0, 1 }, (m_rotAngle / 2.0) + m_rotAngle * i));

		compoundShape->addChildShape(transform, boxShape);
	}

	Object* obj = new Object(parent, { compoundShape, mass, restitution, friction});

	obj->setPosition(btVector3(position.x, position.y, position.z));
	
	return obj;
}