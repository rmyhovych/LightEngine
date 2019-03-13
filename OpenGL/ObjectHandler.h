#pragma once

#include <vector>

#include "Object.h"



class ObjectHandler
{
public:
	ObjectHandler();

	~ObjectHandler();


	virtual void draw() = 0;

protected:

	std::vector<Object*> objectArray;


};

