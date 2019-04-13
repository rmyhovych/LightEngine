#include "Engine.h"



Engine::Engine(int windowW, int windowH) :
	window(windowW, windowH),

	gameRenderer(windowW, windowH)
{
	initShapes();
}



void Engine::initShapes()
{
	ProgramRenderer* mainProgram = gameRenderer.addProgramRenderer("shaders/vertex.glsl", "shaders/fragment.glsl");

	ObjectHandlerVertex* objectHandler = mainProgram->addObjectHandler("data/prismBuffer");

	Object* cube = objectHandler->addObject();
}




void Engine::play()
{
	while (!window.isClosing())
	{

		window.swapBuffers();
	}
}

