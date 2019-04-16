#pragma once

#include "GameRenderer.h"

#include "window.h"


class Engine
{
public:

	Engine(int windowW = 1200, int windowH = 800);


	void initShapes();

	void play();

private:

	ProgramRenderer* program;
	Object* cube;

	Window window;

	GameRenderer gameRenderer;

	double time = 0;
};

