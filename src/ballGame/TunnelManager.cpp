#define MAX_COUNTER 1

#include "TunnelManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <random>
#include <time.h>


float randomFloat()
{
	float max = ((float)RAND_MAX) / 2.0f;

	return ((float)rand() - max) / max;
}

int randomInt(int nPossibilities)
{
	return rand() % nPossibilities;
}


TunnelManager::TunnelManager(GLProgram* program, const glm::vec3& scale, int nSides, Object* ball) :

	m_ball(ball),

	m_counter(MAX_COUNTER),

	m_currentRotation(btVector3(0, 1, 0), btScalar(0)),
	m_orientation(btVector3(0, 1, 0), btScalar(0)),
	m_front(0, 0, -scale.z),
	m_side(0, scale.x, 0),


	m_scale(scale),

	m_sideAngle(std::cos(std::_Pi / (double)(nSides / 2))),

	m_nSides(nSides)
{
	srand(time(NULL));


	m_objectManager = program->addPhantomManager("binary/tunnel" + std::to_string(nSides));


	Tunnel* tunnel = new Tunnel;

	tunnel->object = m_objectManager->createObject(0, 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, scale);
	tunnel->position = btVector3(0, 0, 0);

	m_tunnels.push_back(tunnel);
}


TunnelManager::~TunnelManager()
{
	for (int i = m_tunnels.size() - 1; i >= 0; i--)
	{
		delete m_tunnels[i];
		m_tunnels[i] = nullptr;
	}
}

void TunnelManager::create()
{
	if (--m_counter == 0)
	{
		m_counter = MAX_COUNTER;

		generateRotation();
	}


	Tunnel* oldTunnel = m_tunnels[m_tunnels.size() - 1];
	Tunnel* newTunnel = new Tunnel;

	m_tunnels.push_back(newTunnel);

	
	newTunnel->object = m_objectManager->createObject(0, 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, m_scale);

	const btVector3 rotAxis = m_currentRotation.getAxis();
	const btScalar rotAngle = m_currentRotation.getAngle();

	btVector3 newFront = m_front.rotate(rotAxis, rotAngle);
	btVector3 newSide = m_side.rotate(rotAxis, rotAngle);

	newTunnel->position = oldTunnel->position + m_front + newFront + newSide - m_side;

	m_orientation *= m_currentRotation;

	m_front = newFront;
	m_side = newSide;


	newTunnel->object->setPosition(newTunnel->position);
	newTunnel->object->setRotation(m_orientation);
}



void TunnelManager::generateRotation()
{
	btVector3 top = m_side.cross(m_front);


	btScalar newAngle = m_sideAngle * randomInt(m_nSides / 2);
	btVector3 rotDirection = top.rotate(m_front, newAngle);

	m_side = (btScalar(m_scale.x) / rotDirection.norm()) * rotDirection;
	
	btVector3 rotAxis = rotDirection.cross(m_front);
	btScalar rotAngle = randomFloat() / 10.0;

	static bool sameOrientation = rotAngle < 0;

	if (sameOrientation && rotAngle > 0)
	{
		m_side *= -1.0;
		sameOrientation = !sameOrientation;
	}

	m_currentRotation.setRotation(rotAxis, rotAngle);
}

