#include "object.h"
#include "window.h"



glm::vec3 x = glm::vec3(1, 0, 0);
glm::vec3 y = glm::vec3(0, 1, 0);
glm::vec3 z = glm::vec3(0, 0, 1);



//=============================================================================================
//  OBJECT
//=============================================================================================



Object::Object()
{
	setPosition(glm::vec3(0));
	setOrientation(glm::vec3(0));
	setScale(1);

	setColor(1, 1, 1);


	model();
}

Object::Object(glm::vec3 position, glm::vec3 orientation, glm::vec3 scale, glm::vec3 color)
{
	setPosition(position);
	setOrientation(orientation);
	setScale(scale);

	setColor(color);


	model;
}





void Object::addPosition(glm::vec3 position)
{
	mTranslation = glm::translate(mTranslation, position);

	model();
}

void Object::setPosition(glm::vec3 position)
{
	mTranslation = glm::translate(glm::mat4(1.0f), position);

	model();
}









void Object::addOrientation(glm::vec3 rotation)
{
	mRotation = glm::rotate(mRotation, rotation.x, x);
	mRotation = glm::rotate(mRotation, rotation.y, y);
	mRotation = glm::rotate(mRotation, rotation.z, z);

	model();
}

void Object::setOrientation(glm::vec3 rotation)
{
	mRotation = glm::rotate(glm::mat4(1), rotation.x, x);
	mRotation = glm::rotate(mRotation, rotation.y, y);
	mRotation = glm::rotate(mRotation, rotation.z, z);

	model();
}








void Object::addScale(glm::vec3 scale)
{
	mScale = glm::scale(mScale, scale);

	model();
}

void Object::setScale(glm::vec3 scale)
{
	mScale = glm::scale(glm::mat4(1), scale);

	model();
}

void Object::setScale(float scale)
{
	mScale = glm::scale(glm::mat4(1), glm::vec3(scale));

	model();

}











void Object::setColor(glm::vec3 color)
{
	this->color = color;
}

void Object::setColor(float r, float g, float b)
{
	this->color = glm::vec3(r, g, b);
}









void Object::model()
{
	mModel = mTranslation * mRotation * mScale;
}





void Object::useDepth()
{
	
}

void Object::use()
{
	glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(rotationHandle, 1, false, glm::value_ptr(rotationMatrix));

	glUniform1f(colorHandle, color);
}
