#include "prism.h"


//=============================================================================================
//  STATIC
//=============================================================================================



void Prism::init()
{
	glShader::genVertexArray();


	glShader::addVertexBuffer("data/prismBuffer");

	vao = glShader::vao;
	vboSize = glShader::vertexDataSize / (4 * 6);



	glBindVertexArray(vao);

	glShader::linkLayout(0, 3, 6, 0);
	glShader::linkLayout(1, 3, 6, 3);

	glBindVertexArray(0);
}


void Prism::useVao()
{
	glBindVertexArray(vao);
}





//=============================================================================================
//  OBJECT
//=============================================================================================


Prism::Prism() :
	Object()
{
}

Prism::Prism(glm::vec3 scale, glm::vec3 position, float angle, float color) :
	Object(scale, position, angle, color)
{
}




void Prism::drawShadow()
{
	Object::useDepth();

	glShader::render(vboSize, false);
}

void Prism::draw()
{
	Object::use();

	glShader::render(vboSize, false);
}
