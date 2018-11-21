#define STB_IMAGE_IMPLEMENTATION

#include <iomanip>

#include "camera.h"
#include "shader.h"
#include "window_gl.h"
#include "sphereList.h"

int width = 1200;
int height = 800;

bool pressed = false;
double scroll = 0;
glm::vec2 cursor;
float inputForce = 0.005;
void mouseInput(WindowGL& window, Camera& camera);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scroll = yoffset;
}

int main()
{
	//	Create window
	WindowGL window(width, height);
	double time;

	glfwSetScrollCallback(window.window_, scroll_callback);

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  0.0f,  -5.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -6.3f),
		glm::vec3(5.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(0.0f,  1.0f, -6.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-3.3f,  1.0f, -5.5f)
	};

	std::vector<glm::mat4> models;
	for (int i = 0; i < positions.size(); i++)
	{
		models.push_back(glm::translate(glm::mat4(1.0f), positions[i]));
		if (i >= positions.size() - 3)
		{
			models[i] = glm::scale(models[i], glm::vec3(0.2f));
		}
	}

	float vertices[] = {
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	// Left face
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	// Bottom face          
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	};

	//==================	LIGHT
	Shader lightCube("shaders/vertex.glsl", "shaders/fragmentLight.glsl");

	lightCube.addBufferObject(vertices, 36, 6);

	lightCube.addLayout(0, 3, 0);
	//==================

	std::vector<Light> lights;

	lights.push_back({
		glm::vec3(0.3f, 0.3f, 1.0f),
		positions[7],
		10.0f
		});

	lights.push_back({
		glm::vec3(1.0f, 0.3f, 0.3f),
		positions[8],
		10.0f
		});

	lights.push_back({
		glm::vec3(1.0f, 1.0f, 1.0f),
		positions[9],
		20.0f
		});

	//==================	COLOR CUBES
	Shader colorCube("shaders/vertex.glsl", "shaders/fragment.glsl");

	colorCube.addBufferObject(vertices, 36, 6);

	colorCube.addLayout(0, 3, 0);
	colorCube.addLayout(1, 3, 3);

	glm::vec3 cubeColor = glm::vec3(0.4f, 0.6f, 0.4f);
	//==================


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//	=== EVENT LOOP ===
	Camera camera(time, width, height, window.getInput(), 0.1);

	SphereList spheres = SphereList("shaders/vertex.glsl", "shaders/fragment.glsl", camera, lights);
	spheres.addSphere(glm::vec3(0, 0, -3), 1, glm::vec3(0.5));
	spheres.init();

	glfwSetTime(0);
	int k = 0;
	double fps = 0;
	while (!glfwWindowShouldClose(window.window_))
	{
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


		camera.adjust(window.window_);

		window.input();
		mouseInput(window, camera);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.refresh();
	
		spheres.draw();
		//spheres[0].move(glm::vec3(0, 0, -0.0001));
		spheres[0].rotate(glm::vec3(0, 1, 0), 0.001);

		colorCube.use();
		models[1] = glm::rotate(models[1], -0.001f, glm::normalize(glm::vec3(1, 1, 0)));
		for (int i = 0; i < models.size() - 3; i++)
		{
			//	- FRAGMENT -
			//	Lights
			colorCube.uniformInt("uSize", lights.size());
			for (int j = 0; j < lights.size(); j++)
			{
				colorCube.uniformVec3(("uLights[" + std::to_string(j) + "].color").c_str(), lights[j].color);
				colorCube.uniformVec3(("uLights[" + std::to_string(j) + "].pos").c_str(), lights[j].pos);
				colorCube.uniformFloat(("uLights[" + std::to_string(j) + "].intensity").c_str(), lights[j].intensity);
			}

			//	Object
			colorCube.uniformVec3("uColor", cubeColor);
			colorCube.uniformVec3("uViewPos", camera.getPosition());
			

			//	- VERTEX -
			glUniformMatrix3fv(glGetUniformLocation(colorCube.ID, "uRotation"), 1, GL_FALSE, glm::value_ptr(glm::mat3(models[i])));
			colorCube.uniformMat4Ptr("uModel", glm::value_ptr(models[i]));
			colorCube.uniformMat4Ptr("uView", glm::value_ptr(camera.getView()));
			colorCube.uniformMat4Ptr("uProjection", camera.getProjection());

			colorCube.draw();
		}

		lightCube.use();
		for (int i = models.size() - 3; i < models.size(); i++)
		{
			//	- FRAGMENT -
			lightCube.uniformVec3("uColor", lights[i - 7].color);

			//	- VERTEX -
			lightCube.uniformMat4Ptr("uModel", glm::value_ptr(models[i]));
			lightCube.uniformMat4Ptr("uView", glm::value_ptr(camera.getView()));
			lightCube.uniformMat4Ptr("uProjection", camera.getProjection());

			lightCube.draw();
		}


		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}

	return 0;
}

void mouseInput(WindowGL& window, Camera& camera)
{
	double x;
	double y;
	if (glfwGetMouseButton(window.window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !pressed)
	{
		pressed = true;
		glfwSetInputMode(window.window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwGetCursorPos(window.window_, &x, &y);
		glfwSetCursorPos(window.window_, x, y);

		cursor.x = x;
		cursor.y = y;
	}
	else if (glfwGetMouseButton(window.window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		pressed = false;
		glfwSetInputMode(window.window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (pressed)
	{		
		glfwGetCursorPos(window.window_, &x, &y);

		camera.rotateCamera(inputForce*(x - cursor.x), inputForce*(y - cursor.y));
		glfwSetCursorPos(window.window_, (double)cursor.x, (double)cursor.y);
	}

	if (scroll != 0)
	{

		if (scroll == 1)
		{
			camera.zoom_ /= 1.1;
		}
		else
		{
			camera.zoom_ *= 1.1;
		}

		scroll = 0;
	}
}