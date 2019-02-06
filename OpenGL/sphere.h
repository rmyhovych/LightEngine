#pragma once
#include "object.h"


class Sphere :
	public Object
{

	//=============================================================================================
	//  STATIC
	//=============================================================================================



public:
	static void init();

	static void useVao();


private:

	static int vao;
	static int ebo;

	static int eboSize;




	//=============================================================================================
	//  OBJECT
	//=============================================================================================


public:

	Sphere();

	Sphere(float radius, glm::vec3 position, float color);


	void drawShadow();

	void draw();

};

