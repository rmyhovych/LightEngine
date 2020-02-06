#include "ObjectRenderer.h"


//=============================================================================================
//  OBJECT
//=============================================================================================



ObjectRenderer::ObjectRenderer(const glm::vec3& color, const glm::vec3& scale) :
	
	mScale(0),
	mMovement(0),
	
	mModel(0)
{
	mScale = glm::scale(glm::mat4(1), scale);

	this->color = color;

	model();
}

float* ObjectRenderer::getMovementPtr()
{
	return glm::value_ptr(mMovement);
}


glm::vec3 ObjectRenderer::getScale()
{
	return (mScale * glm::vec4(1));
}



void ObjectRenderer::model()
{
	mModel = mMovement * mScale;
}





void ObjectRenderer::useDepth()
{
	
}

void ObjectRenderer::use(ObjectUniforms& uniforms)
{
	glm::mat3 mRotation(mModel);
	mRotation = glm::transpose(glm::inverse(mModel));

	glUniformMatrix4fv(uniforms.mModel, 1, false, glm::value_ptr(mModel));
	glUniformMatrix3fv(uniforms.mRotation, 1, false, glm::value_ptr(mRotation));

	
	glUniform3fv(uniforms.vColor, 1, glm::value_ptr(color));
}

void ObjectRenderer::useDepth(GLint modelIndex)
{
	glUniformMatrix4fv(modelIndex, 1, false, glm::value_ptr(mModel));
}
