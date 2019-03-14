#pragma once


#include "ProgramRenderer.h"

#include "window.h"



class GameRenderer
{
public:
	GameRenderer();
	~GameRenderer();

	ProgramRenderer* addProgramRenderer(const char* vPathRender, const char* fPathRender);


	void draw();

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering();




	std::vector<ProgramRenderer*> programRendererArray;

	Shader programDepth;

	GLuint depthFbo;
	GLuint depthMap;


	static int depthMapSize;


};

