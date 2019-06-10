#pragma once

#include "GLProgram.h"

#include <vector>

class TunnelManager
{
public:
	TunnelManager(GLProgram* program, const glm::vec3& scale, int nSides, Object* ball);
	~TunnelManager();

	void create();


private:
	
	void generateRotation();

private:

	struct Tunnel
	{
		Object* object;
		btVector3 position;
	};

	
	Object* m_ball;

	ObjectManager* m_objectManager;

	std::vector<Tunnel*> m_tunnels;


	int m_counter;

	btQuaternion m_currentRotation;
	btQuaternion m_orientation;
	btVector3 m_front;
	btVector3 m_side;


	const glm::vec3 m_scale;

	const btScalar m_sideAngle;

	const int m_nSides;
};

