#include "drawables.h"



Drawables::Drawables() :
	colorFramebuffer(0)
{
	Object::compilePrograms();

	Prism::init();
	Sphere::init();
}

void Drawables::add(Prism* prism)
{
	prismList.push_back(prism);
}

void Drawables::add(Sphere* sphere)
{
	sphereList.push_back(sphere);
}

void Drawables::draw()
{
	Object::initRenderingShadow();

	sendUniformsShadow();

	Prism::useVao();
	for (int i = 0; i < prismList.size(); i++)
	{
		prismList[i]->drawShadow();
	}

	Sphere::useVao();
	for (int i = 0; i < sphereList.size(); i++)
	{
		sphereList[i]->drawShadow();
	}



	Object::initRendering();

	colorFramebuffer.renderOn();

	sendUniforms();

	Prism::useVao();
	for (int i = 0; i < prismList.size(); i++)
	{
		prismList[i]->draw();
	}

	Sphere::useVao();
	for (int i = 0; i < sphereList.size(); i++)
	{
		sphereList[i]->draw();
	}



	colorFramebuffer.draw();

}

void Drawables::sendUniformsShadow()
{
}

void Drawables::sendUniforms()
{
}
