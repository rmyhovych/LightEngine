#pragma once


#include "ObjectHandler.h"

#include "window.h"




struct CommonData
{

};



class Renderer
{
public:
	Renderer();
	~Renderer();

	ObjectHandler* addObjectHandler(const char* vPathRender, const char* fPathRender);


	void draw();

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering();




	std::vector<ObjectHandler*> objectHandlers;

	GLShader programDepth;

	GLuint depthFbo;
	GLuint depthMap;


	static int depthMapSize;


};

