#include "sphere.h"

//=============================================================================================
//  STATIC
//=============================================================================================

void Sphere::init()
{
	Shader::addVertexBuffer("data/sphereBuffer");
	Shader::addElementBuffer("data/sphereElements");

	vao = Shader::vao;
	ebo = Shader::ebo;
	eboSize = Shader::elementDataSize;



	glBindVertexArray(vao);

	Shader::linkLayout(0, 3, 3, 0);
	Shader::linkLayout(1, 3, 3, 0);
}



void Sphere::useVao()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}





//=============================================================================================
//  OBJECT
//=============================================================================================


Sphere::Sphere() :
	Object()
{
}



Sphere::Sphere(float radius, glm::vec3 position, float color) :
	Object(glm::vec3(radius), position, 0, color)
{
}



void Sphere::drawShadow()
{
	Object::drawShadow();

	Shader::render(eboSize, true);
}



void Sphere::draw()
{
	Object::draw();

	Shader::render(eboSize, true);
}
