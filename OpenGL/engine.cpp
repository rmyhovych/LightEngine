#include "Engine.h"



Engine::Engine(int windowW, int windowH) :
	window(windowW, windowH),

	gameRenderer(windowW, windowH)
{
	initShapes();
}



void Engine::initShapes()
{
	program = gameRenderer.addProgramRenderer("shaders/vertex.glsl", "shaders/fragment.glsl");

	ObjectHandlerVertex* objectHandler = program->addObjectHandler("data/prismBuffer");

	cube = objectHandler->addObject();
}




void Engine::play()
{
	Camera* camera = window.createCamera(2);

	glm::vec3 dirLight = glm::vec3(0.5, 0.8, 0.2);

	while (!window.isClosing())
	{
		glClearColor(0.1, 0.5, 0.1, 0);

		program->render(dirLight, camera->getVP());
		window.swapBuffers();
	}
}

