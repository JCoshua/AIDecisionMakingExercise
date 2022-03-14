#include "EvadeJComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "MoveComponent.h"

MathLibrary::Vector2 EvadeJComponent::calculateForce()
{
	MathLibrary::Vector2 V = getOwner()->getTransform()->getWorldPosition() - (getTarget()->getTransform()->getWorldPosition() + getTarget()->getComponent<MoveComponent>()->getVelocity());
	MathLibrary::Vector2 SteeringForce = V.getNormalized() * m_speed - m_velocity;
	m_velocity = m_velocity + SteeringForce;
	return m_velocity;
}