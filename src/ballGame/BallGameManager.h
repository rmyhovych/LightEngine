#pragma once

#include "GLProgram.h"
#include "Camera.h"

#include <vector>

class BallGameManager
{
public:
	BallGameManager(GLProgram* program, int nTunnels, const glm::vec3& scale, int nSides, Object* ball);
	~BallGameManager();

	void step(Camera* camera);
	
	
	void moveRight();
	void moveLeft();


private:


	void setCameraProperties(Camera* camera);

	void choseFocus(const btVector3& ballPos);

	void createNewTunnel();

	void shiftTunnels();

	void setTunnel(int tunnelIndex);

	void generateRotation();

	btVector3 getRightVector();

private:
	
	Object* m_ball;

	std::vector<Object*> m_tunnels;
	const int m_nTunnels;

	int m_lastTunnelIndex;
	int m_focusTunnel;

	ObjectManager* m_objectManager;

	int m_counter;

	btQuaternion m_currentRotation;
	btQuaternion m_orientation;
	btVector3 m_front;
	btVector3 m_side;


	const glm::vec3 m_scale;

	const btScalar m_sideAngle;

	const int m_nSides;
};

