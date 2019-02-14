#pragma once

#include "drawables.h"
#include "dirLight.h"
#include "camera.h"


class Engine
{
public:

	static Camera* camera;
	static DirLight* dirLight;

	Engine();
	~Engine();


	void initShapes();


	void step();


	void createSphere(float radius, glm::vec3 position, float color);

	void createPrism(glm::vec3 scale, glm::vec3 position, float angle, float color);


private:

	Drawables drawables;

	Window window;

	double time = 0;

	
};

