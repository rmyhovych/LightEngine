#pragma once


#include "GLProgram.h"
#include "DirLight.h"
#include "Camera.h"


class GameManager
{
public:
	GameManager(int width, int height);
	~GameManager();


	void resize(int width, int height);


	Camera* getCamera();

	GLProgram* addProgram(const char* pathVertex, const char* pathFragment);


	void render(glm::mat4& pv);

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering(glm::mat4& pv);



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

