#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

GLFWwindow* windowInit(int width, int height, const char* name);

char* loadShader(std::string filename);
