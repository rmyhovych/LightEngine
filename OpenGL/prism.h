#pragma once

#include "object.h"



class Prism : private Object
{

	//=============================================================================================
	//  STATIC
	//=============================================================================================



public:

	static void init();


	static void useVao();



private:

	static int vao;

	static int vboSize;



	//=============================================================================================
	//  OBJECT
	//=============================================================================================


public:

	Prism();

	Prism(glm::vec3 scale, glm::vec3 position, float angle, float color);



	void drawShadow();

	void draw();

};

