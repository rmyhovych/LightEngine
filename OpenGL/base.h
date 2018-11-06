#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

bool input[1024];

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* windowInit(int width, int height, const char* name);

void windowInput(GLFWwindow* window);