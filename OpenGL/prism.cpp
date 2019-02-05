#include "prism.h"


//=============================================================================================
//  STATIC
//=============================================================================================



void Prism::init()
{
	Shader::addVertexArray();


	Shader::addVertexBuffer("data/prismBuffer");

	vao = Shader::vao;
	vboSize = Shader::vertexDataSize / (4 * 6);



	glBindVertexArray(vao);

	Shader::linkLayout(0, 3, 6, 0);
	Shader::linkLayout(1, 3, 6, 3);

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
	Object::drawShadow();

	Shader::render(vboSize, false);
}

void Prism::draw()
{
	Object::draw();

	Shader::render(vboSize, false);
}
