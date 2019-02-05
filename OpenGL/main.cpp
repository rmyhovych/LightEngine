#define STB_IMAGE_IMPLEMENTATION

#include <iomanip>

#include "camera.h"
#include "shader.h"
#include "gl_window.h"


int width = 1200;
int height = 800;


int main()
{

	//	Create window
	GLWindow window(width, height);
	double time;


	






	glfwSetTime(0);

	int k = 0;
	double fps = 0;

	while (!glfwWindowShouldClose(window.window_))
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


		
			
	
		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}

	return 0;
}
