#include "GameRenderer.h"


int GameRenderer::depthMapSize = 1024;


GameRenderer::GameRenderer(int windowW, int windowH) :
	windowW(windowW),
	windowH(windowH)
	//programDepth("shaders/vertex_shadow.glsl", "shaders/fragment_shadow.glsl")
{
	//createDepthMap();

	createUniforms();
}

GameRenderer::~GameRenderer()
{
	for (int i = 0; i < programRendererArray.size(); i++)
	{
		delete programRendererArray[i];
		programRendererArray[i] = nullptr;
	}
}



ProgramRenderer* GameRenderer::addProgramRenderer(const char* pathVertex, const char* pathFragment)
{
	ProgramRenderer* objectHandler = new ProgramRenderer(pathVertex, pathFragment);

	programRendererArray.push_back(objectHandler);

	return objectHandler;
}

ProgramRenderer* GameRenderer::addProgramRenderer(FileData& vertexData, FileData& fragmentData)
{
	ProgramRenderer* objectHandler = new ProgramRenderer(vertexData, fragmentData);

	programRendererArray.push_back(objectHandler);

	return objectHandler;
}





void GameRenderer::render(glm::vec3& dirLight, glm::mat4& pv)
{
	for (int i = 0; i < programRendererArray.size(); i++)
	{
		programRendererArray[i]->render(dirLight, pv);
	}
}


void GameRenderer::createDepthMap()
{
	//  DEPTH MAP TEXTURE

		//      create depthMap
	glGenTextures(1, &depthMap);


	//      use depthMap
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, depthMapSize, depthMapSize, 0,	GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);



	//  FRAMEBUFFER OBJECT

	//      create fbo
	glGenFramebuffers(1, &depthFbo);


	//      use fbo
	glBindFramebuffer(GL_FRAMEBUFFER, depthFbo);


	//      no draw buffers
	//glDrawBuffer(GL_NONE);


	//      bind data to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,	GL_TEXTURE_2D, depthMap, 0);



	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.5f, 150.0f);
}



void GameRenderer::createUniforms()
{
	// TODO : create uniforms
}








void GameRenderer::initRenderingDepth()
{
	glViewport(0, 0, depthMapSize, depthMapSize);
	glBindFramebuffer(GL_FRAMEBUFFER, depthFbo);

	glColorMask(false, false, false, false);
	glClear(GL_DEPTH_BUFFER_BIT);


	//programDepth.use();



	// TODO : set uniforms

}



void GameRenderer::initRendering()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, windowW, windowH);

	glColorMask(true, true, true, true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, depthMap);


	// TODO : set ubo
}
