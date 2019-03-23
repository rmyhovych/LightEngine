#pragma once

#include "GameRenderer.h"

#include "window.h"


class Engine
{
public:

	Engine();


	void initShapes();

	GLFWwindow* getWindow();

	void step();


	void createSphere(float radius, glm::vec3 position, float color);

	void createPrism(glm::vec3 scale, glm::vec3 position, float angle, float color);


private:

	GameRenderer gameRenderer;

	Window window;

	double time = 0;

	
};

