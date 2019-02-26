#define STB_IMAGE_IMPLEMENTATION

#include <iomanip>

#include "engine.h"

int width = 1200;
int height = 800;


int main()
{

	//	Create window
	double time;


	


	Engine engine;
	GLFWwindow* window = engine.getWindow();


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
}
