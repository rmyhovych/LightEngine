#pragma once


#include "GLProgram.h"


class GameManager
{
public:
	GameManager(int width, int height);
	~GameManager();

	GLProgram* addProgram(const char* pathVertex, const char* pathFragment);


	void render(glm::vec3& dirLight, glm::mat4& pv);

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

	Shader m_programDepth;

	GLuint m_depthFbo;
	GLuint m_depthMap;
};

