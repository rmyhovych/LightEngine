#include "ProgramRenderer.h"



ProgramRenderer::ProgramRenderer(const char* pathVertex, const char* pathFragment) :
	program(pathVertex, pathFragment)
{
	createUniforms();
}

ProgramRenderer::~ProgramRenderer()
{
	for (int i = 0; i < objectHandlerArray.size(); i++)
	{
		delete objectHandlerArray[i];
		objectHandlerArray[i] = nullptr;
	}
}





ObjectHandlerVertex* ProgramRenderer::addObjectHandler(const char* arrayPath)
{
	ObjectHandlerVertex* oHandler = new ObjectHandlerVertex(arrayPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}


ObjectHandlerElement* ProgramRenderer::addObjectHandler(const char* arrayPath, const char* elementPath)
{
	ObjectHandlerElement* oHandler = new ObjectHandlerElement(arrayPath, elementPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}




void ProgramRenderer::render(glm::vec3& dirLight, glm::mat4& pv)
{
	program.use();

	glUniform3f(globalUniforms.vDirLight, dirLight.x, dirLight.y, dirLight.z);
	glUniformMatrix4fv(globalUniforms.mVP, 1, false, glm::value_ptr(pv));

	for (int i = 0; i < objectHandlerArray.size(); i++)
	{
		objectHandlerArray[i]->render(objectUniforms);
	}
}





void ProgramRenderer::createUniforms()
{
	program.use();

	globalUniforms = {
		program.getUniformLocation("vDirLight"),
		program.getUniformLocation("mVP")
	};


	objectUniforms = {
		program.getUniformLocation("mRotation"),
		program.getUniformLocation("mModel"),
		program.getUniformLocation("vColor")
	};
}
