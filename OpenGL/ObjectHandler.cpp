#include "ObjectHandler.h"





ObjectHandler::ObjectHandler(const char* vPathRender, const char* fPathRender) :

	program(vPathRender, fPathRender)
{
	createUniforms();
}


ObjectHandler::~ObjectHandler()
{
}



void ObjectHandler::render()
{
}



void ObjectHandler::createUniforms()
{

}
