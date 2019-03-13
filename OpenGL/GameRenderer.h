#pragma once


#include "ObjectHandler.h"

#include "window.h"




struct CommonData
{

};



class GameRenderer
{
public:
	GameRenderer();
	~GameRenderer();

	ObjectHandler* addObjectHandler(const char* vPathRender, const char* fPathRender);


	void draw();

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering();




	std::vector<ObjectHandler*> objectHandlers;

	Shader programDepth;

	GLuint depthFbo;
	GLuint depthMap;


	static int depthMapSize;


};

