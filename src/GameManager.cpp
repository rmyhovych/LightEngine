#include "GameManager.h"


static int depthMapSize = 1024;


GameManager::GameManager(int width, int height) :
	m_width(width),
	m_height(height),

	m_globalUboBinding(1),

	m_programDepth("shaders/vertex_shadow.glsl", "shaders/fragment_shadow.glsl")
{
	createDepthMap();

	createUniforms();
}

GameManager::~GameManager()
{
	for (int i = m_programs.size() - 1; i >= 0; i--)
	{
		delete m_programs[i];
		m_programs[i] = nullptr;
	}
}



GLProgram* GameManager::addProgram(const char* pathVertex, const char* pathFragment)
{
	GLProgram* program = new GLProgram(pathVertex, pathFragment);

	program->bindUbo("GlobalData", m_globalUboBinding);

	m_programs.push_back(program);

	return program;
}


void GameManager::render(glm::vec3& dirLight, glm::mat4& pv)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUbo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, (void*)&dirLight);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 64, (void*)&pv);

	for (int i = m_programs.size() - 1; i >= 0; i--)
	{
		m_programs[i]->render(dirLight, pv);
	}
}


void GameManager::createDepthMap()
{
	//  DEPTH MAP TEXTURE

		//      create depthMap
	glGenTextures(1, &m_depthMap);


	//      use depthMap
	glBindTexture(GL_TEXTURE_2D, m_depthMap);

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
	glGenFramebuffers(1, &m_depthFbo);


	//      use fbo
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);


	//      no draw buffers
	//glDrawBuffer(GL_NONE);


	//      bind data to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,	GL_TEXTURE_2D, m_depthMap, 0);



	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.5f, 150.0f);
}



void GameManager::createUniforms()
{
	glGenBuffers(1, &m_globalUbo);

	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUbo);
	glBufferData(GL_UNIFORM_BUFFER, 5 * 4 * sizeof(float), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, m_globalUboBinding, m_globalUbo, 0, 5 * 4 * sizeof(float));
}








void GameManager::initRenderingDepth()
{
	glViewport(0, 0, depthMapSize, depthMapSize);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);

	glColorMask(false, false, false, false);
	glClear(GL_DEPTH_BUFFER_BIT);


	//programDepth.use();



	// TODO : set uniforms

}



void GameManager::initRendering()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_width, m_height);

	glColorMask(true, true, true, true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, m_depthMap);


	// TODO : set ubo
}
