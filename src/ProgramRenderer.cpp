#include "ProgramRenderer.h"



ProgramRenderer::ProgramRenderer(const char* pathVertex, const char* pathFragment) :
	program(pathVertex, pathFragment)
{
	createUniforms();
}

ProgramRenderer::ProgramRenderer(FileData& vertexData, FileData& fragmentData) :
	program(vertexData, fragmentData)
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





ObjectHandler* ProgramRenderer::addObjectHandler(const char* arrayPath)
{
	ObjectHandler* oHandler = new ObjectHandlerVertex(arrayPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}

ObjectHandler* ProgramRenderer::addObjectHandler(FileData& arrayData)
{
	ObjectHandler* oHandler = new ObjectHandlerVertex(arrayData);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}


ObjectHandler* ProgramRenderer::addObjectHandler(const char* arrayPath, const char* elementPath)
{
	ObjectHandler* oHandler = new ObjectHandlerElement(arrayPath, elementPath);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}

ObjectHandler* ProgramRenderer::addObjectHandler(FileData& arrayData, FileData& elementData)
{
	ObjectHandler* oHandler = new ObjectHandlerElement(arrayData, elementData);

	objectHandlerArray.push_back(oHandler);

	return oHandler;
}





void ProgramRenderer::render(glm::vec3& dirLight, glm::mat4& pv)
{
	program.use();

	glUniform3fv(globalUniforms.vDirLight, 1, (GLfloat*)&dirLight);
	glUniformMatrix4fv(globalUniforms.mVP, 1, false, (GLfloat*)&pv);

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
