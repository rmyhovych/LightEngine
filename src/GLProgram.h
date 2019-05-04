#pragma once


#include "PhantomManagerV.h"
#include "PhantomManagerE.h"
#include "BoxManager.h"
#include "SphereManager.h"


class GLProgram
{
public:
	GLProgram(const std::string& pathVertex, const std::string& pathFragment);

	~GLProgram();


	ObjectManagerAbs* addPhantomManager(const std::string& vertexPath);
	ObjectManagerAbs* addPhantomManager(const std::string& vertexPath, const std::string& elementPath);

	PhysicalManager* addBoxManager();
	PhysicalManager* addSphereManager();


	void bindUbo(const char* name, GLuint binding);


	void render(glm::vec3& dirLight, glm::mat4& pv);
	void renderDepth(GLint modelIndex);

private:
	
	void createUniforms();


private:

	Shader m_program;

	GlobalUniforms m_globalUniforms;
	ObjectUniforms m_objectUniforms;


	std::vector<ObjectManagerAbs*> m_objectManagers;
};

