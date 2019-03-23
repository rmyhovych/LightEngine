#include "Engine.h"



Engine::Engine() :
	window()	
{
	initShapes();
}



void Engine::initShapes()
{
	ProgramRenderer* mainProgram = gameRenderer.addProgramRenderer("shaders/vertex.glsl", "shaders/fragment.glsl");

	ObjectHandlerVertex* prismHandler = mainProgram->addObjectHandler("data/prismBuffer");

	
}

GLFWwindow* Engine::getWindow()
{
	return window.windowHandle;
}

void Engine::step()
{
	
}

void Engine::createSphere(float radius, glm::vec3 position, float color)
{
}

void Engine::createPrism(glm::vec3 scale, glm::vec3 position, float angle, float color)
{

}
