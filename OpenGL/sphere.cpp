#include "sphere.h"

//=============================================================================================
//  STATIC
//=============================================================================================

void Sphere::init()
{
	glShader::addVertexBuffer("data/sphereBuffer");
	glShader::addElementBuffer("data/sphereElements");

	vao = glShader::vao;
	ebo = glShader::ebo;
	eboSize = glShader::elementDataSize;



	glBindVertexArray(vao);

	glShader::linkLayout(0, 3, 3, 0);
	glShader::linkLayout(1, 3, 3, 0);
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
	Object::useDepth();

	glShader::render(eboSize, true);
}



void Sphere::draw()
{
	Object::use();

	glShader::render(eboSize, true);
}
