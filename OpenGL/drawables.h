#pragma once

#include "sphere.h"
#include "prism.h"

#include "framebuffer.h"


class Drawables
{
public:
	Drawables();

	void add(Prism* prism);
	void add(Sphere* sphere);

	void draw();


private:

	void sendUniformsShadow();
	void sendUniforms();


	std::vector<Prism*> prismList;
	std::vector<Sphere*> sphereList;
	
	Framebuffer colorFramebuffer;

};

