#include "ObjectManagerAbs.h"
#include "FileReaderHandler.h"


ObjectManagerAbs::ObjectManagerAbs() :
	m_objects(0),

	m_vao(0),
	m_ebo(0),

	m_glDataSize(0)
{
}


ObjectManagerAbs::~ObjectManagerAbs()
{
	for (int i = m_objects.size() - 1; i >= 0; i--)
	{
		delete m_objects[i];
		m_objects[i] = nullptr;
	}
}



GraphicalObject* ObjectManagerAbs::createGraphicalObject(
	const glm::vec3& position, 
	const glm::vec3& orientation, 
	const glm::vec3& scale, 
	const glm::vec3& color)
{
	GraphicalObject* o = new GraphicalObject(color, scale);

	o->setMovement(position, orientation);

	m_objects.push_back(o);

	return o;
}





void ObjectManagerAbs::initVertexData(const std::string& vertexPath)
{
	FileReaderAbs* fr = FileReaderHandler::getFileReader();
	FileData vertexData = fr->read(vertexPath);

	m_glDataSize = vertexData.size() / (sizeof(float) * 6); // 6 -> vertex size


	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	Shader::addVertexBuffer(vertexData);

	Shader::linkLayout(0, 3, 6, 0);
	Shader::linkLayout(1, 3, 6, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ObjectManagerAbs::initElementData(const std::string& vertexPath, const std::string& elementPath)
{
	FileReaderAbs* fr = FileReaderHandler::getFileReader();
	FileData vertexData = fr->read(vertexPath);
	FileData elementData = fr->read(elementPath);

	m_glDataSize = elementData.size() / sizeof(GLuint);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	Shader::addVertexBuffer(vertexData);
	m_ebo = Shader::addElementBuffer(elementData);


	Shader::linkLayout(0, 3, 3, 0);
	Shader::linkLayout(1, 3, 3, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
