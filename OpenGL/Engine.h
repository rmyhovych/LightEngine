#pragma once

#include "include/GameRenderer.h"

#include "Window.h"
#include <chrono>

struct fpsCounter
{
	float counter = 0;
	const float fCeil = 2000;

	std::chrono::time_point<std::chrono::system_clock> t;

	void inc()
	{
		if (counter == 0)
		{
			t = std::chrono::system_clock::now();
		}
		counter++;
		
		if (counter >= fCeil)
		{
			std::chrono::duration<float> duration = std::chrono::system_clock::now() - t;
			std::cout << fCeil / (duration.count()) << "\n";
			
			counter = 0;
		}
	}
};


class Engine
{
public:

	Engine(int windowW = 1200, int windowH = 800);


	void initShapes();

	void play();

private:

	fpsCounter fps;

	Object* cube;

	Window window;

	GameRenderer gameRenderer;
};

