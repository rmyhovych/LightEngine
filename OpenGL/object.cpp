#include "object.h"

Object::Object(glm::vec3 position, glm::vec3 scale, glm::vec3 color) :
	position_(position),
	scale_(scale),
	color_(color),

	rotation_(glm::mat3(1)),
	model_(glm::mat4(1)),

	modified_(true)
{
}

void Object::move(glm::vec3 vector)
{
	position_ += vector;
	modified_ = true;
}

void Object::rotate(glm::vec3 axis, float angle)
{
	rotation_ = glm::rotate(rotation_, angle, axis);
	modified_ = true;
}

void Object::scale(glm::vec3 vector)
{
	scale_ *= vector;
	modified_ = true;
}

void Object::setColor(glm::vec3 color)
{
	color_ = color;
}

glm::vec3& Object::getPosition()
{
	return position_;
}

void Object::linkRotation(const char* name, GLuint ID)
{
	rotationPtr_ = glGetUniformLocation(ID, name);
}

void Object::linkModel(const char* name, GLuint ID)
{
	modelPtr_ = glGetUniformLocation(ID, name);
}

void Object::linkColor(const char* name, GLuint ID)
{
	colorPtr_ = glGetUniformLocation(ID, name);
}

void Object::use()
{
	if (modified_)
	{
		constructModel();
		modified_ = false;
	}

	glm::mat3 rotate = glm::mat3(rotation_);

	glUniformMatrix3fv(rotationPtr_, 1, GL_FALSE, glm::value_ptr(rotate));
	glUniformMatrix4fv(modelPtr_, 1, GL_FALSE, glm::value_ptr(model_));
	glUniform3f(colorPtr_, color_.x, color_.y, color_.z);
}

void Object::constructModel()
{
	model_ = glm::translate(glm::mat4(1), position_);
	model_ = model_ * rotation_;
	model_ = glm::scale(model_, scale_);
}

