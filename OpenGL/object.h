#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


struct LightHandle;

class Object
{
public:

	glm::mat4 mRotation;
	glm::mat4 mModel;


	glm::vec3 color;





	Object();

	Object(glm::vec3 position, glm::vec3 orientation, glm::vec3 scale, glm::vec3 color);




	void addPosition(glm::vec3 position);

	void setPosition(glm::vec3 position);



	void addOrientation(glm::vec3 rotation);

	void setOrientation(glm::vec3 rotation);




	void addScale(glm::vec3 v);

	void setScale(glm::vec3 v);

	void setScale(float v);



	void setColor(glm::vec3 color);

	void setColor(float r, float g, float b);


	void useDepth();

	void use();




private:

	void model();


	static const glm::vec3 x;
	static const glm::vec3 y;
	static const glm::vec3 z;


	glm::mat4 mScale;
	glm::mat4 mTranslation;


};













struct LightHandle
{
	GLuint posHandle;
	GLuint intensityHandle;
};