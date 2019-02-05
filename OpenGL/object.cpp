#include "object.h"


//=============================================================================================
//  STATIC
//=============================================================================================


void Object::compilePrograms()
{
	program = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	programShadow = Shader("shaders/vertex_shadow.glsl", "shaders/fragment_shadow.glsl");


	createUniforms();

	addFramebuffer();
}





void Object::initRenderingShadow()
{
	glViewport(0, 0, depthMapSize, depthMapSize);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClear(GL_DEPTH_BUFFER_BIT);
	glColorMask(false, false, false, false);


	programShadow.use();

}




void Object::initRendering()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, GLWindow::width, GLWindow::height);

	glColorMask(true, true, true, true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	program.use();
	glBindTexture(GL_TEXTURE_2D, depthMap);
}




void Object::addFramebuffer()
{
	//  DEPTH MAP TEXTURE

		//      create depthMap
	glGenTextures(1, &depthMap);


	//      use depthMap
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, depthMapSize, depthMapSize, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);





	//  FRAMEBUFFER OBJECT

	//      create fbo
	glGenFramebuffers(1, &fbo);


	//      use fbo
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);


	//      no draw buffers
	glDrawBuffer(GL_NONE);


	//      bind data to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, depthMap, 0);



	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.5f, 150.0f);

}




void Object::createUniforms()
{
	//  link uniforms
	program.use();

	rotationHandle = program.getUniformLocation("mRotation");
	modelHandle = program.getUniformLocation("mModel");
	viewHandle = program.getUniformLocation("mView");
	projectionHandle = program.getUniformLocation("mProjection");


	colorHandle = program.getUniformLocation("vColor");


	dirLightHandle = program.getUniformLocation("vDirLight");

	sizeHandle = program.getUniformLocation("uSize");

	lightSpaceHandle = program.getUniformLocation("mLightSpace");




	//  link shadow uniforms
	programShadow.use();

	modelHandleShadow = programShadow.getUniformLocation("mModel");
	lightSpaceHandleShadow = programShadow.getUniformLocation("mLightSpace");
}









//=============================================================================================
//  OBJECT
//=============================================================================================



Object::Object()
{
	setScale(scale);
	setPosition(position);
	setAngle(angle, 0, 0, 1);

	this->color = 1.0f;


	model();
}

Object::Object(glm::vec3 scale, glm::vec3 position, float angle, float color)
{
	setScale(scale);
	setPosition(position);
	setAngle(angle, 0, 0, 1);


	this->color = color;

	model();
}





void Object::setPosition(glm::vec3 v)
{
	position = v;

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, position);

	model();
}

void Object::setPosition(float x, float y, float z)
{
	position.x = x;

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, position);

	model();
}





void Object::setAngle(float angle, glm::vec3 v)
{
	this->angle = angle;

	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, angle, v);

	model();
}

void Object::setAngle(float angle, float x, float y, float z)
{
	this->angle = angle;

	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(x, y, z));

	model();
}





void Object::setScale(glm::vec3 v)
{
	this->scale = v;

	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, v);

	model();
}

void Object::setScale(float x, float y, float z)
{
	this->scale = glm::vec3(x, y, z);

	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, scale);

	model();
}

void Object::setScale(float v)
{
	this->scale = glm::vec3(v, v, v);

	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, scale);

	model();
}



void Object::model()
{
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}





void Object::drawShadow()
{
	glUniformMatrix4fv(modelHandleShadow, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Object::draw()
{
	glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(rotationHandle, 1, false, glm::value_ptr(rotationMatrix));

	glUniform1f(colorHandle, color);
}
