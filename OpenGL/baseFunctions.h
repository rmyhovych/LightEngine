#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* windowInit(int width, int height, const char* name);

void windowInput(GLFWwindow* window);