#pragma once

#include "shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



class Object
{


	//=============================================================================================
	//  STATIC
	//=============================================================================================


public:

	static void compilePrograms();



	static void initRenderingShadow();

	static void initRendering();



	


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


	static void addFramebuffer();

	static void createUniforms();




	static Shader program;
	static Shader programShadow;

	static GLuint fbo;
	static GLuint depthMap;

	static const int depthMapSize = 1024;








	//=============================================================================================
	//  OBJECT
	//=============================================================================================

public:

	Object();

	Object(glm::vec3 scale, glm::vec3 position, float angle, float color);



	void setPosition(glm::vec3 v);

	void setPosition(float x, float y, float z);



	void setAngle(float angle, glm::vec3 v);

	void setAngle(float angle, float x, float y, float z);



	void setScale(glm::vec3 v);

	void setScale(float x, float y, float z);

	void setScale(float v);



	void drawShadow();

	void draw();





protected:

	glm::vec3 position;

	float color;




private:

	void model();



	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 translationMatrix;

	glm::mat4 modelMatrix;


	glm::vec3 scale;

	float angle;
};













struct LightHandle
{
	GLuint posHandle;
	GLuint intensityHandle;
};