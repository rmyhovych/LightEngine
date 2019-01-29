#pragma once

#include "shader.h"


class Object
{
public:
	Object();
	~Object();



protected:

	static int rotationHandle;
	static int modelHandle;

	//      color
	static int colorHandle;





	//  global
	//      matrices
	static int viewHandle;
	static int projectionHandle;
	static int lightSpaceHandle;


	//      lights
	static int sizeHandle;
	static std::vector<LightHandle> lightHandles;
	static int dirLightHandle;



	//  shadow
	static int modelHandleShadow;
	static int lightSpaceHandleShadow;



private:

	static Shader program;
	static Shader programShadow;

	static GLuint fbo;
	static GLuint depthMap;

	static const int depthMapSize = 1024;
};




struct LightHandle
{
	GLuint posHandle;
	GLuint intensityHandle;
};