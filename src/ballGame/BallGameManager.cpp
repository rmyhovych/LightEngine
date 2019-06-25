#define MAX_COUNTER 3
#define PI 3.14159265359

#include "BallGameManager.h"

#include <random>
#include <time.h>


btScalar randomScalar()
{
	return btScalar(rand()) / btScalar(RAND_MAX);
}

int randomInt(int nPossibilities)
{
	return rand() % nPossibilities;
}


BallGameManager::BallGameManager(GLProgram* program, int nTunnels, const glm::vec3& scale, int nSides, Object* ball) :

	m_ball(ball),

	m_nTunnels(nTunnels),

	m_lastTunnelIndex(0),
	m_focusTunnel(4),

	m_counter(MAX_COUNTER),

	m_currentRotation(btVector3(0, 1, 0), btScalar(0)),
	m_orientation(btVector3(0, 1, 0), btScalar(0)),
	m_front(0, 0, -scale.z),
	m_side(0, scale.x, 0),


	m_scale(scale),

	m_sideAngle(std::cos(PI / (double)(nSides / 2))),

	m_nSides(nSides)
{
	srand(time(NULL));

	m_ball->getBody()->setDamping(0.999, 0.0);

	m_objectManager = program->addTunnelManager(nSides, scale.z, scale.x);


	Tunnel* tunnel = new Tunnel;

	tunnel->object = m_objectManager->createObject(0, 0, 0, {0, 0, 0}, { 1, 1, 1 }, scale);
	tunnel->position = btVector3(0, 0, 0);

	m_tunnels.push_back(tunnel);

	for (int i = m_nTunnels - 1; i > 0; i--)
	{
		createNewTunnel();
	}

	m_tunnels.shrink_to_fit();
}


BallGameManager::~BallGameManager()
{
	for (int i = m_tunnels.size() - 1; i >= 0; i--)
	{
		delete m_tunnels[i];
		m_tunnels[i] = nullptr;
	}
}


void BallGameManager::step(Camera* camera)
{
	const btVector3& ballPosition = m_ball->getPosition();

	choseFocus(ballPosition);

	btVector3 gravity = m_tunnels[m_focusTunnel]->position - ballPosition;
	gravity.normalize();

	gravity *= btScalar(30);

	m_ball->setGravity(gravity);

	setCameraProperties(camera);
}

void BallGameManager::moveRight()
{
	m_ball->push(15 * getRightVector());
}

void BallGameManager::moveLeft()
{
	m_ball->push(-15 * getRightVector());
}

void BallGameManager::setCameraProperties(Camera* camera)
{
	btVector3 parallel = m_tunnels[m_focusTunnel]->position - m_tunnels[m_focusTunnel - 1 < 0 ? m_nTunnels - 1 : m_focusTunnel - 1]->position;

	btVector3 up = m_ball->getGravity().cross(parallel).cross(parallel);
	btVector3 ballPos = m_ball->getPosition();

	parallel.normalize();
	up.normalize();

	parallel -= 0.4 * up;

	camera->setFocus({ ballPos.getX(), ballPos.getY(), ballPos.getZ() }, { up.getX(), up.getY(), up.getZ() });
	camera->setDirection({ parallel.getX(), parallel.getY(), parallel.getZ() });
}


void BallGameManager::choseFocus(const btVector3& ballPos)
{
	int i = (0 - 1) % 10;

	const btVector3& lastTunnelPos = m_tunnels[(m_focusTunnel - 1) < 0 ? m_nTunnels - 1 : m_focusTunnel - 1]->position;
	const btVector3& focusTunnelPos = m_tunnels[m_focusTunnel]->position;

	if ((ballPos - lastTunnelPos).length() > (ballPos - focusTunnelPos).length())
	{
		m_focusTunnel = (m_focusTunnel + 1) % m_nTunnels;
		shiftTunnels();
	}
}





void BallGameManager::createNewTunnel()
{
	Tunnel* newTunnel = new Tunnel;

	newTunnel->object = m_objectManager->createObject(0, 0, 0, { 0, 0, 0 }, { 1, 1, 1 }, m_scale);

	m_tunnels.push_back(newTunnel);

	setTunnel(m_tunnels.size() - 1);
}



void BallGameManager::shiftTunnels()
{
	setTunnel(m_lastTunnelIndex);

	m_lastTunnelIndex = (m_lastTunnelIndex + 1) % m_nTunnels;
}


void BallGameManager::setTunnel(int tunnelIndex)
{
	if (--m_counter == 0)
	{
		m_counter = MAX_COUNTER;

		generateRotation();
	}

	Tunnel* newTunnel = m_tunnels[tunnelIndex];
	Tunnel* oldTunnel = m_tunnels[(tunnelIndex - 1) < 0 ? m_nTunnels - 1 : tunnelIndex - 1];


	const btVector3 rotAxis = m_currentRotation.getAxis();
	const btScalar rotAngle = m_currentRotation.getAngle();

	btVector3 newFront = m_front.rotate(rotAxis, rotAngle);
	btVector3 newSide = m_side.rotate(rotAxis, rotAngle);

	newTunnel->position = oldTunnel->position + m_front + newFront + newSide - m_side;

	m_orientation = m_currentRotation * m_orientation; // was doing the opposite, fuck this shit 

	m_front = newFront;
	m_side = newSide;


	newTunnel->object->setPosition(newTunnel->position);
	newTunnel->object->setRotation(m_orientation);
}



void BallGameManager::generateRotation()
{
	m_front = btVector3(0, 0, -m_scale.z).rotate(m_orientation.getAxis(), m_orientation.getAngle()); // precision is getting fucked
	btVector3 top = m_side.cross(m_front);


	btScalar newAngle = m_sideAngle * randomInt(m_nSides);
	btVector3 rotDirection = top.rotate(m_front, newAngle);

	m_side = (btScalar(m_scale.x) / rotDirection.norm()) * -rotDirection;
	
	btVector3 rotAxis = rotDirection.cross(m_front);
	btScalar rotAngle = randomScalar() / 5.0;

	m_currentRotation.setRotation(rotAxis, rotAngle);
}

btVector3 BallGameManager::getRightVector()
{
	btVector3 parallel = m_tunnels[m_focusTunnel]->position - m_tunnels[m_focusTunnel - 1 < 0 ? m_nTunnels - 1 : m_focusTunnel - 1]->position;

	return m_ball->getGravity().cross(parallel).normalized();
}

