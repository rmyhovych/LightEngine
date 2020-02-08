#include "GLProgram.h"



GLProgram::GLProgram(const std::string& pathVertex, const std::string& pathFragment) :
	m_program(pathVertex, pathFragment)
{
	createUniforms();
}


GLProgram::~GLProgram()
{
	for (int i = m_objectManagers.size() - 1; i >= 0; i--)
	{
		delete m_objectManagers[i];
		m_objectManagers[i] = nullptr;
	}
}






ObjectManager* GLProgram::addPhantomManager(const std::string& vertexPath)
{
	ObjectManager* om = new PhantomManagerV(vertexPath);

	m_objectManagers.push_back(om);

	return om;
}

ObjectManager* GLProgram::addPhantomManager(const std::string& vertexPath, const std::string& elementPath)
{
	ObjectManager* om = new PhantomManagerE(vertexPath, elementPath);

	m_objectManagers.push_back(om);

	return om;
}




ObjectManager* GLProgram::addBoxManager()
{
	ObjectManager* bm = new BoxManager();

	m_objectManagers.push_back(bm);

	return bm;
}

ObjectManager* GLProgram::addSphereManager()
{
	ObjectManager* sm = new SphereManager();

	m_objectManagers.push_back(sm);

	return sm;
}



void GLProgram::bindUbo(const char* name, GLuint binding)
{
	m_program.bindUbo(name, binding);
}





void GLProgram::render(glm::vec3& dirLight, glm::mat4& pv)
{
	m_program.use();
	//glUniform3f(m_globalUniforms.vDirLight, dirLight.x, dirLight.y, dirLight.z);
	//glUniformMatrix4fv(m_globalUniforms.mVP, 1, false, glm::value_ptr(pv));

	for (int i = m_objectManagers.size() - 1; i >= 0; i--)
	{
		m_objectManagers[i]->render(m_objectUniforms);
	}
}

void GLProgram::renderDepth(GLint modelIndex)
{
	for (int i = m_objectManagers.size() - 1; i >= 0; i--)
	{
		m_objectManagers[i]->renderDepth(modelIndex);
	}
}





void GLProgram::createUniforms()
{
	m_program.use();

	/*
	m_globalUniforms = {
		m_program.getUniformLocation("vDirLight"),
		m_program.getUniformLocation("mVP")
	};
	*/

	m_objectUniforms = {
		m_program.getUniformLocation("mRotation"),
		m_program.getUniformLocation("mModel"),
		m_program.getUniformLocation("vColor")
	};
}
