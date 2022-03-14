#include "StateMachineComponentsKW.h"
#include "Actor.h"
#include "SteeringComponent.h"
#include "SeekComponentKW.h"
#include "MoveComponent.h"
#include "Transform2D.h"

void StateMachineComponentsKW::start()
{
	Component::start();

	m_seekComponent = getOwner()->getComponent<SeekComponentKW>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_currentState = SEEK;
}

void StateMachineComponentsKW::update(float deltaTime)
{
	Component::update(deltaTime);

	switch (m_currentState)
	{
	case SEEK:
		m_seekComponent->setSteeringForce(m_seekForce);
		break;
	case ATTACKENEMY:

		break;
	}
}
