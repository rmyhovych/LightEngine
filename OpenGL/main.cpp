#define STB_IMAGE_IMPLEMENTATION

#include <iomanip>

#include "Engine.h"

#include "sphereGen/generator.h"

int main()
{
	generateSphere("data/");

	Engine engine;
	engine.play();

	/*
	glfwSetTime(0);

	int k = 0;
	double fps = 0;

	while (!glfwWindowShouldClose(window))
	{
		//	=======	FPS	========
		time = glfwGetTime();
		glfwSetTime(0);

		if (k == 500)
		{
			std::cout << fps/500 << " fps\n";
			fps = 0;
			k = 0;
		}
		fps += 1 / time;
		k++;
		//	=====================


		engine.step();
		
			
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
	*/
}
