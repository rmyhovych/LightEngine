#include "framebuffer.h"
#include <fstream>


//=============================================================================================
//  STATIC
//=============================================================================================


void Framebuffer::addFramebuffer(float whRatio)
{
	Framebuffer::width = resolution;
	Framebuffer::height = (int)((float)resolution / whRatio);



	//  create texture
	glGenTextures(1, &texture);

	//  use texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);





	//  create rbo
	GLuint rbo;
	glGenFramebuffers(1, &rbo);

	//  use rbo
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);





	//  create fbo
	glGenFramebuffers(1, &fbo);


	//  use fbo
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
}




//=============================================================================================
//  OBJECT
//=============================================================================================


Framebuffer::Framebuffer(int paletteNumber) :
	program("shaders/vertex_fbo.glsl", "shaders/fragment_fbo_pixel.glsl")
{
	glShader::genVertexArray();

	glShader::addVertexBuffer("data/fboBuffer");


	vao = glShader::vao;
	vboSize = glShader::vertexDataSize / (4 * 4);



	glBindVertexArray(vao);

	glShader::linkLayout(0, 2, 4, 0);
	glShader::linkLayout(1, 2, 4, 2);

	glBindVertexArray(0);





	std::ifstream file("data/palettes", std::ios::binary);

	int size;

	file.read((char*)&size, sizeof(size));

	if (size <= paletteNumber)
	{
		throw std::exception("no palette that high");
	}


	file.read((char*)&size, sizeof(size));

	file.seekg(paletteNumber * (size + 1) * sizeof(float), file.cur);




	float* paletteData = new float[size];

	file.read((char*)paletteData, size * sizeof(float));

	






	glGenTextures(1, &paletteTexture);

	glBindTexture(GL_TEXTURE_1D, paletteTexture);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, paletteData);
}



void Framebuffer::createUniforms()
{
}




void Framebuffer::renderOn()
{
}

void Framebuffer::draw()
{
}
