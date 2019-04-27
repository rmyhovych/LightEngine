#pragma once


#include "ObjectHandler.h"



class ProgramRenderer
{
public:
	ProgramRenderer(const char* pathVertex, const char* pathFragment);
	ProgramRenderer(FileData& vertexData, FileData& fragmentData);

	~ProgramRenderer();


	ObjectHandler* addObjectHandler(const char* arrayPath);
	ObjectHandler* addObjectHandler(FileData& arrayData);

	ObjectHandler* addObjectHandler(const char* arrayPath, const char* elementPath);
	ObjectHandler* addObjectHandler(FileData& arrayData, FileData& elementData);


	void render(glm::vec3& dirLight, glm::mat4& pv);

private:

	void createUniforms();



	Shader program;

	GlobalUniforms globalUniforms;
	ObjectUniforms objectUniforms;


	std::vector<ObjectHandler*> objectHandlerArray;

};

