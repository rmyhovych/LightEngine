#include "Object.h"





glm::vec3 Object::right(1, 0, 0);
glm::vec3 Object::top(0, 1, 0);
glm::vec3 Object::back(0, 0, 1);



//=============================================================================================
//  OBJECT
//=============================================================================================



Object::Object(
	const glm::vec3& position, 
	const glm::vec3& orientation, 
	const glm::vec3& scale, 
	const glm::vec3& color) :
	
	mScale(0),
	mRotation(0),
	mTranslation(0),
	
	mModel(0)
{
	setScale(scale);
	setOrientation(orientation);
	setPosition(position);

	setColor(color);


	model();
}





void Object::addPosition(const glm::vec3& position)
{
	mTranslation = glm::translate(mTranslation, position);

	model();
}

void Object::setPosition(const glm::vec3& position)
{
	mTranslation = glm::translate(glm::mat4(1.0f), position);

	model();
}









void Object::addOrientation(const glm::vec3& rotation)
{
	mRotation = glm::rotate(mRotation, rotation.x, right);
	mRotation = glm::rotate(mRotation, rotation.y, top);
	mRotation = glm::rotate(mRotation, rotation.z, back);

	model();
}

void Object::setOrientation(const glm::vec3& rotation)
{
	mRotation = glm::rotate(glm::mat4(1), rotation.x, right);
	mRotation = glm::rotate(mRotation, rotation.y, top);
	mRotation = glm::rotate(mRotation, rotation.z, back);

	model();
}








void Object::addScale(const glm::vec3& scale)
{
	mScale = glm::scale(mScale, scale);

	model();
}

void Object::setScale(const glm::vec3& scale)
{
	mScale = glm::scale(glm::mat4(1), scale);

	model();
}

void Object::setScale(float scale)
{
	mScale = glm::scale(glm::mat4(1), glm::vec3(scale));

	model();

}











void Object::setColor(const glm::vec3& color)
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

void Object::use(ObjectUniforms& uniforms)
{
	glUniformMatrix4fv(uniforms.mModel, 1, false, glm::value_ptr(mModel));
	glUniformMatrix4fv(uniforms.mRotation, 1, false, glm::value_ptr(mRotation));

	glUniform3f(uniforms.vColor, color.r, color.g, color.b);
}
