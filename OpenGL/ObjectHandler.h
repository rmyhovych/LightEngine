#pragma once

#include <vector>

#include "Object.h"



class ObjectHandler
{
public:
	ObjectHandler();

	~ObjectHandler();


	virtual void renderDepth() = 0;

	virtual void render() = 0;

protected:

	virtual void initRendering() = 0;

	std::vector<Object*> objectArray;


};

