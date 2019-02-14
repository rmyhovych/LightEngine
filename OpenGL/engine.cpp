#include "engine.h"



Engine::Engine() :
	window(),

	camera(&time, Window::width, Window::height, window.keyInput),
	
	dirLight(2, 3, camera.focus, camera.zoom)
{
	initShapes();
}



void Engine::initShapes()
{
	float depth = 0.6f;

	float boxWidth = 10;
	float boxHeight = 16;

	float boxThickness = 0.1f;

	float miniObsLen = 2;


	createPrism(glm::vec3(boxWidth, boxHeight, 0.2f), glm::vec3(0, 0, -depth - 0.2f), 0, 0.2f);


	createPrism(glm::vec3(boxThickness, boxWidth, depth), glm::vec3(0, boxHeight, 0), 90, 0.6f);
	createPrism(glm::vec3(boxThickness, boxWidth, depth), glm::vec3(0, -boxHeight, 0), 90, 0.6f);
	createPrism(glm::vec3(boxThickness, boxHeight, depth), glm::vec3(boxWidth, 0, 0), 0, 0.6f);
	createPrism(glm::vec3(boxThickness, boxHeight, depth), glm::vec3(-boxWidth, 0, 0), 0, 0.6f);
	createPrism(glm::vec3(boxThickness, miniObsLen, depth), glm::vec3(0, 1, 0), 90, 0.6f);
	createPrism(glm::vec3(boxThickness, miniObsLen, depth), glm::vec3(0, -1, 0), 90, 0.6f);
	createPrism(glm::vec3(boxThickness, miniObsLen, depth), glm::vec3(-3.31f, -0.35f, 0), 135, 0.6f);
	createPrism(glm::vec3(boxThickness, miniObsLen, depth), glm::vec3(3.31f, 0.35f, 0), 135, 0.6f);


	createSphere(0.5f, glm::vec3(0, 0, -(depth - 0.5f)), 1.0f);
}

void Engine::step()
{
	dirLight.update();
	camera.update();


	drawables.draw();
}

void Engine::createSphere(float radius, glm::vec3 position, float color)
{
	drawables.add(new Sphere(radius, position, color));
}

void Engine::createPrism(glm::vec3 scale, glm::vec3 position, float angle, float color)
{
	drawables.add(new Prism(scale, position, angle, color));

}
