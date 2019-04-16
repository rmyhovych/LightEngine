#pragma once


#include "ObjectHandler.h"



class ProgramRenderer
{
public:
	ProgramRenderer(const char* pathVertex, const char* pathFragment);

	~ProgramRenderer();


	ObjectHandlerVertex* addObjectHandler(const char* arrayPath);
	ObjectHandlerElement* addObjectHandler(const char* arrayPath, const char* elementPath);



	void render(glm::vec3& dirLight, glm::mat4& vp);

private:

	void createUniforms();



	Shader program;

	GlobalUniforms globalUniforms;
	ObjectUniforms objectUniforms;


	std::vector<ObjectHandler*> objectHandlerArray;

};

