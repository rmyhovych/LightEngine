#include "Engine.h"



Engine::Engine(int windowW, int windowH) :
	window(windowW, windowH),

	gameRenderer(windowW, windowH)
{
	initShapes();
}



void Engine::initShapes()
{
	ProgramRenderer* program = gameRenderer.addProgramRenderer("shaders/vertex.glsl", "shaders/fragment.glsl");

	ObjectHandlerVertex* objectHandler0 = program->addObjectHandler("data/prismBuffer");
	ObjectHandlerElement* objectHandler1 = program->addObjectHandler("data/sphereBuffer", "data/sphereElements");

	objectHandler0->addObject();

	objectHandler1->addObject(glm::vec3(3, 1, 2.5));
}




void Engine::play()
{
	Camera* camera = window.createCamera(10, 0, 1.3);

	glm::vec3 dirLight = glm::vec3(0.5, 0.8, 0.2);

	while (!window.isClosing())
	{
		fps.inc();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->rotate(0.001, 0);
		gameRenderer.render(dirLight, camera->getVP());
		window.swapBuffers();
	}
}

