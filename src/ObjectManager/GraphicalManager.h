#pragma once


#include "Graphics/GLProgram.h"
#include "World/DirLight.h"
#include "World/Camera.h"


class GraphicalManager
{
public:
	GraphicalManager(int width, int height);
	~GraphicalManager();


	void resize(int width, int height);


	Camera* getCamera();

	GLProgram* addProgram(const char* pathVertex, const char* pathFragment);


	void render();


	void clear();

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering();



private:

	int m_width;
	int m_height;


	GLuint m_globalUboBinding;
	GLuint m_globalUbo;

	std::vector<GLProgram*> m_programs;


	Camera m_camera;


	DirLight m_dirLight;

	Shader m_programDepth;
	GLint m_lightSpaceIndex;
	GLint m_modelIndex;


	GLuint m_depthFbo;
	GLuint m_depthMap;
};

