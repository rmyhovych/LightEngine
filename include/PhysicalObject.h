#include "Object.h"

#include <btBulletDynamicsCommon.h>


class PhysicalObject
{
public:
	PhysicalObject();
	~PhysicalObject();

private:

	Object* parent;
};

