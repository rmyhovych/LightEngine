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

GraphicalObject* PhantomManagerV::createObject(
	const glm::vec3& position, 
	const glm::vec3& orientation, 
	const glm::vec3& scale, 
	const glm::vec3& color)
{
	return createGraphicalObject(position, orientation, scale, color);
}
