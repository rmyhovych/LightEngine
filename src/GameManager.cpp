#include "GameManager.h"


static int depthMapSize = 2048;


GameManager::GameManager(int width, int height) :
	m_width(width),
	m_height(height),

	m_globalUboBinding(1),

	m_camera(m_width, m_height, 15),
	m_dirLight(PI / 3, 5 * PI / 6, { 16, -2, 0 }, 10),

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



void GameManager::resize(int width, int height)
{
	m_width = width;
	m_height = height;


	glDeleteTextures(1, &m_depthMap);
	glDeleteFramebuffers(1, &m_depthFbo);
	createDepthMap();


	m_camera.resize(width, height);
}



Camera* GameManager::getCamera()
{
	return &m_camera;
}


GLProgram* GameManager::addProgram(const char* pathVertex, const char* pathFragment)
{
	GLProgram* program = new GLProgram(pathVertex, pathFragment);

	program->bindUbo("GlobalData", m_globalUboBinding);

	m_programs.push_back(program);

	return program;
}


void GameManager::render(glm::mat4& pv)
{
	m_dirLight.setFocus(m_camera.getFocus());



	initRenderingDepth();

	for (int i = m_programs.size() - 1; i >= 0; i--)
	{
		m_programs[i]->renderDepth(m_modelIndex);
	}

	initRendering(pv);

	for (int i = m_programs.size() - 1; i >= 0; i--)
	{
		m_programs[i]->render(m_dirLight.getDirection(), pv);
	}
}




void GameManager::clear()
{
	for (int i = m_programs.size() - 1; i >= 0; i--)
	{
		delete m_programs[i];
		m_programs[i] = nullptr;
	}
}




void GameManager::createDepthMap()
{
	//  DEPTH MAP TEXTURE

		//      create depthMap
	glGenTextures(1, &m_depthMap);


	//      use depthMap
	glBindTexture(GL_TEXTURE_2D, m_depthMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, depthMapSize, depthMapSize, 0,	GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);



	//  FRAMEBUFFER OBJECT

	//      create fbo
	glGenFramebuffers(1, &m_depthFbo);


	//      use fbo
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);


	//      no draw buffers
	GLenum draws[1] = {GL_NONE};
	glDrawBuffers(1, draws);


	//      bind data to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void GameManager::createUniforms()
{
	glGenBuffers(1, &m_globalUbo);

	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUbo);
	glBufferData(GL_UNIFORM_BUFFER, 9 * 4 * sizeof(float), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, m_globalUboBinding, m_globalUbo, 0, 9 * 4 * sizeof(float));


	m_lightSpaceIndex = m_programDepth.getUniformLocation("mLightSpace");
	m_modelIndex = m_programDepth.getUniformLocation("mModel");
}








void GameManager::initRenderingDepth()
{
	glViewport(0, 0, depthMapSize, depthMapSize);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthFbo);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glClear(GL_DEPTH_BUFFER_BIT);


	m_programDepth.use();

	glUniformMatrix4fv(m_lightSpaceIndex, 1, GL_FALSE, glm::value_ptr(m_dirLight.getLightSpace()));
}



void GameManager::initRendering(glm::mat4& pv)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_width, m_height);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, m_depthMap);


	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUbo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, (void*)&m_dirLight.getDirection());
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 64, (void*)&pv);
	glBufferSubData(GL_UNIFORM_BUFFER, 80, 64, (void*)&m_dirLight.getLightSpace());
}
